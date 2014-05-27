
/*
 * 节点的各项动作
 *
 * */

#include "NODE.h"
#include <fstream>

extern ofstream fout;

bool NODE::random_dor(double prob)
{
    double t = 1.0 * rand() / RAND_MAX;
    return t - prob <= 0.00001;
}

MSG NODE::connect(int to_ID)                    // 向其他节点发出连接, 根据节点ID连接, ID即为被连接节点ID
{
    // 更新 M_contacts_rec, 从Q_max_k_heap中选出最大的k组.
    vector < pair < int, int > >::iterator posB, posC;  // Q_max_k_heap;
    int index, indirect_vote_ID;
    int value, voteB, voteC;
    int a, b, c;
    voteB = voteC = 0;
    indirect_vote_ID = 0;
    a = ++M_contacts_rec[to_ID];
    Q_heap_insert(MP(to_ID, a));
    posB = in_Q_heap(to_ID);

    if (posB != Q_max_k_heap.end())
    {
        if (M_adj_node.count(to_ID))
        {
            MSG_REC t_rec = M_adj_node[to_ID];              // B
            indirect_vote_ID = t_rec.adj_max_node;
            b = t_rec.contacts;

            if (state < t_rec.state)                        // A.s < B.s
            {
                if (t_rec.adj_max_node == to_ID)            // B == C
                {
                    index = posB - Q_max_k_heap.begin();
                    voteB += Q_vote[index];
                }
                else                                        // C.s > B.s
                {
                    posC = in_Q_heap(t_rec.adj_max_node);

                    if (posC != Q_max_k_heap.end())         // C in A.Q
                    {
                        c = ++M_contacts_rec[t_rec.adj_max_node];
                        Q_heap_insert(MP(t_rec.adj_max_node, c));
                        posB = in_Q_heap(to_ID);

                        if (posB != Q_max_k_heap.end())
                        {
                            index = posB - Q_max_k_heap.begin();
                        }
                        else
                        {
                            index = VOTE_K - 1;
                        }

                        value = Q_vote[index];

                        if (a > b)
                        {
                            voteB += floor(1.0 * value * a / (a + c) * (a - b) / a);
                        }

                        voteC += value - voteB;
                    }
                    else                                    // C not in A.Q
                    {
                        index = posB - Q_max_k_heap.begin();
                        value = Q_vote[index];

                        if (a > b)
                        {
                            voteB += floor(1.0 * value * (a - b) / a);
                        }

                        voteC += value - voteB;
                    }
                }
            }
            else                                            // B.s < A.s
            {
                if (state >= t_rec.adj_max_state || t_rec.adj_max_node == ID)               // A == C
                {
                    index = posB - Q_max_k_heap.begin();
                    value = Q_vote[index];
                    state += value;
                    indirect_vote_ID = 0;
                }
                else
                {
                    posC = in_Q_heap(t_rec.adj_max_node);

                    if (posC != Q_max_k_heap.end())         // C in A.Q
                    {
                        c = ++M_contacts_rec[t_rec.adj_max_node];
                        Q_heap_insert(MP(t_rec.adj_max_node, c));
                        posB = in_Q_heap(to_ID);

                        if (posB != Q_max_k_heap.end())
                        {
                            index = posB - Q_max_k_heap.begin();
                        }
                        else
                        {
                            index = VOTE_K - 1;
                        }

                        value = Q_vote[index];
                        voteC += value;
                    }
                    else                                    // C not in A.Q
                    {
                        //
                    }
                }
            }
        }
        else                                                // A.s ? B.s
        {
            index = posB - Q_max_k_heap.begin();
            value = Q_vote[index];
            voteB += value;
        }
    }

    if (M_indirect_vote.count(to_ID))
    {
        voteB += M_indirect_vote[to_ID];
        M_indirect_vote[to_ID] = 0;
    }

    VOTE direct_vote(ID, to_ID, voteB);
    VOTE indirect_vote(to_ID, indirect_vote_ID, voteC);
    MSG_REC msg_rec(state, adj_max_state, adj_max_node, contacts, is_dominator);
    return MSG(ID, to_ID, msg_rec, direct_vote, indirect_vote);
}

vector < pair < int, int > >::iterator NODE::in_Q_heap(int ID)
{
    vector < pair < int, int > >::iterator pos;

    for (pos = Q_max_k_heap.begin(); pos != Q_max_k_heap.end(); pos++)
        if (ID == pos->first)
        {
            break;
        }

    return pos;
}

