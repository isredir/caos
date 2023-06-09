|                      |        |
|----------------------|--------|
| **Time limit:**      | `3 s`  |
| **Real time limit:** | `3 s`  |
| **Memory limit:**    | `256M` |


### Problem sm17-5: cxx/thread/vector-callback-1

Разработайте шаблонную функцию `async_vector` с прототипом:

    
    
    template<class Input, class Output, class Function, class Callback>
    void async_vector(const std::vector<Input> &ins, const Function &f, Callback &&c);
    

Функция работает следующим образом: для каждого элемента вектора `ins` с помощью функции
`async_launch` (см. задачу c++/thread/launch-callback-1 В этой задаче функция написана за вас)
запускается асинхронная функция `f`. Результат, который вырабатывает функция `f`, добавляется в
вектор типа `std::vector<Output>`. Когда весь входной вектор будет обработан, запускается функция
`c`, которой по константной ссылке передается вектор результатов.

Функция `async_vector` должна завершиться немедленно, ожидание завершения обработки всех элементов
вектора не допускается.

Например:

    
    
    int incr(int a)
    {
        return a + 1;
    }
    
    void print(const std::vector<int> &outs)
    {
        for (auto v : outs) {
            std::cout << v << endl;
        }
    }
    
    int main()
    {
        using namespace std::literals::chrono_literals;
    
        std::vector<int> ins{1, 2, 3, 4, 5};
        async_vector<int, int>(ins, std::function(incr), std::function(print));
        std::this_thread::sleep_for(500ms);
    }
    

На стандартный поток вывода будут выведены числа 2, 3, 4, 5, 6 в произвольном порядке.

Не создавайте дополнительный тред для ожидания завершения обработки вектора. Учитывайте время жизни
переменных.

