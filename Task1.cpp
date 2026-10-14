#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Stack for storing strings
class StringStack {
    string items[100];
    int top = -1;

public:
    bool isEmpty() {
        return top == -1;
    }

    void push(string value) {
        items[++top] = value;
    }

    string pop() {
        return items[top--];
    }

    string peek() {
        return items[top];
    }
};

// Stack for storing numbers
class NumberStack {
    double items[100];
    int top = -1;

public:
    bool isEmpty() {
        return top == -1;
    }

    void push(double value) {
        items[++top] = value;
    }

    double pop() {
        return items[top--];
    }
};

// Check whether a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '^';
}

// Return operator precedence
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    return 1;
}

// Calculate the result of an operation
double calculate(char op, double a, double b) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return pow(a, b);
}

// Reverse a string
string reverseString(string s) {
    string result = "";
    for (int i = (int)s.length() - 1; i >= 0; i--)
        result += s[i];
    return result;
}

// Convert infix to postfix
string infix_to_postfix(string expr) {
    StringStack operators;
    string output = "";

    for (char c : expr) {
        if (c == ' ') continue;

        if (c == '(') {
            operators.push("(");
        }
        else if (c == ')') {
            while (!operators.isEmpty() && operators.peek() != "(")
                output += operators.pop();

            if (!operators.isEmpty())
                operators.pop();
        }
        else if (isOperator(c)) {
            while (!operators.isEmpty() && operators.peek() != "(" &&
                   (precedence(operators.peek()[0]) > precedence(c) ||
                   (precedence(operators.peek()[0]) == precedence(c) &&
                    c != '^'))) {
                output += operators.pop();
            }
            operators.push(string(1, c));
        }
        else {
            output += c;
        }
    }

    while (!operators.isEmpty())
        output += operators.pop();

    return output;
}

// Convert infix to prefix
string infix_to_prefix(string expr) {
    expr = reverseString(expr);

    for (int i = 0; i < (int)expr.length(); i++) {
        if (expr[i] == '(') expr[i] = ')';
        else if (expr[i] == ')') expr[i] = '(';
    }

    StringStack operators;
    string output = "";

    for (char c : expr) {
        if (c == ' ') continue;

        if (c == '(') {
            operators.push("(");
        }
        else if (c == ')') {
            while (!operators.isEmpty() && operators.peek() != "(")
                output += operators.pop();

            if (!operators.isEmpty())
                operators.pop();
        }
        else if (isOperator(c)) {
            while (!operators.isEmpty() && operators.peek() != "(" &&
                   (precedence(operators.peek()[0]) > precedence(c) ||
                   (precedence(operators.peek()[0]) == precedence(c) &&
                    c == '^'))) {
                output += operators.pop();
            }
            operators.push(string(1, c));
        }
        else {
            output += c;
        }
    }

    while (!operators.isEmpty())
        output += operators.pop();

    return reverseString(output);
}

// Convert postfix to infix
string postfix_to_infix(string expr) {
    StringStack stack;

    for (char c : expr) {
        if (c == ' ') continue;

        if (isOperator(c)) {
            string right = stack.pop();
            string left = stack.pop();
            stack.push("(" + left + c + right + ")");
        }
        else {
            stack.push(string(1, c));
        }
    }

    return stack.pop();
}

// Evaluate postfix expression
double evaluate_postfix(string expr) {
    NumberStack stack;

    for (char c : expr) {
        if (c == ' ') continue;

        if (isOperator(c)) {
            double b = stack.pop();
            double a = stack.pop();
            stack.push(calculate(c, a, b));
        }
        else {
            stack.push(c - '0');
        }
    }

    return stack.pop();
}

// Evaluate prefix expression
double evaluate_prefix(string expr) {
    NumberStack stack;

    for (int i = (int)expr.length() - 1; i >= 0; i--) {
        char c = expr[i];

        if (c == ' ') continue;

        if (isOperator(c)) {
            double a = stack.pop();
            double b = stack.pop();
            stack.push(calculate(c, a, b));
        }
        else {
            stack.push(c - '0');
        }
    }

    return stack.pop();
}

int main() {
    string expr;
    cout << "Enter an infix expression: ";
    if (!getline(cin, expr) || expr.empty()) {
        cerr << "No expression entered." << endl;
        return 1;
    }

    string postfix = infix_to_postfix(expr);
    string prefix = infix_to_prefix(expr);

    cout << "Infix: " << expr << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Prefix: " << prefix << endl;
    cout << "Postfix to Infix: " << postfix_to_infix(postfix) << endl;
    cout << "Postfix Result: " << evaluate_postfix(postfix) << endl;
    cout << "Prefix Result: " << evaluate_prefix(prefix) << endl;

    return 0;
}
