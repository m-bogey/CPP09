#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <utility> // std::pair

class PmergeMe
{
    private:
        PmergeMe(const PmergeMe & o);
        PmergeMe& operator=(const PmergeMe & o);
    public:
        std::vector<int> vec;
        std::vector<int> id_vec;
        std::vector<std::pair<int, int> > vecPairs;
        std::vector<std::pair<int, int> > vec_pend;
        std::vector<std::pair<int, int> > vec_odd;

        std::deque<int> deq;

        PmergeMe();
        ~PmergeMe();

        void printVector(std::vector<int>& vec);
        void printVector(std::vector<std::pair<int, int> >& vec);
};

#endif