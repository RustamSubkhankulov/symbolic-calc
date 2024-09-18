# symbolic-calc
Калькулятор символьных выражений.

## Описание

Калькулятор арифметический выражений с поддержкой:
- Бинарных операций: ``+``, ``-``, ``*``, ``/``.
- Использования целых чисел и чисел с плавающей точкой одинарной точности.
- Констант, поддерживаемых языком арифметики: ``PI`` - число Пи, ``EXP`` - число Эйлера.
- Некоторых математических функций: ``sin``, ``cos``, ``tg``, ``ctg``, ``sqrt``.
- Приоритизации посредством фигурных скобок: ``{}``.
- Соблюдением приоритета операций, совпадающего с приоритетом соответствующих операций в стандарте языка C.
- Определения переменных - непосредственным значением или именованной константой.

## Структура репозитория
- *inc* - директория, содержащая 'public 'заголовочные файлы - необходимые при использовании калькулятора в качестве библиотеки. 
- *inc-private* - директория, содержащая заголовочные файлы, необходимыe для драйвера запуска калькулятора из командной строки.
- *lex* - директория, содержащая правила для генерации лексического анализатора посредством *Flex*.
- *src* - директория, содержащая файлы с исходным кодом. 
- *yacc* - директория, содержащая правила для генерации парсера посредством *Bison*. 

## Детали реализации

В данном репозитории предоставлен драйвер для использования калькулятора выражений посредством его вызова из командной строки. Калькулятор может быть использовать в качестве библиотеки и в других проектах, посредством копирования соответствующих исходных файлов, исключая необходимые лишь для работы в качестве cmnd line утилиты.

Для вычисления выражений в проекте использовались *Flex* и *Bison*.

### Flex

*Flex* — инструмент для создания сканеров. Сканер — это программа, распознающая лексические закономерности в тексте. *Flex* считывает заданные входные файлы или стандартный ввод, если имена файлов не указаны, для получения описания создаваемого сканера. Описание представлено в виде пар регулярных выражений и кода C, называемых правилами. *Flex* генерирует в качестве вывода исходный файл C, который определяет функцию ``yylex()``. Этот файл можно скомпилировать и связать с библиотекой времени выполнения *Flex* для создания исполняемого файла. При запуске исполняемого файла он анализирует входные данные на наличие регулярных выражений. Всякий раз, когда он его находит, он выполняет соответствующий код C.

Правила для создания сканера расположены в файле ``lex/lex.l``. 
Примерами токенов, которые распознает лексер в данном проекте, являются: ``NUMINT`` и ``NUMFLT``, соответствующие целым числам и числам с плавающей точкой; ``VAR_ID`` - идентификатор (имя) переменной; ``STD_FUNC`` - стандартная математическая функция из числа поддерживаемых и т.д.

