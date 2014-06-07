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
#define DEBUG 0

using namespace std;

#define MP(a, b) make_pair(a, b)

#define VOTE_K 3                // 投票种类, 0, 1, 2 ... 类票
#define MAXN 100                // iMote设备数, 节点编号从1开始
#define INTERVAL_TIME 100       // 投票淘汰间隔时间
#define RESERVE_TIME 1000       // 投票保留间隔时间
#define CHECK_TIME_LEN 10000    // check时间间隔
#define DOR_THRESHOLD 0.9       // 支配概率dor_prob阈值

struct EVENT_REC                // 记录连接事件
{
    EVENT_REC(): ID1(0), ID2(0), start_time(0), end_time(0), num(0), interval(0)
    {
    }

    EVENT_REC(int ID1, int ID2, int start_time, int end_time, int num, int interval)
    {
        this->ID1 = ID1;
        this->ID2 = ID2;
        this->start_time = start_time;
        this->end_time = end_time;
        this->num = num;
        this->interval = interval;
    }

    int ID1;                    // 主动连接设备ID
    int ID2;                    // 被连接设备ID
    int start_time, end_time;   // 连接开始和结束时间
    int num;                    // 连接编号
    int interval;               // 连接时间间隔
};

struct VOTE                     // 投票
{
    VOTE(): from_ID(0), to_ID(0), vote(0)
    {
    }

    VOTE(int from_ID, int to_ID, int vote)
    {
        this->from_ID = from_ID;
        this->to_ID = to_ID;
        this->vote = vote;
    }

    int vote;                   // 各类票数
    int from_ID;                // 投票节点ID
    int to_ID;                  // 被投票节点ID
};

struct MSG_REC                          // 记录相邻节点信息
{
    MSG_REC()
    {
    }

    MSG_REC(int ID,int state, int adj_max_state, int adj_max_node, int contacts, bool is_dominator, int time)
    {
        this->ID=ID;
        this->state = state;
        this->adj_max_state = adj_max_state;
        this->adj_max_node = adj_max_node;
        this->contacts = contacts;
        this->is_dominator = is_dominator;
        this->time = time;
    }

    int ID;
    int state;                          // 相邻节点B的state
    int adj_max_state;                  // 相邻节点B记录的相邻最大state节点C的state
    int adj_max_node;                   // 相邻节点B记录的相邻最大state节点C的ID
    int contacts;                       // 与C的连接次数
    bool is_dominator;                  // 是否为DOR
    int time;                           // 最近一次连接的时间
};

struct MSG                              // 一次连接传递的信息
{
    MSG(): ID1(0), ID2(0), msg_rec(), direct_vote(), indirect_vote()
    {
    }

    MSG(int ID1, int ID2, MSG_REC msg_rec, VOTE direct_vote, VOTE indirect_vote)
    {
        this->ID1 = ID1;
        this->ID2 = ID2;
        this->msg_rec = msg_rec;
        this->direct_vote = direct_vote;
        this->indirect_vote = indirect_vote;
    }

    int ID1;
    int ID2;
    MSG_REC msg_rec;                    // 节点B需要记录的信息
    VOTE direct_vote;                   // 该节点的直接投票
    VOTE indirect_vote;                 // 该节点的间接投票
};

#endif
