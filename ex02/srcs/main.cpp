#include "PmergeMe.hpp"

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
	std::vector<std::pair<int, int> > vec;
	std::vector<std::pair<int, int> > vec_pend;

	p.fillContainer(argc, argv, vec);
	p.recursiveContainer(1, vec, vec_pend);


	//----------------- Fin Vector ---------------------
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

void swapper(PmergeMe &p, size_t i, size_t j, size_t x)
{
    ssize_t nb_swap = x - 1; //=> nb d'element a swap

    while (nb_swap >= 0)
    {
        std::swap(p.vec[i - nb_swap], p.vec[j - nb_swap]);
        nb_swap--;
    }
}

size_t recursive_vec(PmergeMe &p, size_t x, size_t y, size_t turn)
{
    size_t i = x - 1;
    size_t j = y - 1;
    int     compteur = 0;

    //p.printVector(p.vec);
    
    while (j < p.vec.size())
    {
        if (p.vec[i] > p.vec[j])
            swapper(p, i, j, x);
       // std::cout << " i = " << i << " j = " << j << std::endl;
        i = i + y;
        j = i + x;
        compteur++;
    }

    p.printVector(p.vec);
    //std::cout << "---- x et y avant " << x << " " << y << std::endl;
    if (x == 1)
        x = 2;
    else
        x = (x) * 2;
    y = (x * 2);

    turn++;
    //std::cout << "---- x et y apres " << x << " " << y << "size du vec " << p.vec.size()<<std::endl;
    if (compteur == 1)
        return turn;
    return recursive_vec(p, x, y, turn);
}


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

void create_vec_pair(PmergeMe &p)
{
    int size = p.vec.size();

    for (int i = 0; i < size; ++i)
        p.vecPairs.push_back(std::make_pair(p.vec[i], p.id_vec[i]));
    std::cout <<"--------- Pair ----------" << std::endl;
    p.printVector(p.vecPairs);
    
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