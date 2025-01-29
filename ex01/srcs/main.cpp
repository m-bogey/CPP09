#include "RPN.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

int parsing(std::string s, RPN &r)
{
    int nb = 0;
    int op = 0;
    int i = 0;
    while (s[i])
    {
        if ((s[i] < '0' || s[i] > '9') && s[i] != '-' && s[i] != '+'
            && s[i] != '/' && s[i] != '*' && s[i] != ' ')
            return 1;
        i++;
    }
    i--;
    while (i >= 0)
    {
        if ((s[i] >= '0' && s[i] <= '9'))
        {
            r.stackNumber.push(s[i] - '0');
            nb++;
        }
        if (s[i] == '-' || s[i] == '+'
            || s[i] == '/' || s[i] == '*')
        {
            r.stackOp.push(s[i]);
            op++;
        }
        i--;
    }
    if ((nb - 1) != op)
        return 1;
    return 0;
}

int calculRPN(int a, int b, RPN &r)
{
    char op = r.stackOp.top();

    if (!r.stackOp.empty())
        r.stackOp.pop();
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
    {
        if (b == 0)
        {
            std::cerr << "Error : div by 0" << std::endl;
            exit(1);
        }
        return a / b;
    }
    return 0;
}

int resultRPN(RPN &r)
{
    int a;
    int b;
    bool is_first = true;
    while (!r.stackNumber.empty())
    {
        if (is_first)
        {
            a = r.stackNumber.top();
            r.stackNumber.pop();
        }
        else
        {
            a = r.stack.top();
            r.stack.pop();
        }
        b = r.stackNumber.top();
        r.stackNumber.pop();
        r.stack.push(calculRPN(a, b, r));
        is_first = false;
    }

    a = r.stack.top();
    std::cout << a << std::endl;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Need 1 argument" << std::endl;
        return 1;
    }

    RPN r;

    if (parsing(argv[1], r) == 1)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    resultRPN(r);
    return 0;
}