/*
 * 按照时间轴进行仿真.
 *
 * */

#include "NODE.h"
#include <fstream>

extern vector < EVENT_REC > Q_contact_rec_time_based;       // 表示每一次连接
extern vector < NODE > Q_node_rec;                          // 表示每一个节点
int connection(EVENT_REC record);
ofstream fout_iso("iso_nodes.out");
ofstream fout_dor("dor_nodes.out");

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
    bool Q[MAXN + 10], P[MAXN + 10];
    memset(tmp_node_is_dor, false, sizeof(tmp_node_is_dor));
    srand(time(NULL));

    for (int i = 0, ll = 1; ; update_time += INTERVAL_TIME, ll++)
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
        fout_dor << ll << "\t";
        int sum_dor = 0;

        for (int j = 1; j < (int)Q_node_rec.size(); j++)
        {
            Q_node_rec[j].update(update_time);
            int id = Q_node_rec[j].ID;

            if (Q_node_rec[j].dor_prob >= DOR_THRESHOLD)
            {
                tmp_node_is_dor[tmp_pos][id] = true;
                sum_dor++;
                fout_dor << id << " ";
            }

            tmp_node_is_dor[(tmp_pos + 1) % len][id] = false;
        }

        fout_dor << 0 << endl;
        memset(node_is_dor, false, sizeof(node_is_dor));

        for (int j = 1; j < (int)Q_node_rec.size(); j++)
        {
            int id = Q_node_rec[j].ID;

            for (int k = tmp_pos, l = 0; l < len; k = (k - 1 + len) % len, l++)
            {
                node_is_dor[id] |= tmp_node_is_dor[k][id];
            }
        }

        // check
        // 查询该时间段有多少节点未被支配, 2跳支配.
        int sum_iso_node = 0;
        int sum_event_rec = 0;

        if (current_time >= CHECK_TIME_LEN)
        {
            memset(contact_to_dor, false, sizeof(contact_to_dor));
            memset(Q, false, sizeof(Q));
            memset(P, false, sizeof(P));

            /*
            // 1跳支配
            for (; contact_rec_pos <= i ; contact_rec_pos++)
            {
                int id1 = Q_contact_rec_time_based[contact_rec_pos].ID1;            // 主动连接设备ID
                int id2 = Q_contact_rec_time_based[contact_rec_pos].ID2;            // 主动连接设备ID

                if (id1 <= MAXN && id2 <= MAXN)
                {
                    sum_event_rec++;
                    contact_to_dor[id1] = node_is_dor[id2];
                    Q[id1]=true;
                }
            }
            */
            // 2跳支配
            for (int p = contact_rec_pos; p <= i ; p++)
            {
                int id1 = Q_contact_rec_time_based[p].ID1;                          // 主动连接设备ID
                int id2 = Q_contact_rec_time_based[p].ID2;                          // 主动连接设备ID

                if (id1 <= MAXN && id2 <= MAXN)
                {
                    sum_event_rec++;
                    contact_to_dor[id1] = node_is_dor[id2];
                    Q[id1] = true;
                    P[id2] = true;
                }
            }

            for (int j = 1; j < (int)Q_node_rec.size(); j++)
            {
                if (contact_to_dor[j])
                {
                    node_is_dor[j] = true;
                }
            }

            for (; contact_rec_pos <= i ; contact_rec_pos++)
            {
                int id1 = Q_contact_rec_time_based[contact_rec_pos].ID1;            // 主动连接设备ID
                int id2 = Q_contact_rec_time_based[contact_rec_pos].ID2;            // 主动连接设备ID

                if (id1 <= MAXN && id2 <= MAXN)
                {
                    contact_to_dor[id1] = node_is_dor[id2];
                }
            }

            for (int j = 1; j < (int)Q_node_rec.size(); j++)
            {
                if (!node_is_dor[Q_node_rec[j].ID] && !contact_to_dor[Q_node_rec[j].ID])
                {
                    sum_iso_node++;
                }
            }

            fout_iso << ll << "\t" << sum_iso_node << " " << sum_event_rec << endl;
        }

        // check end
        current_time = update_time;

        // 跳出循环, 仿真结束.
        if (i == (int)Q_contact_rec_time_based.size())
        {
            break;
        }
    }

    /*
        sort(Q_node_rec.begin() + 1, Q_node_rec.end(), cmp);

        for (int i = 1; i <= MAXN; i++)
        {
            cout << Q_node_rec[i].ID << " " << Q_node_rec[i].dor_prob << " "
                 << Q_node_rec[i].state << " " << Q_node_rec[i].adj_max_node << endl;
        }
    */
    fout_iso.close();
    fout_dor.close();
    return 0;
}

