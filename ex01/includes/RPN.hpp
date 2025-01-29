#ifndef RPN_HPP
# define RPN_HPP

#include <stack>

class RPN
{
    private:
        RPN(const RPN & o);
        RPN& operator=(const RPN & o);
    public:
        std::stack<int> stackNumber;
        std::stack<char> stackOp;
        std::stack<int> stack;
        RPN();
        ~RPN();
};

#endif