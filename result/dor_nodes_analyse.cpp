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
#include <fstream>
#define DEBUG 0

using namespace std;

/*
 * */

#define MAXN 4000
ifstream fin("dor_nodes_4.out");
ofstream fout("dor_nodes_4");
int main()
{
    fout << "DOR_THRESHOLD = 0.5\nINTERVAL_TIME = 100\nRESERVE_TIME = 1000\nCHECK_TIME_LEN = 1000" << endl;
    fout << "analyse_interval = 300" << endl << endl;
    int num;
    int k;
    int tot_dor[MAXN];
    memset(tot_dor, 0, sizeof(tot_dor));

    while (fin >> num)
    {
        for (;;)
        {
            fin >> k;
            tot_dor[num]++;

            if (!k)
            {
                break;
            }
        }
    }

    // interval = 300
    int interval_dor_nodes[100];
    int tot = 1;
    memset(interval_dor_nodes, 0, sizeof(interval_dor_nodes));

    for (int i = 1, j = 1; i <= num; i++, j++)
    {
        interval_dor_nodes[tot] += tot_dor[i];

        if (j == 300)
        {
            interval_dor_nodes[tot] /= j;
            j = 0;

            if (i < num)
            {
                tot++;
            }
        }
        else if (i == num)
        {
            interval_dor_nodes[tot] /= j;
        }
    }

    for (int i = 1; i <= tot; i++)
    {
        fout << interval_dor_nodes[i] << endl;
    }

    fin.close();
    fout.close();
    return 0;
}

