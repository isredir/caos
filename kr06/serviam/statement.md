|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem kr06-3: kr6/serviam

Напишите программу serviam, которая пытается ответить, на каком порту обычно находится TCP-сервис,
заданный в командной строке. Если такой TCP-сервис неизвестен, программа должна ответить "Non
serviam." и успешно завершиться.

Используйте getaddrinfo или getservbyname.

### Examples

#### Input

    
    
    ./serviam http

#### Output

    
    
    80

#### Input

    
    
    ./serviam bootps

#### Output

    
    
    Non serviam.

