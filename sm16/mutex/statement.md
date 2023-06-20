|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem sm16-2: unix/threads/mutex

Сделайте мьютекс на фьютексах.

Определите тип `caos_mutex_t` и следующие функции:

    
    
    void caos_mutex_init(caos_mutex_t *m);
    void caos_mutex_lock(caos_mutex_t *m);
    void caos_mutex_unlock(caos_mutex_t *m);

Тестирующая программа обязана инициализировать мьютекс перед использованием. После этого пара
вызовов `caos_mutex_lock/caos_mutex_unlock` с одним и тем же мьютексом создаёт в программе
критическую секцию, в которой может одновременно находиться только один тред.

Активное ожидание запрещено. Для ожидания используйте фьютексы.

Можно считать, что мьютекс никогда не будет уничтожен (не будет освобождена память, в которой он
находится).

В тестирующей программе определены следующие вспомогательные функции:

    
    
    void futex_wait(_Atomic int *addr, int val) {
        // atomically: block on addr if (*addr == val)
        syscall(SYS_futex, addr, FUTEX_WAIT, val, NULL, NULL, 0);
    }
    
    void futex_wake(_Atomic int *addr, int num) {
        // wake up to num threads blocked on addr
        syscall(SYS_futex, addr, FUTEX_WAKE, num, NULL, NULL, 0);
    }

