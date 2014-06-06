
/*
 * 节点的各项动作
 *
 * */

#include "NODE.h"
#include <fstream>

extern ofstream fout;

bool cmp(const pair<int, int> &t1, const pair<int, int> &t2)
{
    return t1.second < t2.second;
}

int NODE::vote_expire(int current_time)
{
    tmp_adj_max_state = state;
    tmp_adj_max_node = ID;
    contacts = 0;

    while (!Q_vote_rev.empty() && current_time - Q_vote_rev.front().first >= RESERVE_TIME)
    {
        state -= Q_vote_rev.front().second;
        Q_vote_rev.pop();
    }

    Q_vote_rev.push(MP(current_time, 0));
    map < int, MSG_REC >::iterator iter;
    map <int, int>::iterator c_iter;

    for (iter = M_adj_node.begin(); iter != M_adj_node.end();)
    {
        if (current_time - iter->second.time >= RESERVE_TIME)
        {
            M_contacts_rec.erase(iter->second.ID);
            M_adj_node.erase(iter++);
        }
        else
        {
            if (M_contacts_rec.count(iter->second.ID))
            {
                M_contacts_rec[iter->second.ID]--;

                if (M_contacts_rec[iter->second.ID] == 0)
                {
                    M_contacts_rec.erase(iter->second.ID);
                    M_adj_node.erase(iter++);
                    continue;
                }
            }

            iter++;
        }
    }

    Q_max_k_heap.clear();

    for (c_iter = M_contacts_rec.begin(); c_iter != M_contacts_rec.end(); ++c_iter)
    {
        Q_max_k_heap.push_back(MP(c_iter->first, c_iter->second));
    }

    sort(Q_max_k_heap.begin(), Q_max_k_heap.end(), cmp);
    return 0;
}

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
    MSG_REC msg_rec(ID, state, adj_max_state, adj_max_node, contacts, is_dominator, duration);
    return MSG(ID, to_ID, msg_rec, direct_vote, indirect_vote);
}

vector < pair < int, int > >::iterator NODE::in_Q_heap(int ID)
{
    vector < pair < int, int > >::iterator pos;
    int k;

    for (k = 0, pos = Q_max_k_heap.begin(); k < VOTE_K && pos != Q_max_k_heap.end(); pos++)
        if (ID == pos->first)
        {
            break;
        }

    if (k == VOTE_K)
    {
        pos = Q_max_k_heap.end();
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

    /*
        if (Q_max_k_heap.size() > VOTE_K)
        {
            Q_max_k_heap.pop_back();
        }
        else if (Q_max_k_heap.size() < VOTE_K)
        {
            Q_max_k_heap.push_back(node);
        }
    */
    return 0;
}

int NODE::be_connected(MSG msg)                 // 被投票
{
    state += msg.direct_vote.vote;
    Q_vote_rev.back().second += msg.direct_vote.vote;
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

    if (tmp_adj_max_state < t_rec.state)
    {
        tmp_adj_max_state = t_rec.state;
        tmp_adj_max_node = msg.ID1;

        if (M_contacts_rec.count(msg.ID1))
        {
            tmp_contacts = M_contacts_rec[msg.ID1];
        }
    }

    /*
        if (tmp_adj_max_state <= state)
        {
            tmp_adj_max_state = state;
            tmp_adj_max_node = ID;
            tmp_contacts = 0;
        }
    */
    if (adj_max_state < tmp_adj_max_state)
    {
        adj_max_state = tmp_adj_max_state;
        adj_max_node = tmp_adj_max_node;
        contacts = tmp_contacts;
    }

    return 0;
}

int NODE::update(int current_time)
{
    // update投票, 淘汰超过保留时间的投票.
    update_time(current_time);
    vote_expire(current_time);
    // 确定is_dominator的状态
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

    if (state >= adj_max_state)
    {
        adj_max_state = state;
        adj_max_node = ID;
    }

    double p, q;

    // p = adj_max_state == 0 ? 1.0 : 1.0 * state / adj_max_state;
    if (state == 0 || adj_max_state == 0)
    {
        p = 0;
    }
    else
    {
        p = 1.0 * state / adj_max_state;
    }

    if (state == 0 || avg_adj_dee == 0)
    {
        q = 0;
        p = 0;
    }
    else if (avg_adj_dor == 0)
    {
        q = state / (avg_adj_dee * sum_adj_dee);
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

    // is_dominator = random_dor(dor_prob);
    is_dominator = (dor_prob >= DOR_THRESHOLD);
    //
    adj_max_state = tmp_adj_max_state;
    adj_max_node = tmp_adj_max_node;
    contacts = tmp_contacts;
    return 0;
}

int NODE::update_time(int current_time)
{
    duration = current_time;
    return 0;
}

