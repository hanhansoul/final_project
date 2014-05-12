
/*
 * 处理每一次连接事件
 *
 * */

#include "NODE.h"

extern vector < NODE > Q_node_rec;              // 表示每一个节点

int connection(EVENT_REC record)
{
    // connection 一次连接
    int ID1 = record.ID1;                       // 主动连接设备ID
    int ID2 = record.ID2;                       // 被连接设备ID
    int start_time = record.start_time;         // 连接开始时间
    int end_time = record.end_time;             // 连接结束时间
    int num = record.num;                       // 连接编号
    int interval = record.num;                  // 连接时间间隔
        
    if(ID1 > 100 || ID2 > 100) 
    {
        printf("external device.\n"); 
        return -1; 
    }

    // update
    Q_node_rec[ID1].update_time(start_time); 
    Q_node_rec[ID2].update_time(start_time); 

    MSG msg; 
    // ID1 --> ID2
    // ID1
    msg = Q_node_rec[ID1].connect(ID2); 
    // ID2 
    Q_node_rec[ID2].be_connected(ID1, msg); 

    return 0; 
}

