# DSA-LAB-06

CS-250 Data Structures and Algorithms - Lab 6 (Stacks and Queues), written in C++.

## Task 1: Expression Conversion and Evaluation

`Task1.cpp` uses two array-based stacks written from scratch (`StringStack` and `DoubleStack`) to:

- convert infix to postfix (shunting-yard)
- convert infix to prefix (reverse, swap brackets, convert, reverse again)
- convert postfix back to infix
- evaluate postfix and prefix expressions

Operands are single characters; supported operators are `+ - * / ^` and brackets.

### Build and run

```bash
g++ Task1.cpp -o task1
./task1
```

### Sample output

```
Infix   : A+B*C-(D/E)^F
Postfix : ABC*+DE/F^-
Prefix  : -+A*BC^/DEF
Postfix to Infix : ((A+(B*C))-((D/E)^F))

Infix   : (2+3)*4-6/2
Postfix : 23+4*62/-  Result = 17
Prefix  : -*+234/62  Result = 17
```
