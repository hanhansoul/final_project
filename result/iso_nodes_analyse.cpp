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

ifstream fin("iso_nodes_3.out");
ofstream fout("iso_nodes_3");
int main()
{
    fout << "DOR_THRESHOLD = 0.8\nINTERVAL_TIME = 100\nRESERVE_TIME = 1000\nCHECK_TIME_LEN = 1000" << endl;
    fout << "analyse_interval = 300" << endl << endl;
    int num;
    int k;
    int tot_contacts, tot_iso;
    int p, q;
    k = 11;
    tot_contacts = tot_iso = 0;

    while (fin >> num)
    {
        fin >> p >> q;
        tot_iso += p;
        tot_contacts += q;

        if (k == 300)
        {
            fout << tot_iso / k << "\t" << tot_contacts / k << endl;
            k = 0;
            tot_contacts = tot_iso = 0;
        }

        k++;
    }

    k--;
    fout << tot_iso / k << "\t" << tot_contacts / k << endl;
    fin.close();
    fout.close();
    return 0;
}

