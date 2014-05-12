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

#define MP(a, b) make_pair(a, b)
vector < pair < int, int > > Q;  // 保存前k大的数. < i, j > ===== < ID, 连接次数>
int main()
{
    for(int i = 0; i < 10; i++)
        Q.push_back(MP(i, i * i)); 
    vector < pair < int, int > >::iterator pos; 
    pos = lower_bound(Q_max_k_heap.begin(), Q_max_k_heap.end(), to_ID); 
    
    return 0;
}

