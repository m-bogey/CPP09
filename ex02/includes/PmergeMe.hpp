#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>

class PmergeMe
{
    private:
        PmergeMe(const PmergeMe & o);
        PmergeMe& operator=(const PmergeMe & o);
    public:
        std::vector<int> vec;

        PmergeMe();
        ~PmergeMe();

        void printVector(std::vector<int>& vec);
};

#endif