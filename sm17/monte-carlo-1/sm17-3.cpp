#include <iostream>
#include <thread>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <future>
#include <iomanip>
#include <climits>
#include <tuple>

std::pair<uint64_t, uint64_t> f(unsigned num, uint64_t iters) {
    uint64_t circle = 0;
    for (uint64_t i = 0; i < iters; ++i) {
        double x = (double)rand_r(&num) / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand_r(&num) / RAND_MAX * 2.0 - 1.0;
        circle += (x * x + y * y < 1.0);
    }
    return std::make_pair(circle, iters);
}

int main(int argc, char **argv) {
    uint64_t square = 0, circle = 0;
    std::vector<std::future <std::pair<uint64_t, uint64_t>>> fts(atoi(argv[1]));
    for (int i = 0; i < atoi(argv[1]); ++i) {
        fts[i] = std::async(std::launch::async, f, i, atoi(argv[2]));
    }
    for (auto &ft : fts) {
        std::pair<uint64_t, uint64_t> p = ft.get();
        circle += p.first;
        square += p.second;
    }
    double pi = (double) circle / square * 4.0;
    std::cout << std::fixed << std::setprecision(5) << pi << std::endl;
    return 0;
}
