#include "STRUCT.h"

#ifndef NODE_H_H
#define NODE_H_H

struct NODE                     // NODE表示一个节点中包含的数据结构和内容.
{ 
    NODE():state(0), duration(0), voting(false), vote_level(0), ID(0) 
    {
        while( ! Q_vote_rev.empty()) Q_vote_rev.pop(); 
        Q_max_k_heap.clear(); 
        M_contacts_rec.clear(); 
        M_adj_vote.clear(); 
    }

    /* 
       节点状态
    */ 
    int ID;                             // 该节点ID
    int state;                          // 状态.表明该节点为支配节点或被支配节点.用概率表示?
    int duration;                       // 节点启动后持续运作的时间 

    /* 
       根据M_contacts_rec中记录的节点间的连接次数, 利用max_k_heap计算出连接次数前k大的节点, 并进行投票.
       每发生一次连接, 便堆M_contacts_rec进行更新, 同时更新max_k_heap中的内容.
    */ 
    map < int, int > M_contacts_rec;            // 记录该节点与其他节点的连接次数. <i, j>与ID为i的节点连接了j次.
    vector < pair < int, int > > Q_max_k_heap;  // 保存前k大的数. 
//    priority_queue< pair<int, int>, vector< pair<int, int> >, less< pair<int, int> > > Q_max_k_heap; 
//                                              // 大顶堆, 取出前k大的数. ** priority_queue不提供遍历

    /* 
       每一次连接, 被连接节点获得连接节点的各类票总数tot_vote, 节点状态state, 以及连接节点是否向被连接节点投票, 什么类型的票.
       然后节点通过获得的信息, 更新Q_vote_rev, M_adj_vote. 
       最后根据Q_vote_rev[i](i为连接节点ID)和被连接节点的tot_vote进行博弈, 确定状态.
    */ 
    VOTE tot_vote;                      // 当前节点所获得的各类票总数.
    queue < VOTE > Q_vote_rev;          // 节点获得投票, 分时间段间, 将该段时间内获得的票加入队首, 将过期的票从队尾去除.
    map < int, VOTE > M_adj_vote;       // 附近节点获得的投票数.根据附近节点获得投票进行博弈.该信息不是实时的.

    // vote 处理向其他节点投票
    bool voting; 
    int vote_level; 

    // functions
    int vote_expire(); 
    int vote_for(int to_ID, MSG &msg); 
    int be_voted(int from_ID, MSG msg); 
    int connect(int ID); 
    int game(); 

}; 

extern vector < REC > Q_contact_rec_node_based[MAXN];      // 根据节点来记录连接
extern vector < REC > Q_contact_rec_time_based;            // 根据时间轴来记录连接
extern vector < NODE > Q_node_rec;                         // 表示每一个节点

#endif
