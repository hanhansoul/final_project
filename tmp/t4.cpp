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

int ext; 

struct A
{
    int v[10]; 
    int fun()
    {
        ext++; 
        return ext; 
    }
}; 

int main()
{
    A a, b; 
    for(int i = 0; i < 10; i++)
        a.v[i] = i; 
    b = a; 
    for(int i = 0; i < 10; i++)
        cout << b.v[i] << endl; 
    a.v[1] = 100; 
    cout << endl; 
    for(int i = 0; i < 10; i++)
        cout << a.v[i] << endl; 
    return 0;
}

