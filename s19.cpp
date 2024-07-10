// 对于一个字符串str,将几个线程分别输出特定个字符
// 例如: str="abcdefg" thread_count=3 char_count=3
// 线程0输出abc 线程1输出def 线程2输出gab 再循环下去

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class MyPrinter {
public:
    MyPrinter(string s, int c_count, int t_count)
        : str(s)
        , char_count(c_count)
        , thread_count(t_count)
    {
    }

    auto getCurrentThreadId(const thread::id& id) -> int;
    void waitForAllThreadInit();
    void printChars();
    void printThread();
    void run();
    static int max_count;

private:
    int char_count;
    int thread_count;
    int allowed_thread = 0;
    int next_char_index = 0;
    string str;
    mutex mtx;

    condition_variable cond;
    vector<thread> threads;
    vector<thread::id> thread_ids;
};
int MyPrinter::max_count = 0;

auto MyPrinter::getCurrentThreadId(const thread::id& id) -> int
{
    int thread_id = 0;
    for (auto& e : thread_ids) {
        if (e == id) {
            return thread_id;
        }
        thread_id++;
    }
    return -1;
}

void MyPrinter::waitForAllThreadInit()
{
    while (true) {
        if (thread_count == thread_ids.size()) {
            return;
        }
    }
}

void MyPrinter::printChars()
{
    cout << "ThreadId " << getCurrentThreadId(this_thread::get_id()) << ":";
    int print_count = 0;
    auto len = str.length();
    int i = next_char_index;
    while (print_count < char_count) {
        cout << str[i];
        print_count++;
        i = (i + 1) % len;
    }
    max_count += print_count;
    cout << endl;
}

void MyPrinter::printThread()
{
    while (true) {
        // 等待所有线程就绪在输出
        waitForAllThreadInit();
        unique_lock<mutex> mutex_lock(mtx);
        cond.wait(mutex_lock, [this] { return this_thread::get_id() == thread_ids[allowed_thread]; });
        printChars();
        allowed_thread = (allowed_thread + 1) % thread_count;
        next_char_index = (next_char_index + char_count) % str.length();
        // 输出超过一百个字符直接退出,避免无限循环
        if (max_count > 100) {
            exit(0);
        }
        mutex_lock.unlock();
        cond.notify_all();
    }
}

void MyPrinter::run()
{
    for (int i = 0; i < thread_count; ++i) {
        thread t(&MyPrinter::printThread, this);
        cout << "Thread " << t.get_id() << " is " << i << endl;
        thread_ids.push_back(t.get_id());
        threads.push_back(std::move(t));
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

int main()
{
    string str = "abcdefg";
    int char_count = 3;
    int thread_count = 3;

    MyPrinter my_printer(str, char_count, thread_count);
    my_printer.run();

    return 0;
}
