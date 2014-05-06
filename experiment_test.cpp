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

extern vector < REC > Q_contact_rec_time_based; 
extern vector < NODE > Q_node_rec;                     // 表示每一个节点
int data_input(); 


int simulation_time_based()
{
    for(int i = 0; i < (int)Q_contact_rec_time_based.size(); i++)
    {
        REC tmp = Q_contact_rec_time_based[i];  // tmp表示一次连接事件
        int ID1 = tmp.ID1;                      // 主动连接设备ID
        int ID2 = tmp.ID2;                      // 被连接设备ID
        int start_time = tmp.start_time;        // 连接开始时间
        int end_time = tmp.end_time;            // 连接结束时间
        int num = tmp.num;                      // 连接编号
        int interval = tmp.num;                 // 连接时间间隔
        
    }
    return 0; 
}

