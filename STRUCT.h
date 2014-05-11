#ifndef STRUCT_H_H
#define STRUCT_H_H

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std; 

#define MP(a, b) make_pair(a, b)

#define VOTE_K 3                // 投票种类, 0, 1, 2 ... 类票
#define MAXN 100                // iMote设备数, 节点编号从1开始
#define INTERVAL_TIME 100       // 投票淘汰间隔时间
#define RESERVE_TIME 1000       // 投票保留间隔时间

struct EVENT_REC                      // 记录连接事件
{
    EVENT_REC():ID1(0), ID2(0), start_time(0), end_time(0), num(0), interval(0)
    {

    }

    int ID1;                    // 主动连接设备ID
    int ID2;                    // 被连接设备ID
    int start_time, end_time;   // 连接开始和结束时间
    int num;                    // 连接编号
    int interval;               // 连接时间间隔
}; 

struct VOTE{                    // 记录获得的投票
    VOTE():time(0)
    {
        memset(0, sizeof(v), 0); 
    }
    VOTE(int t):time(t)
    {
        memset(0, sizeof(v), 0); 
    }
    int v[VOTE_K];              // 各类票数
    int time;                   // 该轮投票时间, tot_vote中无用
}; 

struct MSG_REC
{
    MSG_REC()
    {

    }
    MSG_REC(int state, VOTE vote)
    {
        this->vote = vote; 
        this->state = state; 
    }
    VOTE vote; 
    int state; 
}; 

struct MSG                              // 一次连接传递的信息
{
    MSG()
    {

    }
    MSG(int ID1, int ID2, int state, VOTE vote, bool voting, int vote_level)
    {
        this->ID1 = ID; 
        this->ID2 = to_ID;  
        this->state = state; 
        this->vote = tot_vote; 
        this->voting = voting; 
        this->vote_level = vote_level; 
    }
    int ID1; 
    int ID2; 
    int state;                          // 主动连接节点的状态
    VOTE vote;                          // 主动连接节点票数
    bool voting;                        // 是否投票
    int vote_level;                     // 投票种类
}; 

#endif
