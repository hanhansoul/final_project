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

/*
 * 按照时间轴进行仿真.
 *
 * */

#include "STRUCT.h"

extern vector < REC > Q_contact_rec_time_based;     // 表示每一次连接
extern vector < NODE > Q_node_rec;                  // 表示每一个节点
int data_input(); 
int connection(); 

int simulation_time_based()
{
    for(int i = 0; i < (int)Q_contact_rec_time_based.size(); i++)
    {
        // connection 一次连接
        REC tmp = Q_contact_rec_time_based[i];  // tmp表示一次连接事件
        int ID1 = tmp.ID1;                      // 主动连接设备ID
        int ID2 = tmp.ID2;                      // 被连接设备ID
        int start_time = tmp.start_time;        // 连接开始时间
        int end_time = tmp.end_time;            // 连接结束时间
        int num = tmp.num;                      // 连接编号
        int interval = tmp.num;                 // 连接时间间隔
        
        // ID1 --> ID2
        NODE &node1= Q_node_rec[ID1];          // 连接节点对的节点信息
        NODE &node2 = Q_node_rec[ID2]; 

        // ID1
        // 更新 M_contacts_rec, 从Q_max_k_heap中选出最大的k组.
        int k = ++node1.M_contacts_rec[ID2];            // 增加一次连接计数
        bool vote_for_ID2 = false;                      // 是否向ID2投票
        int vote_level = 0;                             // 选票类型
        // 选出前k多连接次数的节点
        for(vector < pair < int, int > >::iterator it = node1.Q_max_k_heap.begin(), int i = 1; it != node1.Q_max_k_heap.end(); it++, i++)
            if(k >= it->second) 
            {
                node1.Q_max_k_heap.insert(it, MP(ID2, k));
                vote_for_ID2 = true; 
                vote_level = i; 
                break; 
            }
        if( ! vote_for_ID2) 
        {
            if(node1.Q_max_k_heap.size() < VOTE_K)
            {
                node1.Q_max_k_heap.push_back(MP(ID2, k)); 
                vote_level = node1.Q_max_k_heap.size(); 
                vote_for_ID2 = true; 
            }
        }else
        {
            if(node1.Q_max_k_heap.size() > VOTE_K)
                node1.Q_max_k_heap.pop_back(); 
        }

        // ID2
        if(vote_for_ID2)        // 如果ID1向ID2投票
        {
            // node2.Q_vote_rev *** 
            node2.Q_vote_rev.front().v[vote_level]++;
            // node2.tot_vote
            node2.tot_vote.v[vote_level]++; 
        }
        // *修改:判断是否在表中
        node2.M_adj_vote[ID1] = node1.tot_vote; 

        // 开始博弈, 确定状态.
        
    }
    return 0; 
}