int NODE::Q_heap_insert(pair < int, int > node)
{
    vector < pair < int, int > >::iterator pos;
    pos = in_Q_heap(node.first);

    if (pos != Q_max_k_heap.end())
    {
        Q_max_k_heap.erase(pos);
    }

    for (pos = Q_max_k_heap.begin(); pos != Q_max_k_heap.end(); pos++)
        if (node.second >= pos->second)
        {
            Q_max_k_heap.insert(pos, node);
            break;
        }

    if (Q_max_k_heap.size() > VOTE_K)
    {
        Q_max_k_heap.pop_back();
    }
    else if (Q_max_k_heap.size() < VOTE_K)
    {
        Q_max_k_heap.push_back(node);
    }

    return 0;
}

int NODE::be_connected(MSG msg)                 // 被投票
{
    state += msg.direct_vote.vote;
    MSG_REC t_rec = msg.msg_rec;

    if (M_adj_node.count(msg.ID1))
    {
        adj_tot_state -= M_adj_node[msg.ID1].state;
    }

    M_adj_node[msg.ID1] = t_rec;
    adj_tot_state += t_rec.state;

    if (msg.indirect_vote.to_ID && M_indirect_vote.count(msg.indirect_vote.to_ID))
    {
        M_indirect_vote[msg.indirect_vote.to_ID] += msg.indirect_vote.vote;
    }
    else
    {
        M_indirect_vote.insert(MP(msg.indirect_vote.to_ID, msg.indirect_vote.vote));
    }

    if (adj_max_state < t_rec.state)
    {
        adj_max_state = t_rec.state;
        adj_max_node = msg.ID1;

        if (M_contacts_rec.count(msg.ID1))
        {
            contacts = M_contacts_rec[msg.ID1];
        }
    }

    if (adj_max_state <= state)
    {
        adj_max_state = state;
        adj_max_node = ID;
        contacts = 0;
    }

    return 0;
}

int NODE::update(int current_time)
{
    // update投票, 淘汰超过保留时间的投票.
    update_time(current_time);
    // 确定is_dorminator的状态
    is_dominator = random_dor(dor_prob);
    map < int, MSG_REC >::iterator iter;
    int sum_adj_dor, sum_adj_dee;
    double avg_adj_dor, avg_adj_dee;
    sum_adj_dor = sum_adj_dee = 0;
    avg_adj_dor = avg_adj_dee = 0;

    for (iter = M_adj_node.begin(); iter != M_adj_node.end(); ++iter)
    {
        if (iter->second.is_dominator)
        {
            avg_adj_dor += iter->second.state;
            sum_adj_dor++;
        }
        else
        {
            avg_adj_dee += iter->second.state;
            sum_adj_dee++;
        }
    }

    if (sum_adj_dor > 0)
    {
        avg_adj_dor /= sum_adj_dor;
    }

    if (sum_adj_dee > 0)
    {
        avg_adj_dee /= sum_adj_dee;
    }

    if (state >= adj_tot_state)
    {
        adj_max_state = state;
        adj_max_node = ID;
    }

    double p, q;
    p = adj_max_state == 0 ? 1.0 : 1.0 * state / adj_max_state;

    if (state == 0)
    {
        q = 1.0;
    }
    else if (avg_adj_dor == 0)
    {
        q = 2.0;
    }
    else
    {
        q = (state + avg_adj_dee) / avg_adj_dor;
    }

    q = min(2.0, q);
    bool flag;

    if (random_dor(q * 0.5))
    {
        // 奖励
        dor_prob = dor_prob + p * (1 - dor_prob);
        flag = true;
    }
    else
    {
        // 惩罚
        dor_prob = p * dor_prob;
        flag = false;
    }

#if DEBUG

    if (ID == 71)
    {
        fout << q << " " << p << " ";
        fout << flag << endl;
        // fout << state << " " << avg_adj_dee << " " << avg_adj_dor << " " << q << endl;
    }

#endif
    // vote_expire(current_time);
    /*
        // state增加

        // 根据投票更新节点状态
        // I.
        // Q_max_k_heap M_adj_node
        for(int i = 0; i < VOTE_K; i++)
        {
            int tID = Q_max_k_heap[i].first;
            if(M_adj_node.count(tID))
            {
                if(is_dominator(M_adj_node[tID]))
                {
                    // 节点投票的节点为DOR, DEE增大.
                }else
                {
                    // 节点投票的节点为DEE, DOR增大.
                }
            }else
            {
                // 节点的投票的节点信息缺失
            }
        }

        // II.
        // tot_vote
        for(int i = 0; i < VOTE_K; i++)
        {

        }
        last_tot_vote = tot_vote;
    */
    return 0;
}

int NODE::update_time(int current_time)
{
    duration = current_time;
    return 0;
}

