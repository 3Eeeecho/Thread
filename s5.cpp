// std::mutex::try_lock() on Mutex in C++

// 1.尝试获取锁,返回ture或false
// 2.如果失败,立即返回,不会堵塞
// 3.如果已经拥有锁的线程尝试获取锁,这种行为是未定义的,会造成死锁

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int count = 0;
mutex mtx;

void increase100000Times()
{
    for (int i = 0; i < 100000; ++i) {
        if (mtx.try_lock()) {
            ::count++;
            mtx.unlock();
        }
    }
}

int main()
{
    thread t1(increase100000Times);
    thread t2(increase100000Times);
    t1.join();
    t2.join();
    cout << "count: " << ::count;
    return 0;
}