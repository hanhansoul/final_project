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

#include "STRUCT.h"

using namespace std;

/*
 * 初始化
 *
 * */

vector < REC > Q_contact_rec_node_based[MAXN];      // 根据节点来记录连接
vector < REC > Q_contact_rec_time_based;            // 根据时间轴来记录连接
vector < NODE > Q_node_rec;                         // 表示每一个节点

int init()
{
    for(int i = 0; i < MAXN; i++)
        Q_contact_rec_node_based[i].clear(); 
    Q_contact_rec_time_based.clear(); 
    Q_node_rec.clear(); 
    return 0; 
}


