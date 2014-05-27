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
 * */

int main()
{
    srand(time(NULL));
    double sum = 0;
    for (int i = 0; i < 100; i++)
    {
        double t = 1.0 * rand() / RAND_MAX;
        cout << t << endl;
        sum += t;
    }

    cout << "sum= " << sum / 100 << endl;
    return 0;
}

