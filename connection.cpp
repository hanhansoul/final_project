
/*
 * 处理每一次连接事件
 *
 * */

#include "NODE.h"

extern vector < NODE > Q_node_rec;              // 表示每一个节点

int connection(REC record)
{
    // connection 一次连接
    int ID1 = record.ID1;                       // 主动连接设备ID
    int ID2 = record.ID2;                       // 被连接设备ID
    int start_time = record.start_time;         // 连接开始时间
    int end_time = record.end_time;             // 连接结束时间
    int num = record.num;                       // 连接编号
    int interval = record.num;                  // 连接时间间隔
        
    // ID1 --> ID2
    NODE &node1 = Q_node_rec[ID1];               // 连接节点对的节点信息
    NODE &node2 = Q_node_rec[ID2]; 
    MSG msg; 

    // ID1
    node1.vote_expire(); 
    node1.connect(ID2); 
    node1.vote_for(ID2, msg); 
    node1.game(); 

    // ID2 
    node2.vote_expire(); 
    node2.be_voted(ID1, msg); 
    node2.game(); 

    return 0; 
}

