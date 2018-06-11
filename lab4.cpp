#include <iostream>
#include <string> // Pay attention to this. I'm using "string" class from standard
                  // c++ library. It's allowed, because in the methodical material
                  // the description of this algorithm contains class "String" from
                  // builder's library. So, this code becomes even more cross-compiler.

#include <set>
#include <cmath>

using namespace std;

/** STACK FROM THE SECOND LABORATORY **/
/// !!!! PUT YOUR STACK HERE !!!
/// !!!! DELETE MY STACK !!!!
struct Stack {
    double value;
    Stack *next;
};

Stack* push(Stack* parent, double value)
{
    Stack *temp = new Stack;
    temp->value = value;
    temp->next = parent;
    return temp;
}

Stack* pop(Stack* parent, double& out)
{
    if (parent == nullptr) return nullptr;
    out = parent->value;
    Stack* tmp = parent->next;
    delete parent;
    return tmp;
}

void print(Stack* first)
{
    while (first != nullptr)
    {
        cout << first->value << " ";
        first = first->next;
    }
}

int priority(char c) // return the priority of the operator
{
    if (c == '^')
        return 4;
    if (c == '*' || c == '/')
        return 3;
    if (c == '+' || c == '-')
        return 2;
    if (c == '(')
        return 1;
    return 0;
}

/// REVERSE POLISH NOTATION PART (RPN)
string convert(string source) // converting the 'source' string that contains infix expression to RPN
{
    /* It's assuming, that you're going to use your stack from the second laboratory.
        Since I don't have exact YOUR stack, I'll use someone's.
        There'd be no difference, I guess.
     */

    Stack *st = NULL;
    string result;

    int n = source.size(); // length of the source string
    for (int i = 0; i < n; ++i)
    {
        char c = source[i];
        if (c >= 'a' && c <= 'z') {
            result += c;
        } else if (c == '(') {
            st = push(st, c);
        } else if (c == ')') {
            while (st && st->value != '(') {
                double top;
                st = pop(st, top);
                result += char(top);
            }
            if (st && st->value == '(') { double x; st = pop(st, x); }
        } else {
            while (st && priority(st->value) >= priority(c)) {
                double top;
                st = pop(st, top);
                result += char(top);
            }
            st = push(st, c);
        }
    }
    while (st) {
        double top;
        st = pop(st, top);
        result += char(top);
    }
    return result;
}

double calculate(string rpn, double *values)
{
    set<char> math;
    math.insert('*');
    math.insert('/');
    math.insert('+');
    math.insert('-');
    math.insert('^');

    Stack *st;

    double result = 0;

    int n = rpn.size();
    for (int i = 0; i < n; ++i)
    {
        char c = rpn[i];
        if (math.count(c) == 0) {
            st = push(st, values[(int) c - 'a']);
        } else {
            double val1, val2;
            st = pop(st, val1);
            st = pop(st, val2);

            if (c == '+') result = val2 + val1;
            else if (c == '-') result = val2 - val1;
            else if (c == '*') result = val2 * val1;
            else if (c == '/') result = val2 / val1;
            else if (c == '^') result = pow(val2, val1);

            st = push(st, result);
        }
    }
    return result;
}

int main()
{
    cout << "RPN Calculator\n"
            "Input the number of variables: ";
    int n;
    cin >> n;
    double *values = new int[n];

    cout << "Input values of variables. \n";
    for (int i = 0; i < n; ++i)
    {
        cout << char('a' + i) << " = ";
        cin >> values[i];
    }
    cout << "Now, input the expression in infix form:\n";
    string source;
    cin >> source;
    string rpn = convert(source);
    cout << "This expression in RPN: " << rpn << " = " << calculate(rpn, values);
    return 0;
}
