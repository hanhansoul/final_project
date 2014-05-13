#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#define DEBUG 0

using namespace std;

/*
 * 统计table.Exp.dat文件
 * */

#define MIN_CONTACTS_FREQUENCY 50
struct REC
{
    REC()
    {

    }
    REC(int a, int b, int c, int d):ID(a), cls(b), incidence(c), tot_contact(d), tot_time(0)
    {
        tot_contact_node = 0; 
        contacts.clear(); 
        time.clear(); 
    }
    int ID;
    int cls; 
    int incidence; 
    int tot_contact; 
    int tot_time; 
    vector < int > contacts; 
    vector < int > time; 

    int tot_contact_node;       // 该节点一共接触了多少个节点
}; 
vector < REC > R; 

bool cmp(const REC &t1, const REC &t2)
{
    return t1.tot_contact_node > t2.tot_contact_node; 
}

int main()
{
    FILE *fin = fopen("table.Exp6.dat", "r"); 
    FILE *fout = fopen("output", "w"); 
    int ID, cls, incidence, tot_contact, tot_time; 
    R.push_back(REC()); 
    while(fscanf(fin, "%d%d%d%d", &ID, &cls, &incidence, &tot_contact) != EOF)
    {
        REC t(ID, cls, incidence, tot_contact); 

        t.contacts.push_back(0); 
        t.time.push_back(0); 
        
        for(int i = 1, c; i <= 99; i++)
        {
            fscanf(fin, "%d", &c); 
            t.contacts.push_back(c); 
            if(c >= MIN_CONTACTS_FREQUENCY)
                t.tot_contact_node++; 
        }

        fscanf(fin, "%d", &tot_time); 
        t.tot_time = tot_time; 
        for(int i = 1, c; i <= 99; i++)
        {
            fscanf(fin, "%d", &c); 
            t.time.push_back(c); 
        }
        R.push_back(t); 
    }

    sort(R.begin() + 1, R.end(), cmp); 
    for(int i = 1; i < (int)R.size(); i++)
    {
        fprintf(fout, "%d\t%d\n", R[i].ID, R[i].tot_contact_node); 
    }

    fclose(fin); 
    fclose(fout); 
    return 0;
}

