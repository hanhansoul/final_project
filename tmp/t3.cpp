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
  queue<int> myqueue;

  myqueue.push(10);
  myqueue.push(20);

  std::cout << "myqueue.front() is now " << myqueue.front() << '\n';

  myqueue.front()++; 
  // myqueue.front() -= myqueue.back();    // 77-16=61

  std::cout << "myqueue.front() is now " << myqueue.front() << '\n';

  return 0;
}
