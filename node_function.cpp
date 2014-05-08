
/*
 * 节点的各项动作
 *
 * */

#include "NODE.h"

int NODE::vote_expire(int current_time)                 // 淘汰超过时间间隔的投票
{
    while(!Q_vote_rev.empty() && current_time - Q_vote_rev.front().time >= RESERVE_TIME)
    {
        for(int i = 0; i < VOTE_K; i++)
            tot_vote.v[i] -= Q_vote_rev.front().v[i]; 
        Q_vote_rev.pop(); 
    }
    return 0; 
}

int NODE::update_time(int current_time)
{
    duration = current_time; 
    return 0; 
}

int NODE::update(int current_time)
{
    // update投票, 淘汰超过保留时间的投票.
    update_time(current_time); 
    vote_expire(current_time); 

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

    return 0; 
}

int NODE::vote_for(int to_ID, MSG &msg)              // 向其他节点发送信息
{
    msg.ID1 = ID; 
    msg.ID2 = to_ID;  
    msg.state = state; 
    msg.voting = voting; 
    msg.vote_level = vote_level; 
    return 0; 
}

int NODE::be_voted(int from_ID, MSG msg)             // 被投票
{
    if(msg.voting)
    {
        if(Q_vote_rev.empty() || duration - Q_vote_rev.back().time >= INTERVAL_TIME)
            Q_vote_rev.push(VOTE(duration)); 
        Q_vote_rev.back().v[vote_level]++;
        tot_vote.v[vote_level]++; 
    }
    M_adj_node[msg.ID1] = msg.state; 
    return 0; 
}

int NODE::connect(int ID)               // 向其他节点发出连接, 根据节点ID连接, ID即为被连接节点ID
{
    // 更新 M_contacts_rec, 从Q_max_k_heap中选出最大的k组.
    int k = ++M_contacts_rec[ID];       // 增加一次连接计数
    voting = false;                     // 是否向该节点投票
    vote_level = 0;                     // 选票类型

    // 更新Q_max_k_heap, 并选出前k多连接次数的节点
    int i = 0; 
    for(vector < pair < int, int > >::iterator it = Q_max_k_heap.begin(); it != Q_max_k_heap.end(); it++, i++)
        if(k >= it->second) 
        {
            Q_max_k_heap.insert(it, MP(ID, k));
            voting = true; 
            vote_level = i; 
            break; 
        }
    if( ! voting) 
    {
        if(Q_max_k_heap.size() < VOTE_K)
        {
            Q_max_k_heap.push_back(MP(ID, k)); 
            vote_level = Q_max_k_heap.size() - 1; 
            voting = true; 
        }else
        {
            if(Q_max_k_heap.size() > VOTE_K)
                Q_max_k_heap.pop_back(); 
        }
    }
    return 0; 
}

bool NODE::is_dominator(int state)
{
    return state >= 50 ? true : false; 
}

//int NODE::game()              // 博弈, 确定状态
//{
//    return 0; 
//}

