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

    NODE(int ID):state(0), duration(0), adj_max_state(0), adj_max_state_node(0), tot_vote(), jump_vote()
    {
        this->ID = ID; 
        M_contacts_rec.clear(); 
        Q_max_k_heap.clear(); 
        tot_vote.clear(); 
        jump_vote.clear(); 
        Q_vote_rev = queue < VOTE >(); 
        M_adj_node.clear(); 
    }

    int ID;                             // 该节点ID
    int state;                          // 支配值.表明该节点为支配节点或被支配节点.
    int duration;                       // 节点启动后持续运作的时间 
    int adj_max_state;                  // 附近节点中的最大state值
    int adj_max_state_node;             // 附近节点中的最大state节点ID

    /* 
       根据M_contacts_rec中记录的节点间的连接次数, 利用max_k_heap计算出连接次数前k大的节点, 并进行投票.
       每发生一次连接, 便堆M_contacts_rec进行更新, 同时更新max_k_heap中的内容.
    */ 
    map < int, int > M_contacts_rec;            // 记录该节点与其他节点的连接次数. <i, j>与ID为i的节点连接了j次.
    vector < pair < int, int > > Q_max_k_heap;  // 保存前k大的数. < i, j > ===== < ID, 连接次数>

    /* 
       每一次连接, 被连接节点获得连接节点的各类票总数tot_vote, 节点状态state, 以及连接节点是否向被连接节点投票, 什么类型的票.
       然后节点通过获得的信息, 更新Q_vote_rev, M_adj_node. 
    */ 
    VOTE tot_vote;                      // 当前节点所获得的各类票总数.
    VOTE jump_vote;                     // 记录二段投票
    queue < VOTE > Q_vote_rev;          // 节点获得投票, 分时间段间, 将该段时间内获得的票加入队首, 将过期的票从队尾去除.
    map < int, MSG_REC > M_adj_node;    // 附近节点状态.该信息不是实时的.

    // functions
    int vote_expire(int current_time); 
    int be_connected(int from_ID, MSG msg); 
    MSG connect(int ID); 
    int update(int current_time); 
    int update_time(int current_time); 
/* 
    bool is_dominator(int state);       // 判断状态state是否为支配节点
    VOTE last_tot_vote;                 // 上一次更新时的票数, 用于与当前票数进行比较
    int adj_dor_num;                    // 附近支配节点数
    NODE():state(0), duration(0), voting(false), vote_level(0), ID(0) 
    {
        while( ! Q_vote_rev.empty()) Q_vote_rev.pop(); 
        Q_max_k_heap.clear(); 
        M_contacts_rec.clear(); 
        M_adj_node.clear(); 
    }
*/ 
}; 

extern vector < EVENT_REC > Q_contact_rec_node_based[MAXN];     // 根据节点来记录连接
extern vector < EVENT_REC > Q_contact_rec_time_based;           // 根据时间轴来记录连接
extern vector < NODE > Q_node_rec;                              // 表示每一个节点

#endif
