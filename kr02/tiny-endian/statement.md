|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem ku02-5: c/ints/tiny-endian

Формат представления данных TinyEndian отличается от привычного нам тем, что биты в байте
располагаются в обратном порядке. Напишите функцию `void tinyconv(uint8_t bytes[], size_t size)`,
которая преобразует данные в массиве bytes в формат TinyEndian. size - размер массива.

Например:

    
    
    uint8_t b[] = {0xfa, 0x04};
    tinyconv(b, 2);
    // теперь b == {0x5f, 0x20}

