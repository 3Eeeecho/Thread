// 使用“条件变量”时要记住的几个要点如下：
// 1.条件变量允许我们通过通知同步线程。
// a.notify_one（）;
// b.notify_all（）;
// 2.需要互斥锁才能使用条件变量
// 3.条件变量用于同步两个或多个线程。
// 4.条件变量的最佳用例是生产者/消费者问题。
// 5.条件变量可用于两个目的：
// a.通知其他线程
// b.等待某些条件

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

condition_variable cv;
long balance = 0;
mutex m;

auto addMoney(int money)
{
    lock_guard<mutex> lg(m);
    balance += 500;
    cout << "Adding money: " << money << endl;
    cv.notify_one();
}

auto withDrawMoney(int money)
{
    unique_lock<mutex> ul(m);
    cv.wait(ul, [] { return balance > 0 ? true : false; });
    if (balance >= money) {
        balance -= money;
        cout << "withdraw money: " << money << endl;
    } else {
        cout << "withdraw money failed.\n";
    }
    cout << "Current balance is " << balance << endl;
}

int main()
{
    thread t1(addMoney, 500);
    thread t2(withDrawMoney, 500);

    t1.join();
    t2.join();
    return 0;
}