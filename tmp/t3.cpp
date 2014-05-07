// queue::front
#include <iostream>       // std::cout
#include <queue>          // std::queue

using namespace std; 

struct NODE
{
    int v[4]; 
}; 

int main ()
{
  queue<NODE> myqueue;

  myqueue.push(NODE());
  myqueue.push(NODE());

  std::cout << "myqueue.front() is now " << myqueue.front().v[0] << '\n';

  myqueue.front().v[0]++; 
  // myqueue.front() -= myqueue.back();    // 77-16=61

  std::cout << "myqueue.front() is now " << myqueue.front().v[0] << '\n';

  return 0;
}
