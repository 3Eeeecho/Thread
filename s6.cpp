// 0. std::try_lock（m1,m2...mn） 尝试按给定顺序逐个锁定其中传递的所有互斥锁
// 1. 成功后，此函数返回 -1，否则它将返回无法锁定的从 0 开始的互斥索引号
// 2. 如果它未能锁定任何互斥锁，那么它将释放之前锁定的所有互斥锁
// 3. 如果对try_lock()的调用导致异常，则在重新抛出之前会为任何锁定的对象解锁

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int X = 0, Y = 0;
mutex m1, m2;

auto doSomeWork(int second) { this_thread::sleep_for(chrono::seconds(second)); }

auto increaseXorY(int& XorY, mutex& mtx, const string& desc)
{
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        ++XorY;
        cout << format("{} {}\n", desc, XorY);
        mtx.unlock();
        doSomeWork(1);
    }
}

auto consumeXY()
{
    int usecount = 5;
    int XplusY = 0;
    while (usecount > 0) {
        int lockresult = std::try_lock(m1, m2);
        if (lockresult == -1) {
            if (X != 0 && Y != 0) {
                --usecount;
                XplusY += X + Y;
                X = 0;
                Y = 0;
                cout << format("XplusY = {}\n", XplusY);
            }
        }
        m2.unlock();
        m1.unlock();
    }
}

int main()
{
    thread t1(increaseXorY, ref(X), ref(m1), "X");
    thread t2(increaseXorY, ref(Y), ref(m2), "Y");
    thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}