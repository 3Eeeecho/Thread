// Timed Mutex in C++11
// 会在一段时间尝试获取锁,直到超时或成功获取锁

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
int count = 0;
timed_mutex mtx;

// try_lock_for() 尝试锁互斥。阻塞直到经过指定的 timeout_duration 或得到锁，取决于何者先到来 (时间段)
// auto increment(int i)
// {
//     if (mtx.try_lock_for(std::chrono::seconds(1))) {
//         ++::count;
//         cout << format("Thread {} entered.\n", i);
//         this_thread::sleep_for(std::chrono::seconds(2));
//         mtx.unlock();
//     } else {
//         cout << format("Thread {} failed.\n", i);
//     }
// }

// try_lock_until() 阻塞直至抵达指定的 timeout_time 或得到锁，取决于何者先到来 (时间点)
auto increment(int i)
{
    auto now = std::chrono::steady_clock::now();
    if (mtx.try_lock_until(now + std::chrono::seconds(1))) {
        ++::count;
        cout << format("Thread {} entered.\n", i);
        this_thread::sleep_for(std::chrono::seconds(2));
        mtx.unlock();
    } else {
        cout << format("Thread {} failed.\n", i);
    }
}

int main()
{
    thread t1(increment, 1);
    thread t2(increment, 2);

    t1.join();
    t2.join();
    return 0;
}