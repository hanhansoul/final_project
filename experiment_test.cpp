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
    int current_time = 0; 
    int update_time = INTERVAL_TIME; 

//    for(int i = 0; i < (int)Q_contact_rec_time_based.size(); i++)
//    {
//        connection(Q_contact_rec_time_based[i]); 
//    }

    for(int i = 0; ; update_time += INTERVAL_TIME)
    {
        // 处理连接
        for( ; i < (int)Q_contact_rec_time_based.size() && Q_contact_rec_time_based[i].start_time <= update_time; i++)
        {
            connection(Q_contact_rec_time_based[i]); 
        }

        // update
        for(int j = 0; j < (int)Q_node_rec.size(); j++)
        {
            Q_node_rec[j].update(update_time); 
        }
        current_time = update_time; 
        
        // 跳出循环, 仿真结束.
        if(i == (int)Q_contact_rec_time_based.size())
            break; 

    }
    return 0; 
}


