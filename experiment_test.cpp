/*
 * 按照时间轴进行仿真.
 *
 * */

#include "NODE.h"
#include <fstream>

extern vector < EVENT_REC > Q_contact_rec_time_based;       // 表示每一次连接
extern vector < NODE > Q_node_rec;                          // 表示每一个节点
int connection(EVENT_REC record);
ofstream fout("tmp_output");

bool cmp(const NODE & t1, const NODE & t2)
{
    return t1.dor_prob < t2.dor_prob;
}

int simulation_time_based()
{
    int current_time = 0;
    int update_time = INTERVAL_TIME;
    int sum_external_device_contact = 0;
    srand(time(NULL));

    for (int i = 0; ; update_time += INTERVAL_TIME)
    {
        // 处理连接
        for (; i < (int)Q_contact_rec_time_based.size() && Q_contact_rec_time_based[i].start_time <= update_time; i++)
        {
            int t = connection(Q_contact_rec_time_based[i]);

            if (t == -1)
            {
                sum_external_device_contact++;
            }
        }

        // update
        for (int j = 1; j < (int)Q_node_rec.size(); j++)
        {
            Q_node_rec[j].update(update_time);
        }

#if DEBUG
        cout << Q_node_rec[13].ID << " " << Q_node_rec[13].dor_prob << " " << Q_node_rec[13].adj_max_node << endl;
        fout << Q_node_rec[71].ID << " " << Q_node_rec[71].dor_prob << " " << Q_node_rec[71].adj_max_state <<
             " " << Q_node_rec[71].state << endl;
        /*
                if (Q_node_rec[71].dor_prob == 0)
                {
                    fout << i << " " << update_time << endl;
                }
        */
#endif
        current_time = update_time;

        // 跳出循环, 仿真结束.
        if (i == (int)Q_contact_rec_time_based.size())
        {
            break;
        }
    }

    sort(Q_node_rec.begin() + 1, Q_node_rec.end(), cmp);
    int sum = 0;

    for (int i = 1; i <= MAXN; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\n", Q_node_rec[i].ID, Q_node_rec[i].adj_max_node, Q_node_rec[i].state,
               Q_node_rec[i].adj_max_state, Q_node_rec[i].adj_tot_state);
/*
        if (Q_node_rec[i].dor_prob > 0.5000)
        {
            printf("%d\t%.4lf\n", Q_node_rec[i].ID, Q_node_rec[i].dor_prob);
            sum++;
        }
*/
#if DEBUG

        if (Q_node_rec[i].adj_max_node == Q_node_rec[i].ID)
            printf("%d\t%d\t%d\t%d\t%d\n", Q_node_rec[i].ID, Q_node_rec[i].adj_max_node, Q_node_rec[i].state,
                   Q_node_rec[i].adj_max_state, Q_node_rec[i].adj_tot_state);

#endif
    }

    cout << sum << endl;
    fout.close();
    return 0;
}

