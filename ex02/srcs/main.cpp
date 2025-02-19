#include "PmergeMe.hpp"
#include <ctime>

int parsing(int argc, char **argv); // TODO: gerer int max

int main(int argc, char **argv)
{
    PmergeMe p;

    if (argc < 2)
    {
        std::cerr << "Need arguments" << std::endl;
        return 1;
    }


    if (parsing(argc, argv) == 1)
    {
        std::cerr << "Only positiv int" << std::endl;
        return 1;
    }
	//------------------- Vector ---------------------
    //clock_t start_vec = clock();

	std::vector<std::pair<int, int> > vec;
	std::vector<std::pair<int, int> > vec_pend;
    std::vector<std::pair<int, int> > vec_max;

	p.fillContainer(argc, argv, vec);
    // std::cout << "Before: ";
    // p.printContainer(vec);
	p.recursiveContainer(1, vec, vec_pend, vec_max);
    // std::cout << "After:  ";
    p.printContainer(vec);

    //clock_t end_vec = clock();
    //double time_vec = double(end_vec - start_vec) / CLOCKS_PER_SEC;
	//----------------- Fin Vector ---------------------

    //------------------- Deque ---------------------
    //  clock_t start_deq = clock();

	//  std::deque<std::pair<int, int> > deq;
	//  std::deque<std::pair<int, int> > deq_pend;
    //  std::deque<std::pair<int, int> > deq_max;

	//  p.fillContainer(argc, argv, deq);
	//  p.recursiveContainer(1, deq, deq_pend, deq_max);

    //  clock_t end_deq = clock();
    //  double time_deq = double(end_deq - start_deq) / CLOCKS_PER_SEC;
	//----------------- Fin Deque ---------------------

    //std::cout << "Time to process a range of  " << vec.size() << " elements with std::vector : " << time_vec << " us" << std::endl;
    //std::cout << "Time to process a range of  " << deq.size() << " elements with std::deque : " << time_deq << " us" << std::endl;
    return 0;
}

int parsing(int argc, char **argv)
{
    int i = 1;
    int j;
    while(i < argc)
    {
        j = 0;
        while(argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return 1;
            j++;
        }
        i++;
    }
    return 0;
}



/*

int my_binary_search(const std::vector<std::pair<int, int> >& vec, int target)
{
	int left = 0;
	int right = vec.size();
	int mid;

	while (left < right)
	{
		mid = left + (right - left) / 2;
		if (vec[mid].first < target)
			left = mid + 1;
		else
			right = mid;
	}
	return left;
}

void put_pend_and_odd_in_main(PmergeMe &p, size_t turn)
{
	size_t target_pend = turn;
	std::cout << "taget pend = " << target_pend << std::endl;
	if (target_pend % 2 != 0)
		target_pend--;
	target_pend--;

	std::cout << "taget pend = " << target_pend << std::endl;
	//binary search: trouver l'emplacement ou mettre l'element dans main
	int insertPos = my_binary_search(p.vecPairs, p.vec_pend[target_pend].first);
	
	std::cout << "insert pos = " << insertPos << std::endl;
	//mettre l'element dans main

	//pour odd voir le nb d'elem
}

void classify_in_main_pend_and_odd(PmergeMe &p)
{

    for (size_t i = 0; i < p.vecPairs.size(); ++i)
    {
        if (p.vecPairs[i].second != 0 && p.vecPairs[i].second % 2 == 0)
        {
            p.vec_pend.push_back(p.vecPairs[i]);
            p.vecPairs.erase(std::remove(p.vecPairs.begin(), p.vecPairs.end(), p.vecPairs[i]), p.vecPairs.end());
            i--;
        }
		if (p.vecPairs[i].second == -1)
        {
			std::cout << i << std::endl;
            p.vec_odd.push_back(p.vecPairs[i]);
            p.vecPairs.erase(std::remove(p.vecPairs.begin(), p.vecPairs.end(), p.vecPairs[i]), p.vecPairs.end());
            i--;
        }
    }
    std::cout << std::endl;
    std::cout << "----- main -----" << std::endl;
    p.printVector(p.vecPairs);
    std::cout << "----- pend -----" << std::endl;
    p.printVector(p.vec_pend);
	std::cout << "----- odd -----" << std::endl;
    p.printVector(p.vec_odd);
}*/