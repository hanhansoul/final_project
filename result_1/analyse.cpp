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

int main(int argc, char * args[])
{
    if (argc != 3)
    {
        cout << "./analyse <input> <output>" << endl;
        return -1;
    }

    ifstream fin(args[1]);
    ofstream fout(args[2]);
    int check_time_len;
    double dor_threshold;
    fin >> check_time_len >> dor_threshold;
    fout << "DOR_THRESHOLD = " << 0.9 << endl;
    fout << "CHECK_TIME_LEN = " << check_time_len << endl;
    fout << "INTERVAL_TIME = 100\nRESERVE_TIME = 1000" << endl;
    fout << "analyse_interval = 300" << endl << endl;
    int num;
    int k;
    int tot_contacts, tot_iso;
    int p, q;
    k = tot_contacts = tot_iso = 0;

    while (fin >> num)
    {
        fin >> p >> q;
        tot_iso += p;
        tot_contacts += q;
        k++;

        if (k == 300)
        {
            fout << tot_iso / k << "\t" << tot_contacts / k << endl;
            k = tot_contacts = tot_iso = 0;
        }
    }

    if (k)
    {
        fout << tot_iso / k << "\t" << tot_contacts / k << endl;
    }

    fin.close();
    fout.close();
    return 0;
}

