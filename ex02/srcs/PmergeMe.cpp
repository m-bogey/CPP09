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