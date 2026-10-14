#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Stack for storing strings
class Stack {
    vector<string> items;

public:
    bool isEmpty() {
        return items.empty();
    }

    void push(const string& value) {
        items.push_back(value);
    }

    string pop() {
        string value = items.back();
        items.pop_back();
        return value;
    }

    const string& peek() const {
        return items.back();
    }
};

// Part A: Check balanced brackets
bool isValidBrackets(string s) {
    Stack stack;

    for (char c : s) {
        // Push opening brackets
        if (c == '(' || c == '{' || c == '[') {
            stack.push(string(1, c));
        }
        // Check closing brackets
        else if (c == ')' || c == '}' || c == ']') {
            if (stack.isEmpty())
                return false;

            char top = stack.pop()[0];

            if (c == ')' && top != '(') return false;
            if (c == '}' && top != '{') return false;
            if (c == ']' && top != '[') return false;
        }
    }

    // No opening brackets should remain
    return stack.isEmpty();
}

// Part B: Validate simplified HTML/XML tags
bool validate_markup(const string& s, vector<string>& errors) {
    Stack stack;
    errors.clear();

    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] != '<')
            continue;

        int j = i + 1;

        // Find the closing angle bracket
        while (j < (int)s.length() && s[j] != '>')
            j++;

        if (j == (int)s.length()) {
            errors.push_back("Missing '>' in tag");
            break;
        }

        string tag = s.substr(i + 1, j - i - 1);
        const size_t first = tag.find_first_not_of(" \t\r\n");
        if (first == string::npos) {
            errors.push_back("Empty tag");
        } else {
            tag = tag.substr(first);
            const size_t last = tag.find_last_not_of(" \t\r\n");
            tag.erase(last + 1);

            if (tag[0] != '?' && tag[0] != '!') {
                const bool closing = tag[0] == '/';
                if (closing)
                    tag = tag.substr(1);

                const size_t nameEnd = tag.find_first_of(" \t\r\n/");
                const string name = tag.substr(0, nameEnd);

                if (name.empty()) {
                    errors.push_back("Empty tag");
                } else if (closing) {
                    if (stack.isEmpty()) {
                        errors.push_back("Unexpected closing tag: " + name);
                    } else if (stack.peek() != name) {
                        errors.push_back("Mismatched closing tag: " + name);
                    } else {
                        stack.pop();
                    }
                } else if (tag[tag.length() - 1] != '/') {
                    stack.push(name);
                }
            }
        }

        i = j;
    }

    // Check for unclosed tags
    while (!stack.isEmpty()) {
        errors.push_back("Unclosed tag: " + stack.pop());
    }

    return errors.empty();
}

int main() {
    string brackets;
    cout << "Enter a string to check for balanced brackets: ";
    if (!getline(cin, brackets)) {
        cerr << "Could not read bracket input." << endl;
        return 1;
    }

    if (isValidBrackets(brackets))
        cout << "Brackets are balanced." << endl;
    else
        cout << "Brackets are not balanced." << endl;

    string markup;
    cout << "Enter markup to validate: ";
    if (!getline(cin, markup)) {
        cerr << "Could not read markup input." << endl;
        return 1;
    }

    vector<string> errors;

    if (validate_markup(markup, errors)) {
        cout << "Brackets  is valid." << endl;
    }
    else {
        cout << "Brackets is invalid." << endl;

        for (size_t i = 0; i < errors.size(); i++)
            cout << errors[i] << endl;
    }

    return 0;
}
