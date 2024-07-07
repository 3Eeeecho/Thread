// 关于unique_lock要记住的几个要点如下：
// 1.类unique_lock是互斥锁所有权包装器。
// 2.它允许：
// a.可以有不同的锁定策略
// b.有时间限制的锁定尝试(try_lock_for、try_lock_until)
// c.递归锁定
// d.锁所有权的转让(移动而不是复制)
// e.条件变量(在即将到来的视频中看到这一点)

// 锁定策略
// 类型:                  效果:
// 1.defer_lock           不获得互斥锁的所有权。
// 2.try_to_lock          尝试在不阻塞的情况下获得互斥锁的所有权。
// 3.adopt_lock           假设调用线程已经拥有互斥锁的所有权。

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int buffer = 0;
mutex m;

// Example: 1
// auto task(const char* ThreadID, int loopFor)
// {
//     unique_lock<mutex> lock(m);
//     for (int i = 0; i < loopFor; ++i) {
//         ++buffer;
//         cout << format("ThreadID: {} {}\n", ThreadID, buffer);
//     }
// }

// Example: 2
auto task(const char* ThreadID, int loopFor)
{
    unique_lock<mutex> lock(m, std::defer_lock); // 不会尝试获取互斥锁
    lock.lock(); // 需要手动获取互斥锁
    for (int i = 0; i < loopFor; ++i) {
        ++buffer;
        cout << format("ThreadID: {} {}\n", ThreadID, buffer);
    }
    // 不需要unlock(),析构函数会自动释放互斥锁
}

int main()
{
    thread t1(task, "T1", 10);
    thread t2(task, "T2", 10);

    t1.join();
    t2.join();
    return 0;
}