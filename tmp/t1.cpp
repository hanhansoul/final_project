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

struct NODE
{
    NODE():a(0), b(0)
    {

    }

    NODE(int x, int y):a(x), b(y)
    {

    }
    int a; 
    int b; 
}; 

#define MP(a, b) make_pair(a, b)

vector < NODE > Q; 
map < int, int > M; 

int main()
{
    M.insert(MP(1, 10)); 
    M.insert(MP(4, 40)); 
    M.insert(MP(5, 50)); 
    M.insert(MP(9, 90)); 

    M[1] += 25; 
    cout << M[1] << endl; 

    return 0;
}

