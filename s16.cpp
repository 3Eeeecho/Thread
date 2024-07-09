// 学习std::async及其用法，例如如何创建任务。使用std::async创建任务有三种不同的启动策略，如下所示
// 1. std::launch::async  保证异步行为，即传递函数将在单独的线程中执行
// 2. std::launch::deffered  当其他线程调用get()来访问共享状态时，将调用非异步行为
// 3. std::launch::async | std::launch::deffered  默认行为。有了这个启动策略，它可以异步运行或不运行，这取决于系统的负载，但我们无法控制它。

#include <future>
#include <iostream>
#include <thread>

using namespace std;

using ull = unsigned long long;

ull findOdd(ull start, ull end)
{
    ull oddSum = 0;
    cout << "ThreadID: " << this_thread::get_id() << '\n';
    for (ull i = start; i <= end; ++i) { // corrected loop condition
        if (i & 1) {
            oddSum += i;
        }
    }
    return oddSum;
}

int main()
{
    ull start = 0, end = 1.9e9;
    cout << "ThreadID: " << this_thread::get_id() << endl; // corrected thread ID output

    cout << "Thread created if policy is std::launch::async!!\n";
    future<ull> oddSum = async(launch::async, findOdd, start, end); // corrected launch policy

    cout << "Waiting for the result.\n";
    cout << "oddSum is " << oddSum.get() << endl; // corrected output formatting
    return 0;
}
