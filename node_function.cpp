
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
    Q_vote_rev.push(VOTE(current_time)); 
    return 0; 
}

int NODE::update(int current_time)
{
    // update投票, 淘汰超过保留时间的投票.
    update_time(current_time); 
    vote_expire(current_time); 
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

int NODE::be_connected(int from_ID, MSG msg)             // 被投票
{
    if(msg.is_jump_vote)
    {
        // 二段投票
        Q_vote_rev.back().v[0] += msg.jump_vote.v[0]; 
        // mark
        state += msg.jump_vote.v[0]; 
    }

    if(msg.voting)
    {
        if(msg.vote_level == 0)
        {
            if(state < adj_max_state)
            {
                jump_vote.v[msg.vote_level]++; 
            }else
            {
                Q_vote_rev.back().v[msg.vote_level]++; 
                tot_vote.v[msg.vote_level]++; 
                // mark
                state++; 
            }
        }else
        {
            Q_vote_rev.back().v[msg.vote_level]++; 
            tot_vote.v[msg.vote_level]++; 
        }
    }

    // 更新M_adj_node
    M_adj_node[msg.ID1] = MSG_REC(msg.state, msg.adj_max_state); 
    if(adj_max_state < state)
    {
        adj_max_state = state; 
        adj_max_state_node = 0; 
    }
    if(msg.state > adj_max_state)
    {
        adj_max_state = msg.state; 
        adj_max_state_node = msg.ID1; 
    }
    
    return 0; 
}

MSG NODE::connect(int to_ID)                    // 向其他节点发出连接, 根据节点ID连接, ID即为被连接节点ID
{
    // 更新 M_contacts_rec, 从Q_max_k_heap中选出最大的k组.
    int k = ++M_contacts_rec[to_ID];            // 增加一次连接计数
    bool voting = false;                        // 是否向该节点投票
    int vote_level = 0;                         // 选票类型

    // 更新Q_max_k_heap, 并选出前k多连接次数的节点
    int i = 0; 
    vector < pair < int, int > >::iterator pos; 
    for(pos = Q_max_k_heap.begin(); pos != Q_max_k_heap.end(); pos++)
        if(pos->first == to_ID)
        {
            Q_max_k_heap.erase(pos); 
            break; 
        }
    for(pos = Q_max_k_heap.begin(); pos != Q_max_k_heap.end(); pos++, i++)
        if(k >= pos->second) 
        {
            Q_max_k_heap.insert(pos, MP(to_ID, k));
            voting = true; 
            vote_level = i; 
            break; 
        }

    if(Q_max_k_heap.size() > VOTE_K)
        Q_max_k_heap.pop_back(); 

    if(!voting && i < VOTE_K)
    {
        Q_max_k_heap.push_back(MP(to_ID, k)); 
        voting = true; 
        vote_level = i; 
    }
    
    // 二段投票
    // jump_vote
    if(voting && vote_level == 0 && M_adj_node.count(to_ID))
    {
        // MSG_REC t_rec = M_adj_node[to_ID]; 
        if(state > M_adj_node[to_ID].state)
            voting = false; 
    }

    if(adj_max_state_node == to_ID)
        return MSG(ID, to_ID, state, voting, vote_level, adj_max_state, jump_vote, true); 
    else 
        return MSG(ID, to_ID, state, voting, vote_level, adj_max_state, VOTE(), false); 
}

int NODE::update_time(int current_time)
{
    duration = current_time; 
    return 0; 
}

