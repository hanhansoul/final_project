/*
 * 按照时间轴进行仿真.
 *
 * */

#include "NODE.h"

extern vector < REC > Q_contact_rec_time_based;     // 表示每一次连接
extern vector < NODE > Q_node_rec;                  // 表示每一个节点
int connection(REC record); 

int simulation_time_based()
{
    int last_time = 0;      // 上次更新的时间
    int current_time = 0;   // 当前时间
    for(int i = 0; i < (int)Q_contact_rec_time_based.size(); i++)
    {
        // update投票
        if(Q_contact_rec_time_based[i].start_time - last_time >= INTERVAL_TIME)
        {
            current_time = last_time + INTERVAL_TIME; 
            for(int j = 0; j < (int)Q_node_rec.size(); j++)
                Q_node_rec[j].update(current_time); 
            last_time = current_time; 
        }
        current_time = Q_contact_rec_time_based[i].start_time; 

        // connection处理一次连接
        connection(Q_contact_rec_time_based[i]); 
    }
    return 0; 
}


