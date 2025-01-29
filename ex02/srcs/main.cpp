#include "PmergeMe.hpp"
#include <cstdlib> // atoi

int parsing(int argc, char **argv, PmergeMe &p)
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
        p.vec.push_back(atoi(argv[i]));
        i++;
    }
    return 0;
}

void sort_vec(PmergeMe &p)
{
    size_t i = 0;
 
    p.printVector(p.vec);


    while (i + 1 < p.vec.size())
    {
        if (p.vec[i] > p.vec[i + 1])
            std::swap(p.vec[i], p.vec[i + 1]);
        i = i + 2;
    }

    p.printVector(p.vec);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Need arguments" << std::endl;
        return 1;
    }
    PmergeMe p;

    if (parsing(argc, argv, p) == 1)
    {
        std::cerr << "Only positiv int" << std::endl;
        return 1;
    }
    sort_vec(p);

    return 0;
}