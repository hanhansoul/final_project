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
#define MP(a, b) make_pair(a, b)

using namespace std;

queue < pair<int, int> > Q;
int main()
{
    for (int i = 0; i < 10; i++)
    {
        Q.push(MP(i, 1));
    }

    for (int i = 0; i < 10; i++)
    {
        cout << Q.back().second << endl;
        Q.back().second += 10;
    }

    return 0;
}

