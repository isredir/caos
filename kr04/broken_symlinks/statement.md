|                      |       |
|----------------------|-------|
| **Time limit:**      | `1 s` |
| **Real time limit:** | `5 s` |
| **Memory limit:**    | `64M` |


### Problem ku04-1: kr04-1 (дореш)

Программе в аргументах командной строки передаются пути к файлам. Каждый путь PATH следует
напечатать на stdout в следующем виде:

* `PATH (missing)`, если файл не существует;
* `PATH (broken symlink)`, если файл является символической ссылкой, указывающей на несуществующий путь;
* `PATH` во всех остальных случаях.

Например:

    
    
    $ ln -s /non/existent symlink_bad
    $ ln -s regular symlink_good
    $ touch regular
    $ ./yourprog regular symlink_good symlink_bad /non/existent
    regular
    symlink_good
    symlink_bad (broken symlink)
    /non/existent (missing)

