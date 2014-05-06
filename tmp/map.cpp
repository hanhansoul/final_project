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

/*
 * */

priority_queue< pair<int, int>, vector< pair<int, int> >, less< pair<int, int> > > Q; 
int main()
{
    Q.push(MP(1, 2)); 
    Q.push(MP(3, 4)); 
    Q.push(MP(5, 2)); 
    Q.push(MP(9, 2)); 

    while( ! Q.empty())
    {
        cout << Q.top().first << " == " << Q.top().second << endl; 
        Q.pop(); 
    }
    return 0;
}

