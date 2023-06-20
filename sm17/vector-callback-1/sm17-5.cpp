#include <future>
#include <thread>
#include <vector>
#include <iostream>

template <class Input, class Output, class Function, class Callback>
void async_vector(const std::vector<Input> &ins, const Function &f, Callback &&c) {
    std::vector<Output> v(ins.size());
    std::vector<std::promise<Output>> p(ins.size());
    for (size_t i = 0; i < ins.size(); ++i) {
        async_launch(std::ref(f), [&, i](auto x) { p[i].set_value(std::move(x)); }, ins[i]);
    }
    for (size_t i = 0; i < ins.size(); ++i) {
        v[i] = p[i].get_future().get();
    }
    c(v);
}
