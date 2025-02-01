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
        std::vector<int> vec_pend;
        std::vector<int> id_vec;
        std::deque<int> deq;

        PmergeMe();
        ~PmergeMe();

        void printVector(std::vector<int>& vec);
};

#endif