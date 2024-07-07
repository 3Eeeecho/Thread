// Recursive Mutex in C++11
// 0.它与互斥锁相同，但是，同一线程可以使用recursive_mutex多次锁定一个互斥锁。
// 1.如果线程T1首先在递归互斥锁m1上调用 lock/try_lock，则m1现在被T1锁定
// 由于T1在递归中运行，因此T 可以调用任意次数的 lock/try_lock，没有问题。
// 2.但是，如果T1在互斥锁m1上获得了10次锁定/try_lock，则线程T1将不得不解锁
// 它10次，否则没有其他线程能够锁定互斥锁 M1。
// 这意味着recursive_mutex会计算它被锁定的次数，以便它应该被解锁多少次。
// 3.我们可以锁定recursive_mutex多少次没有定义，但何时到达该次数以及我们是否在调用
// lock()它将返回std::system_error 或者如果我们调用 try_lock()，那么它将返回 false。

// Note：
// 0.它类似于互斥锁，但具有额外的功能，可以由同一线程多次锁定。
// 1.如果我们可以避免recursive_mutex那么我们应该这样做，因为它会给系统带来开销。
// 2.它也可以循环使用。

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int buffer = 0;
recursive_mutex m;

auto recursion(char c, int loopFor)
{
    if (loopFor < 0) {
        return;
    }

    m.lock();
    cout << format("ThreadID: {} {}\n", c, buffer++);
    recursion(c, --loopFor);
    m.unlock();
    cout << format("unlocked by {}\n", c);
}

int main()
{
    thread t1(recursion, '1', 10);
    thread t2(recursion, '2', 10);

    t1.join();
    t2.join();
    return 0;
}