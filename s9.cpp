// 关于lock_guard，要记住的几点如下
// 0.是一种非常轻量级的包装器，用于在作用域内拥有互斥锁
// 1.在创建lock_guard对象的那一刻获得互斥锁
// 2.在超出作用域时调用析构函数,自动移除锁
// 3.无法明确解锁lock_guard
// 4.不能复制lock_guard

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int buffer = 0;
mutex m;

auto task(const char* ThreadID, int loopFor)
{
    lock_guard<mutex> lock(m);
    for (int i = 0; i < loopFor; ++i) {
        ++buffer;
        cout << format("ThreadID: {} {}\n", ThreadID, buffer);
    }
}
int main()
{
    thread t1(task, "T1", 10);
    thread t2(task, "T2", 10);

    t1.join();
    t2.join();
    return 0;
}