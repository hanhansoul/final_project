
/*
 * 初始化
 *
 * */

#include "NODE.h"

vector < REC > Q_contact_rec_node_based[MAXN];      // 根据节点来记录连接
vector < REC > Q_contact_rec_time_based;            // 根据时间轴来记录连接
vector < NODE > Q_node_rec;                         // 表示每一个节点

int init()
{
    for(int i = 1; i <= MAXN; i++)
        Q_contact_rec_node_based[i].clear(); 
    Q_contact_rec_time_based.clear(); 
    Q_node_rec.clear(); 

    // 初始化100个iMote节点信息
    for(int i = 1; i <= MAXN; i++)
        Q_node_rec.push_back(NODE()); 

    return 0; 
}

