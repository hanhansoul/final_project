/*
 * 按照时间轴进行仿真.
 *
 * */

#include "NODE.h"

extern vector < REC > Q_contact_rec_time_based;     // 表示每一次连接
extern vector < NODE > Q_node_rec;                  // 表示每一个节点
int data_input(); 
int connection(REC record); 

int simulation_time_based()
{
    data_input(); 
    for(int i = 0; i < (int)Q_contact_rec_time_based.size(); i++)
    {
        connection(Q_contact_rec_time_based[i]); 
    }
    return 0; 
}


