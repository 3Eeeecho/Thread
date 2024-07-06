// Mutex in C++
// 1. 避免竞争问题
// 2.

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int count = 1;
mutex m;

void increase()
{
    // 尝试获取锁,并对临界资源操作
    m.lock();
    ++::count;
    // 释放锁
    m.unlock();
}
int main()
{
    thread t1(increase);
    thread t2(increase);
    t1.join();
    t2.join();
    cout << "count: " << ::count;
    return 0;
}