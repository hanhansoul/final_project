
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
    if(msg.jump_vote)
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
                Q_vote_rev.back().v[vote_level]++; 
                tot_vote.v[vote_level]++; 
                // mark
                state++; 
            }
        }else
        {
            Q_vote_rev.back().v[vote_level]++; 
            tot_vote.v[vote_level]++; 
        }
    }

/* 
    if(msg.is_jump_vote && msg.vote_level == 0)
    {
        if(state < adj_max_state)
        {
            jump_vote.v[msg.vote_level]++; 
        }else 
        {
            Q_vote_rev.back().v[vote_level]++; 
            tot_vote.v[vote_level]++; 
            // mark
            state++; 
        }
    }

    if(!msg.is_jump_vote &&  msg.voting)
    {
        Q_vote_rev.back().v[vote_level]++; 
        tot_vote.v[vote_level]++; 
        // mark
        if(vote_level == 0)
            state++; 
    }
*/ 

    // 更新M_adj_node
    M_adj_node[msg.ID1] = MSG_REC(msg.state, msg.vote, msg.adj_max_state); 
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

bool cmp(const pair < int, int > &t1, const pair < int, int > &t2)
{
    return t1.second < t2.second; 
}

int NODE::connect(int ID, MSG msg)               // 向其他节点发出连接, 根据节点ID连接, ID即为被连接节点ID
{
    // 更新 M_contacts_rec, 从Q_max_k_heap中选出最大的k组.
    int k = ++M_contacts_rec[ID];       // 增加一次连接计数
    voting = false;                     // 是否向该节点投票
    vote_level = 0;                     // 选票类型

/* 
    vector < pair < int, int > >::iterator pos; 
    pos = lower_bound(Q_max_k_heap.begin(), Q_max_k_heap.end(), ID); 
    if(pos != Q_max_k_heap.end()) 
    {
        *pos->second = k; 
    }else 
    {
        Q_max_k_heap.push_back(MP(ID, k)); 
    }
    sort(Q_max_k_heap.begin(), Q_max_k_heap.end(), cmp); 
    while(Q_max_k_heap.size() > VOTE_K)
    {
        Q_max_k_heap.pop_back(); 
    }
    pos = lower_bound(Q_max_k_heap.begin(), Q_max_k_heap.end(), ID); 
    if(pos != Q_max_k_heap.end())
    {
        voting = true; 
        vote_level = pos - Q_max_k_heap.begin(); 
    }
*/ 

    // 更新Q_max_k_heap, 并选出前k多连接次数的节点
    int i = 0; 
    vector < pair < int, int > >::iterator pos; 
    pos = lower_bound(Q_max_k_heap.begin(), Q_max_k_heap.end(), ID); 
    if(pos != Q_max_k_heap.end())
        Q_max_k_heap.erase(pos); 
    for(pos = Q_max_k_heap.begin(); pos != Q_max_k_heap.end(); pos++, i++)
        if(k >= it->second) 
        {
            Q_max_k_heap.insert(pos, MP(ID, k));
            voting = true; 
            vote_level = i; 
            break; 
        }

    if(Q_max_k_heap.size() > VOTE_K)
        Q_max_k_heap.pop_back(); 

    if(!voting && i < VOTE_K)
    {
        Q_max_k_heap.push_back(MP(ID, k)); 
        voting = true; 
        vote_level = i; 
    }
    
 /* 
    bool is_jump_vote = false; 
    MSG_REC t_rec; 
    if(M_adj_node.count(ID))
    {
        t_rec = M_adj_node[ID]; 
        if(t_rec.adj_max_state > t_rec.state)       // 若B的附近节点的最大state大于B的state, 则A向B的附近节点二段投票而非向B投票.
            is_jump_vote = true; 
        if(state > t_rec.state)                     // 若A的state大于B的state, 则不会向B投票.
            voting = false; 
    }
*/ 

    // 二段投票
    // jump_vote
    MSG_REC t_rec; 
    if(M_adj_node.count(ID))
    {
        t_rec = M_adj_node[ID]; 
        if(state > r_rec.state && vote_level == 0)
            voting = false; 
    }

    if(adj_max_state_node == ID)
        msg = MSG(ID, to_ID, state, tot_vote, voting, vote_level, adj_max_state, jump_vote); 
    else 
        msg = MSG(ID, to_ID, state, tot_vote, voting, vote_level, adj_max_state, 0); 
    return 0; 
}

int NODE::update_time(int current_time)
{
    duration = current_time; 
    return 0; 
}

