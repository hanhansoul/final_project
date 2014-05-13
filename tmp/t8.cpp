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
struct A
{
    A():s(10)
    {
        for(int i = 0; i < 4; i++)
            v[i] = 0; 
    }
    int v[4]; 
    int s; 
}; 

struct B
{
    B():a(1)
    {

    }
    int a; 
    A cls; 
}; 

int main()
{
    B Q; 
    for(int i = 0; i < 4; i++)
    {
        cout << Q.cls.v[i] <<endl; 
    }
    cout << Q.cls.s << endl; 
    return 0;
}

