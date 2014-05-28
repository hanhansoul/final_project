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
ofstream fout_1("tmp_output_1");

bool cmp(const NODE & t1, const NODE & t2)
{
    return t1.dor_prob < t2.dor_prob;
}

int simulation_time_based()
{
    int current_time = 0;
    int update_time = INTERVAL_TIME;
    int sum_external_device_contact = 0;
    //
    int pre_check_time = 0;                 // 确定check的时间长度
    int contact_rec_pos = 0;                // 确定check的连接事件
    //
    bool node_is_dor[MAXN + 10];
    bool tmp_node_is_dor[CHECK_TIME_LEN / INTERVAL_TIME + 1][MAXN + 10];
    int len = CHECK_TIME_LEN / INTERVAL_TIME + 1;
    int tmp_pos = 0;
    //
    bool contact_to_dor[MAXN + 10];
    memset(node_is_dor, false, sizeof(node_is_dor));
    memset(tmp_node_is_dor, false, sizeof(tmp_node_is_dor));
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
        tmp_pos = (tmp_pos + 1) % len;

        for (int j = 1; j < (int)Q_node_rec.size(); j++)
        {
            Q_node_rec[j].update(update_time);
            int id = Q_node_rec[j].ID;

            if (Q_node_rec[j].dor_prob >= DOR_THRESHOLD)
            {
                tmp_node_is_dor[tmp_pos][id] = true;
                tmp_node_is_dor[(tmp_pos + 1) % len][id] = false;
                fout_1 << id << " ";
            }
        }

        fout_1 << endl;

        for (int j = 1; j < (int)Q_node_rec.size(); j++)
        {
            int id = Q_node_rec[j].ID;

            for (int k = tmp_pos, l = 0; l < len; k = (k + 1) % len, l++)
            {
                node_is_dor[id] |= tmp_node_is_dor[k][id];
            }
        }

        // check
        int sum_iso_node = 0;
        int sum_event_rec = 0;

        if (current_time >= CHECK_TIME_LEN)
        {
            memset(contact_to_dor, false, sizeof(contact_to_dor));

            for (; contact_rec_pos <= i ; contact_rec_pos++)
            {
                int id1 = Q_contact_rec_time_based[contact_rec_pos].ID1;                       // 主动连接设备ID
                int id2 = Q_contact_rec_time_based[contact_rec_pos].ID2;                       // 主动连接设备ID

                if (id1 <= MAXN && id2 <= MAXN)
                {
                    sum_event_rec++;
                    contact_to_dor[id1] = node_is_dor[id2];
                }
            }

            for (int j = 1; j < (int)Q_node_rec.size(); j++)
            {
                if (!contact_to_dor[Q_node_rec[j].ID])
                {
                    sum_iso_node++;
                }
            }

            if (sum_event_rec > 100)
            {
                fout << sum_iso_node << " " << sum_event_rec << endl;
            }
        }

#if DEBUG
        cout << Q_node_rec[13].ID << " " << Q_node_rec[13].dor_prob << " " << Q_node_rec[13].adj_max_node << endl;
        fout << Q_node_rec[71].ID << " " << Q_node_rec[71].dor_prob << " " << Q_node_rec[71].adj_max_state <<
             " " << Q_node_rec[71].state << endl;

        if (Q_node_rec[71].dor_prob == 0)
        {
            fout << i << " " << update_time << endl;
        }

#endif
        current_time = update_time;

        // 跳出循环, 仿真结束.
        if (i == (int)Q_contact_rec_time_based.size())
        {
            break;
        }
    }

    sort(Q_node_rec.begin() + 1, Q_node_rec.end(), cmp);
    // int sum = 0;

    for (int i = 1; i <= MAXN; i++)
    {
        if (Q_node_rec[i].dor_prob > 0.9)
        {
            cout << Q_node_rec[i].ID << " " << Q_node_rec[i].dor_prob << endl;
            // printf("%d\t%d\t%d\t%d\t%d\n", Q_node_rec[i].ID, Q_node_rec[i].adj_max_node, Q_node_rec[i].state,
            // Q_node_rec[i].adj_max_state, Q_node_rec[i].adj_tot_state);
        }

#if DEBUG

        /*
                if (Q_node_rec[i].dor_prob > 0.5000)
                {
                    printf("%d\t%.4lf\n", Q_node_rec[i].ID, Q_node_rec[i].dor_prob);
                    sum++;
                }
        */

        if (Q_node_rec[i].adj_max_node == Q_node_rec[i].ID)
            printf("%d\t%d\t%d\t%d\t%d\n", Q_node_rec[i].ID, Q_node_rec[i].adj_max_node, Q_node_rec[i].state,
                   Q_node_rec[i].adj_max_state, Q_node_rec[i].adj_tot_state);

#endif
    }

    fout.close();
    return 0;
}

