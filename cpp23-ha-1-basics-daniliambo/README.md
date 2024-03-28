[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/2vL96XDL)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=11987556&assignment_repo_type=AssignmentRepo)
# Домашнее задание 1

Задания предполагают использование циклов, ветвлений.
**Алгоритмическая сложность заданий не учитывается**, однако очень рекомендуется подумать над сложностью ваших алгоритмов.

**Замечание:** если тест не проходит, то нужно поправить ваш код, а не содержимое теста.

## Формулировка задачи

Необходимо реализовать 4 процедуры:
- `sum_digits` - для подсчета суммы цифр в переданном числе;
- `count_primes` - для подсчета простых чисел строго меньше заданного N;
- `divide` - для целочисленного деления двух чисел a и b (b != 0) без операций умножения, деления и остатка.
- `roman_to_integer` - функция для перевода числа из Римской системы.

В качестве примера входных данных удобно использовать тесты.

### Hint

Для сборки приложения из консоли следуют выполнить следующий набор инструкций:
```shell
mkdir build; cd build;
cmake .. -G <GeneratorName>
cmake --build .
```

Для запуска автотестов:
```shell
ctest . # or use -R <test-name> to run specific test
```
