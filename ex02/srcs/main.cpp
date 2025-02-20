#include "PmergeMe.hpp"
#include <ctime>
#include <climits>
#include <cerrno>

int parsing(int argc, char **argv);
int checkIntMax(int argc, char **argv);

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
    if (checkIntMax(argc, argv) == 1)
    {
        std::cerr << "Only positiv int < int max" << std::endl;
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

int checkIntMax(int argc, char **argv)
{
    int i = 1;
    char *endptr;
    errno = 0;
    long num;

    while(i < argc)
    {
        num = std::strtol(argv[i], &endptr, 10);
        if (errno == ERANGE || num > INT_MAX)
            return 1;
        i++;
    }
    return 0;
}