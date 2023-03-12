|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem ku02-2: c/data-structures/push-pop-dlink-list

Реализуйте нижеописанные функции `push` и `pop` над двусвязным списком.

В тестирующей системе доступен заголовочный файл [`dlist.h`](https://caos.myltsev.ru/cgi-bin/new-
client?SID=2633f3fd3d7825db&prob_id=56&action=194&file=dlist.h), который вы можете включить
директивой #include.

В заголовочном файле определён тип `Node` \- вершина двусвязного списка, и объявлены функции,
которые необходимо реализовать.

    
    
    typedef struct Node {
        struct Node *prev;
        struct Node *next;
        int value;
    } Node;
    
    Node *push(Node *place, int value);
    int pop(Node *node);

Функция `push` создает новую `Node` со значением `value` и вставляет ее перед вершиной `place`.
Функция возвращает созданную на куче вершину.

Если `place == NULL`, то список пустой.

В случае неуспешной аллокации возвращайте `NULL`

Функция `pop` вынимает вершину из списка, высвобождает память вершины и возвращает число из этой
вершины. Гарантируется, что аргумент pop не равен NULL.

Пример использования:

    
    
    Node * head = NULL;
    head = push(head, 1);
    head = push(head, 2);
    pop(head->next) == 1;
    pop(head) == 2;

