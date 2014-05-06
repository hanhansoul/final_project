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

vector < int > Q; 
int main()
{
    Q.push_back(4); 
    Q.push_back(3); 
    Q.push_back(2); 
    Q.push_back(1); 

    for(int i = 0; i < (int)Q.size(); i++)
        cout << Q[i] << endl; 
    cout << endl; 

    int k = 0; 
    bool flag = false; 
    for(vector < int >::iterator it = Q.begin(); it != Q.end(); it++)
    {
        if(k >= *it)
        {
            Q.insert(it, k); 
            flag = true; 
            break; 
        }
    }

    for(int i = 0; i < (int)Q.size(); i++)
        cout << Q[i] << endl; 
    cout << endl; 

    if( ! flag)
    {
        if(Q.size() < 4) 
        {
            Q.push_back(k); 
            flag = true; 
        }
    }else
    {
        if(Q.size() > 4)
            Q.pop_back(); 
    }

    cout << flag << endl << endl; 

    for(int i = 0; i < (int)Q.size(); i++)
        cout << Q[i] << endl; 
    return 0;
}

