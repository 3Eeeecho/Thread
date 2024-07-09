// 基本上,std::promise 被发送到被调用的线程，一旦值准备就绪，我们在promise对象中设置该值，现在在调用线程端，
// 使用std::future对象获取该值，该对象是使用std::promise对象创建的，然后再将其发送到被调用的线程。
// 这就是从一个线程同步到另一个线程接收价值的方式。
#include <chrono>
#include <exception>
#include <format>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

using namespace std;

auto factorial(future<int>& f) -> int
{
    int res = 1;
    int N = f.get();
    for (auto i = N; i > 1; --i) {
        res *= i;
    }
    cout << format("result is {}\n", res);
    return res;
}

int main()
{

    promise<int> p;
    future<int> f = p.get_future();
    future<int> fu = async(factorial, ref(f));

    this_thread::sleep_for(chrono::seconds(1));

    // p.set_exception(std::make_exception_ptr(std::runtime_error("To err is human.\n")));
    p.set_value(4);
    int x = fu.get();
    cout << format("x is {}\n", x);
    return 0;
}