#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void run(int count)
{
    while (count-- > 0) {
        cout << "hello\n";
    }
    this_thread::sleep_for(chrono::seconds(3));
}

int main()
{
    cout << "main start\n";

    // 1.join
    // 主线程会等待子线程返回再运行
    // thread t1(run, 10);
    // t1.join();

    // t.join() 不允许连续join 会报错

    // 可利用joinable()函数,判断是否可以join
    // if (t1.joinable()) {
    //     t1.join();
    // }

    // 2.detach
    // 子线程会分离出来,独立运行,主线程不会等待
    thread t2(run, 5);
    t2.detach();
    cout << "main end\n";
    return 0;
}