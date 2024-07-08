// 语法如下:
// std::lock(m1, m2, m3, m4...mn);
// 1.通过对每个参数调用lock()、try_lock()或unlock()序列来锁定所有参数
// 2.锁定顺序未定义（它将尝试以任何顺序锁定提供的互斥体并确保不存在死锁）
// 3.这是一个阻塞调用

// [示例:0] -- 没有死锁。
//     线程 1 线程 2
//     std::lock(m1,m2);           std::lock(m1,m2);

// [示例:1] -- 没有死锁。

//     线程 1 线程 2
//     std::lock(m1, m2);          std::lock(m2, m1);

// [示例:2] -- 没有死锁。

//     线程 1 线程 2
//     std::lock(m1, m2, m3, m4);  std::lock(m3, m4);
//                                 std::lock(m1, m2);

// [示例:3] -- 是的,下面的情况可能会出现死锁。

//     线程 1 线程 2
//     std::lock(m1,m2);           std::lock(m3,m4);
//     std::lock(m3,m4);           std::lock(m1,m2);

#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

mutex m1, m2;

auto task_a()
{
    while (true) {
        lock(m1, m2);
        cout << "task a\n";
        m1.unlock();
        m2.unlock();
    }
}

auto task_b()
{
    while (true) {
        lock(m2, m1);
        cout << "task b\n";
        m1.unlock();
        m2.unlock();
    }
}

int main()
{
    thread t1(task_a);
    thread t2(task_b);

    t1.join();
    t2.join();
    return 0;
}