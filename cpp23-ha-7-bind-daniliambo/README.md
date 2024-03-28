[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/BiKfpxRy)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=13180506&assignment_repo_type=AssignmentRepo)
# Домашнее задание 7

Реализуйте функциональность `std::bind` из стандартной библиотеки C++ (стандарт 2011 года).

```c++
#include <iostream>
#include <functional>

void f(int n1, int n2)
{
    std::cout << n1 << ' ' << n2 << '\n';
}

int g(int n1)
{
    return n1;
}

int main()
{
    using namespace std::placeholders;

    // demonstrates argument reordering
    auto f1 = std::bind(f, _2, _1);
    f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused

    auto f2 = std::bind(g, 10);
    int x = f2(); // x = g(10)
}
```

## Требования к реализации

Ваша функция `bind` должна частично реализовывать функционал стандартной функции `std::bind`. А именно:
- Позволяет зафиксировать (забиндить) обычную свободную функцию (передачу функтора или member функции можно не поддерживать).
- Можно зафиксировать любые подходящие значения в качестве параметра функции.
- Можно зафиксировать плейсхолдер (`_1` и/или `_2`), обозначающие какой аргумент при вызове будет подставляться в качестве текущего аргумента функции.
- Функция `bind` (назовем биндер) создает объект, который допускает его вызов по оператору `()`. Переданные параметры вместе с зафиксированными должны приводиться к типам, ожидаемым зафиксированной функцией. В противном случае такой вызов не должен компилироваться.
- Биндер допускает вызов по оператору `()` с бОльшим количеством аргументов, чем это может предполагать переданная в `bind` функция с возможно зафиксированными аргументами. Лишние аргументы игнорируются. В «общих требованиях» описаны ограничения на количество параметров.
- Биндер допускает копирование и присваивание. Move биндера допускается, если все зафиксированные аргументы допускают `move`.
- Тип, возвращаемый оператором `()` объекта биндера, должен соответствовать возвращаемому типу переданной в bind функции.

## Общие требования

- Предполагается, что реализация использует **variadic templates**.
- Вводится ограничение на количество плейсхолдеров. Есть только `_1` и `_2`.
- Реализация `bind`’a должна корректно работать как с передачей аргументов по значению, так и со ссылками (как константными, так и неконстантными).
- При передаче параметров функции должен использоваться **perfect forwarding** (`rvalue reference` + `std::forward`).
- Реализация не должна вводить дополнительных пессимизаций. Cледует максимально избегать накладных расходов, которые возникают из-за использования `bind`’a, которые компилятор не может разрешить в силу недостаточности знаний о ваших намерениях.
- Функция `bind`, должны находиться в `namespace fn`. Функция `bind`, `_1`, `_2` и связанные определения типов должны быть реализованы в пространстве имен `fn`. Все необходимые вспомогательные классы и функции должны находиться в пространстве имён `fn::details`.
- Не забывайте о самодостаточности вашего заголовочного файла. Пользователь должен иметь возможность включить его в «пустой» cpp-шник и иметь возможность использовать ваш `bind`. Также, не должно возникать warning’ов, если пользователь ваш хидер включил, но ничего из него не использует.
- Ваша реализация должна обеспечивать строгую гарантию безопасности исключений.

## Структура проекта

Решение необходимо оформить **в виде библиотеки, состоящей из одного заголовочного файла**.

Заголовочный файл должен называться `bind.hpp`.

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