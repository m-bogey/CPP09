#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}
PmergeMe::~PmergeMe()
{}

void PmergeMe::printVector(std::vector<int>& vec)
{
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printVector(std::vector<std::pair<int, int> >& vec)
{
    int size = vec.size();

    for (int i = 0; i < size; ++i)
        std::cout << vec[i].first << " ";
    std::cout << std::endl;
    for (int i = 0; i < size; ++i)
        std::cout << vec[i].second << " ";
    std::cout << std::endl;
}