В данном проекте *Flex* используется для создания лексического анализатора. С помощью него в строке, описывающей арифметическое выражение, распознаются допустимые лексемы и определяются соответствующие им типы токенов. Напрямую через метод ``yylex()`` анализатор в данном проекте не используется, так как его вызывает следующий модуль программы - парсер (cм. [*Bison*](#Bison)).

### Bison

GNU *Bison* — программа, предназначенная для автоматического создания синтаксических анализаторов по данному описанию грамматики. Синтаксический анализатор получает на вход поток токенов, распознанных с помощью лексического анализатора, и находит нетерминальные символы и выполняет заданный код согласно грамматике, определенной в соответствующем формате. В качестве точки входа в синтаксический анализатор *Bison* определяет функцию ``yyparse()``. 

*Bison* является GNU-версией *yacc* (Yet Another Compiler Compile) - компьютерной программы, служащей стандартным генератором синтаксических анализаторов (парсеров) в Unix-системах. 

Грамматика для генерации синтаксического анализатора описана в файле ``yacc/yacc.y``.

Если опустить код, используемый для вычисления выражения, грамматику можно описать следующим образом:

```
result: expr

expr: term | expr ADD term | expr SUB term
term: power | term MUL power | term DIV power
power: factor | power POW factor
factor: OPEN_BR_CRVD expr CLOS_BR_CRVD | VAR_ID | constant | std_func

constant: STD_CONST | NUMINT | NUMFLT
std_func: STD_FUNC OPEN_BR_RND expr CLOS_BR_RND
```

Краткое описание грамматики:
- *result* - 'top-level' нетерминал, значение которого является результатом выполнения калькулятора.
- *expr*, *term*, *power* - нетерминалы, тела продукции для которых задают приоритет бинарных арифметических операций - сложения, вычитания, умножения, деления и возведения в степень.
- *factor* - может быть раскрыт в фигурные скобки, содержащие *expr* (приоритизация посредством скобок), а также в идентификатор переменной, константное значение *constant* или вызов математической функции.
- *constant* - стандартная именованная константа (``STD_CONST``), целое число (``NUMINT``) или число с плавающей точкой (``NUMFLT``).
- *std_func* - вызов стандартной математической функции, аргументом которой является выражение *expr* в круглых скобках.

В прочих приложениях синтаксический анализатор, сгенерированный при помощи *Bison* может быть использован, к примеру, для построения Абстрактного Синтаксического Дерева (AST) в ходе процесса компиляции программы на некотором языке программирования. 

В данном проекте поставлена другая задача, поэтому функционал предоставляемый *Bison* используется сразу для вычисления значения арифметического выражения. Код на языке C, исполняемый при обнаружении структуры, соответствующей некоторому правилу грамматики, вычисляет собственное значение на основании тела продукции. Приведем пример для *term*:

```
term:
  power { $<fval>$ = $<fval>1; }
  | term MUL power { 
    $<fval>$ = $<fval>1 * $<fval>3;
    YACC_VPRINT("%f * %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }
  | term DIV power { 
    $<fval>$ = $<fval>1 / $<fval>3; 
    YACC_VPRINT("%f / %f = %f \n", $<fval>1, $<fval>3, $<fval>$);
  }
```

В примере выше в зависимости от обнаруженного токена арифметической операции, исполняется соответствующее вычисление - умножение или деление. 

Еще один пример - вызов математической функции для *std_func*.

```
std_func: STD_FUNC OPEN_BR_RND expr CLOS_BR_RND {
  $<fval>$ = std_func_evaluate($<ival>1, $<fval>3);
}
```

Функция ``std_func_evaluate()`` здесь принимает значение аргумента и код функции, определенный на стадии лексического анализа, производит соответствующий вызов и возвращает полученное значение в качестве значения нетерминала *std_func*.

## Сборка

Для сборки проекта необходима система сборки CMake версии 3.21 и выше, а также установленные утилиты *Flex* и *Bison*.
Чтобы собрать проект, воспользуйтесь следующими командами:
- <code>cmake -B build</code>
- <code>cmake --build build --target calc</code>

## Запуск

По завершении сборки исполняемый файл находится в директории ``build``.

Использование: calc "expression" [OPTIONS]*
- "expression" - строка, содержащая выражение.
- *OPTIONS* - дополнительные опции запуска. Список доступных опций перечислен ниже.

Опции запуска:
1. ``--help`` - отобразить сообщение с информацией об использовании.
2. ``--var variable_name=variable_value`` - определить переменную с именем *variable_name* и значением *variable_value*. Имя заданной переменной можно использовать в выражении, где в качестве ее значения будет использовано *variable_value*. Допускается определение нескольких переменных сразу, но каждая переменная обязательно должна иметь уникальное имя. Значением переменной может является число с плавающей точкой или имя стандартной константы из списка поддерживаемых. Примеры использования опции: ``--var x=PI``, ``--var y=2.5``.

## Отладочные опции сборки: 
- *VERBOSE_LEX* - включает вывод дополнительной debug информации, аннотирующей процесс лексического анализа. По умолчанию отключена. Чтобы собрать проект с включенной данной опцией, необходимо воспользоваться командой <code>cmake -B build -DVERBOSE_LEX=ON</code>

Пример вывода с ``DVERBOSE_LEX=ON``:
```
❯ ./build/calc "2 + sin(x) / {y + cos(x)} * PI" --var x=4.456 --var y=2.456
Evaluating expression: 2 + sin(x) / {y + cos(x)} * PI
NUMINT: 2
ADD
STD_FUNC: sin
OPEN_BR_RND
VAR_ID: x
CLOS_BR_RND
DIV
OPEN_BR_CRVD
VAR_ID: y
ADD
STD_FUNC: cos
OPEN_BR_RND
VAR_ID: x
CLOS_BR_RND
CLOS_BR_CRVD
MUL
STD_CONST: PI
Evaluation result is 0.620194
```

- *VERBOSE_YACC* - включает вывод дополнительной debug информации, аннотирующей процесс синтаксического анализа. По умолчанию отключена. Чтобы собрать проект с включенной данной опцией, необходимо воспользоваться командой <code>cmake -B build -DVERBOSE_YACC=ON</code>

Пример вывода с ``DVERBOSE_YACC=ON``:
```
❯ ./build/calc "2 + sin(x) / {y + cos(x)} * PI" --var x=4.456 --var y=2.456
Evaluating expression: 2 + sin(x) / {y + cos(x)} * PI
Evaluating 'var_id': name x
Evaluated 'var_id': 4.456000
Evaluating 'std_func': code 0 arg 4.456000
Evaluated 'std_func': -0.967312
Evaluating 'var_id': name y
Evaluated 'var_id': 2.456000
Evaluating 'var_id': name x
Evaluated 'var_id': 4.456000
Evaluating 'std_func': code 1 arg 4.456000
Evaluated 'std_func': -0.253589
2.456000 + -0.253589 = 2.202411
-0.967312 / 2.202411 = -0.439206
Evaluating 'STD_CONST': code 0
Evaluated 'STD_CONST': 3.141593
-0.439206 * 3.141593 = -1.379806
2.000000 + -1.379806 = 0.620194
Evaluating result. Evaluation result is 0.620194
```

## Ссылки

Схожие проекты:
1. [Лексический анализатор с использованием *Flex*](https://github.com/RustamSubkhankulov/lexer)
2. [Восходящий синтаксический анализатор типа "Перенос/свёртка"](https://github.com/RustamSubkhankulov/shift-reduce-parser)

### Использованная документация/спецификация
1. [Документация на Bison](https://www.gnu.org/software/bison/manual/bison.html).
2. [Репозиторий проекта Flex на GitHub](https://github.com/westes/flex)
3. [Полезный HOWTO по использованию связки Lex&YACC](https://berthub.eu/lex-yacc/cvs/lex-yacc-howto.html).
