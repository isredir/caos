#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <chrono>
#include <functional>

template <typename Function, typename Callback, typename ...Args>
void async_launch(Function &&f, Callback &&c, Args &&...args) {
    auto lambda = [](auto &&f, auto &&c, auto &&...args) {
        auto res = f(std::forward<decltype(args)>(args)...);
        c(std::forward<decltype(res)>(res));
    };
    std::thread(lambda, std::forward<Function>(f), std::forward<Callback>(c), std::forward<Args>(args)...).detach();
}
