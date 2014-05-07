/*
 * 从contact.dat中读入数据.
 * contact.dat记录了实验过程中, 任意一对节点间的接触.
 * 
 * ======================== 
 * Examples taken from contact.Exp1.dat (two first columns and first rows)
 * ======================== 
 * 1       8       121     121     1       0
 * 1       3       236     347     1       0
 * 1       4       236     347     1       0
 * 1       5       121     464     1       0
 * 1       8       585     585     2       464
 * ======================== 
 * ======================== 
 *
 * - 第一列记录主动连接的设备ID.
 * - 第二列记录被连接的设备ID.
 *
 * - 第三列和第四列分别记录了一次连接过程的开始时刻和结束时刻.
 *
 * - 第五列枚举了这一节点对每次连接编号.
 * - 第六行记录了这一节点对相邻两次连接的间隔时间.
 *
 * - 由于实验中, 任意节点的扫描过程都不是同步的, 所以任意一次连接都不是相互的, 即连接不是对称的.
 *
 * */

#define INPUT_DATA_FILE "./tmp/contacts.Exp6.dat"

// #define INPUT_DATA_FILE "c.dat"
#include "NODE.h"

extern vector < REC > Q_contact_rec_node_based[MAXN];  // 根据节点来记录连接
extern vector < REC > Q_contact_rec_time_based;        // 根据时间轴来记录连接

REC assign(int ID1, int ID2, int start_time, int end_time, int num, int interval)
{
    // 使用函数比使用构造函数要快一些?
    REC tmp; 
    tmp.ID1 = ID1; 
    tmp.ID2 = ID2; 
    tmp.start_time = start_time; 
    tmp.end_time = end_time; 
    tmp.num = num; 
    tmp.interval = interval; 
    return tmp; 
}

bool time_cmp(const REC& t1, const REC& t2)
{
    if(t1.start_time == t2.start_time)
    {
        return t1.ID1 < t2.ID2; 
    }else
    {
        return t1.start_time < t2.start_time; 
    }
}

int data_input()
{
    // 打开文件
    char * input_data_file = 0;
    if( ! input_data_file)
        input_data_file = (char *)INPUT_DATA_FILE; 
    freopen(input_data_file, "r", stdin); 

    int ID1;                    // 主动连接设备ID
    int ID2;                    // 被连接设备ID
    int start_time, end_time;   // 连接开始和结束时间
    int num;                    // 连接编号
    int interval;               // 连接时间间隔

    while(scanf("%d%d%d%d%d%d", &ID1, &ID2, &start_time, &end_time, &num, &interval) != EOF)
    {
        REC tmp = assign(ID1, ID2, start_time, end_time, num, interval); 
        Q_contact_rec_node_based[ID1].push_back(tmp); 
        Q_contact_rec_time_based.push_back(tmp); 
    }

    // 根据时间轴对Q_contact_rec_time_based进行排序
    sort(Q_contact_rec_time_based.begin(), Q_contact_rec_time_based.end(), time_cmp); 

//    for(int i = 0; i < (int)Q_contact_rec_time_based.size(); i++)
//    {
//        REC tmp = Q_contact_rec_time_based[i]; 
//        printf("%d\t%d\t%d\t%d\t%d\t%d\n", tmp.ID1, tmp.ID2, tmp.start_time, tmp.end_time, tmp.num, tmp.interval); 
//    }

    return 0;
}

