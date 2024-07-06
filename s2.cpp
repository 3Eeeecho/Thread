// How to create threads

#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

// 1.利用函数指针,最基本的方式
// void run(int count)
// {
//     while (count-- > 0) {
//         cout << count << " ";
//     }
// }

// int main()
// {
//     thread t(run, 10);
//     t.join();
//     return 0;
// }

// 2.lambda表达式

// int main()
// {
//     // auto run = [](int count) {while (count-- > 0) {
//     //     cout << count << " ";
//     // } };
//     // thread t(run, 10);

//     // 或者直接将lambda放入参数中

//     thread t([](int count) {while (count-- > 0) {
//         cout << count << " ";
//     } }, 10);

//     t.join();
//     return 0;
// }

// 3.仿函数
// class Base {
// public:
//     void operator()(int count)
//     {
//         while (count-- > 0) {
//             cout << count << " ";
//         }
//     }
// };

// int main()
// {
//     thread t(Base(), 10);
//     t.join();
//     return 0;
// }

// 4.非静态成员函数
// class Base {
// public:
//     void run(int count)
//     {
//         while (count-- > 0) {
//             cout << count << " ";
//         }
//     }
// };

// int main()
// {
//     Base b;
//     thread t(&Base::run, &b, 10);
//     t.join();
//     return 0;
// }

// 5.静态成员函数
// class Base {
// public:
//     static void run(int count)
//     {
//         while (count-- > 0) {
//             cout << count << " ";
//         }
//     }
// };

// int main()
// {
//     thread t(&Base::run, 10);
//     t.join();
//     return 0;
// }