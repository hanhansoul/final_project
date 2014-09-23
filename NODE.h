#include "STRUCT.h"

#ifndef NODE_H_H
#define NODE_H_H

struct NODE                     // NODE表示一个节点中包含的数据结构和内容.
{
    /*
       节点状态
    */
    NODE()
    {
    }

    NODE(int ID): ID(ID), state(0), duration(0), adj_max_state(0), adj_max_node(ID), contacts(0), adj_tot_state(0)
    {
        Q_max_k_heap.clear();
        M_adj_node.clear();
        M_contacts_rec.clear();
        M_indirect_vote.clear();
        dor_prob = 0.5;
        is_dominator = false;
        Q_vote_rev = queue < pair<int, int> >();
        tmp_adj_max_state = 0;
        tmp_adj_max_node = ID;
        contacts = 0;
        tmp_contacts = 0;
        //
        distance = ID == SOURCE ? distance : 0;
        tmp_distance = ID == SOURCE ? tmp_distance : 0;
        carry_data = false;
        step=0;
    }

    int ID;                             // 该节点ID
    int state;                          // 支配值.表明该节点为支配节点或被支配节点.
    int duration;                       // 节点启动后持续运作的时间
    int adj_max_state;                  // 附近节点中的最大state值
    int adj_max_node;                   // 附近节点中的最大state节点ID
    int contacts;
    int tmp_adj_max_state;
    int tmp_adj_max_node;
    int tmp_contacts;
    bool is_dominator;                  // 根据dor_prob随机决定是否为dor

    // push_data
    int distance;                       // 到节点1的最短距离
    int tmp_distance;
    bool carry_data;                    // 是否携带数据
    int step;
    //

    int adj_tot_state;                  // 附近节点的state之和, 通过M_adj_node更新
    double dor_prob;                    // DOR的概率

    map < int, int > M_contacts_rec;            // 记录该节点与其他节点的连接次数. <i, j>与ID为i的节点连接了j次.
    vector < pair < int, int > > Q_max_k_heap;  // 保存前k大的数. < i, j > ===== < ID, 连接次数>

    // VOTE tot_vote;                           // 当前节点所获得的各类票总数.
    queue < pair<int, int> > Q_vote_rev;        // 节点获得投票, 分时段间, 将时段内获得的票加入队首, 将过期的票从队尾去除. <time, vote>
    map < int, int > M_indirect_vote;           // 记录二段投票, < ID, value >
    map < int, MSG_REC > M_adj_node;            // 附近节点信息.该信息不是实时的.

    // functions
    int be_connected(MSG msg);
    MSG connect(int ID);
    int update_time(int current_time);
    int update(int current_time);
    vector < pair < int, int > >::iterator in_Q_heap(int ID);
    int Q_heap_insert(pair < int, int > node);

    bool random_dor(double prob);
    int vote_expire(int current_time);
    // bool cmp(const pair<int, int> &t1, const pair<int, int> &t2);
};

extern vector < EVENT_REC > Q_contact_rec_node_based[MAXN];     // 根据节点来记录连接
extern vector < EVENT_REC > Q_contact_rec_time_based;           // 根据时间轴来记录连接
extern vector < NODE > Q_node_rec;                              // 表示每一个节点
extern int Q_vote[VOTE_K];
extern int data_event;

#endif
