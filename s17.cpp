#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

deque<int> buffer;
mutex mtx;
condition_variable cond;
const int maxBufferSize = 256;
auto producer(int val)
{
    while (val-- > 0) {
        unique_lock<mutex> locker(mtx);
        cond.wait(locker, []() { return buffer.size() < maxBufferSize; });
        buffer.push_back(val);
        cout << "Produced: " << val << endl;
        locker.unlock();
        cond.notify_one();
    }
}

auto consumer()
{
    while (true) {
        unique_lock<mutex> locker(mtx);
        cond.wait(locker, []() { return buffer.size() > 0; });
        int val = buffer.front();
        buffer.pop_front();
        cout << "Consumed: " << val << endl;
        locker.unlock();
        cond.notify_one();
    }
}

int main()
{
    thread t1(producer, 100);
    thread t2(consumer);

    t1.join();
    t2.join();
    return 0;
}