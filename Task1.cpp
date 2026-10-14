// Task 1: Expression conversion and evaluation using our own stacks
// Operands are single characters (A, B, 5 ...), operators are + - * / ^
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
 
// ---------- Stack of strings (array based) ----------
class StringStack {
    string items[100];
    int topIndex = -1;                  // -1 means empty
public:
    bool isEmpty() { return topIndex == -1; }
    void push(string value) { topIndex++; items[topIndex] = value; }
    string pop() { string value = items[topIndex]; topIndex--; return value; }
    string top() { return items[topIndex]; }
};
 
// ---------- Stack of doubles (array based) ----------
class DoubleStack {
    double items[100];
    int topIndex = -1;
public:
    bool isEmpty() { return topIndex == -1; }
    void push(double value) { topIndex++; items[topIndex] = value; }
    double pop() { double value = items[topIndex]; topIndex--; return value; }
};
 
// ---------- Helper functions ----------
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
 
// Higher number = higher priority
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    return 1;                           // + and -
}
 
// Should the operator on the stack top be popped before pushing the current one?
bool shouldPop(char topOp, char currentOp, bool isPrefix) {
    if (precedence(topOp) > precedence(currentOp)) return true;
    if (precedence(topOp) < precedence(currentOp)) return false;
    // Equal priority: ^ goes right-to-left, others left-to-right
    // (prefix works on the reversed expression, so the rule flips)
    if (currentOp == '^') return isPrefix;
    return !isPrefix;
}
 
string reverseString(string s) {
    string result = "";
    for (int i = s.length() - 1; i >= 0; i--) result += s[i];
    return result;
}
 
// Do one calculation: a op b
double calculate(char op, double a, double b) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return pow(a, b);
}
 
// ---------- Infix to Postfix (shunting-yard) ----------
// The same code is reused for prefix with isPrefix = true
string convertToPostfix(string expr, bool isPrefix) {
    StringStack operators;
    string output = "";
 
    for (char c : expr) {
        if (c == ' ') continue;
 
        if (c == '(') {
            operators.push("(");
        }
        else if (c == ')') {
            // pop until the matching '('
            while (operators.top() != "(") output += operators.pop();
            operators.pop();            // remove '('
        }
        else if (isOperator(c)) {
            // pop operators that must be done first
            while (!operators.isEmpty() && operators.top() != "(" &&
                   shouldPop(operators.top()[0], c, isPrefix)) {
                output += operators.pop();
            }
            operators.push(string(1, c));
        }
        else {
            output += c;                // operand goes directly to output
        }
    }
    while (!operators.isEmpty()) output += operators.pop();
    return output;
}
 
string infix_to_postfix(string expr) {
    return convertToPostfix(expr, false);
}
 
// Prefix: reverse -> swap brackets -> convert -> reverse again
string infix_to_prefix(string expr) {
    expr = reverseString(expr);
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '(') expr[i] = ')';
        else if (expr[i] == ')') expr[i] = '(';
    }
    return reverseString(convertToPostfix(expr, true));
}
 
// ---------- Postfix to Infix ----------
string postfix_to_infix(string expr) {
    StringStack stack;
    for (char c : expr) {
        if (isOperator(c)) {
            string right = stack.pop();         // second operand comes out first
            string left = stack.pop();
            stack.push("(" + left + c + right + ")");
        } else {
            stack.push(string(1, c));
        }
    }
    return stack.pop();
}
 
// ---------- Evaluate Postfix: scan left to right ----------
double evaluate_postfix(string expr) {
    DoubleStack stack;
    for (char c : expr) {
        if (isOperator(c)) {
            double right = stack.pop();
            double left = stack.pop();
            stack.push(calculate(c, left, right));
        } else {
            stack.push(c - '0');                // digit character to number
        }
    }
    return stack.pop();
}
 
// ---------- Evaluate Prefix: scan right to left ----------
double evaluate_prefix(string expr) {
    DoubleStack stack;
    for (int i = expr.length() - 1; i >= 0; i--) {
        char c = expr[i];
        if (isOperator(c)) {
            double left = stack.pop();          // first operand comes out first
            double right = stack.pop();
            stack.push(calculate(c, left, right));
        } else {
            stack.push(c - '0');
        }
    }
    return stack.pop();
}
 
int main() {
    // Conversion test
    string expr1 = "A+B*C-(D/E)^F";
    string post1 = infix_to_postfix(expr1);
    cout << "Infix   : " << expr1 << endl;
    cout << "Postfix : " << post1 << endl;
    cout << "Prefix  : " << infix_to_prefix(expr1) << endl;
    cout << "Postfix to Infix : " << postfix_to_infix(post1) << endl;
 
    // Evaluation test
    string expr2 = "(2+3)*4-6/2";
    string post2 = infix_to_postfix(expr2);
    string pre2 = infix_to_prefix(expr2);
    cout << "\nInfix   : " << expr2 << endl;
    cout << "Postfix : " << post2 << "  Result = " << evaluate_postfix(post2) << endl;
    cout << "Prefix  : " << pre2 << "  Result = " << evaluate_prefix(pre2) << endl;
    return 0;
}
