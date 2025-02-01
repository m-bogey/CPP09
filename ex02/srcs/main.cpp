#include "PmergeMe.hpp"
#include <cstdlib> // atoi
#include <algorithm> // std::remove

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
        p.deq.push_back(atoi(argv[i])); // voir pour deque
        i++;
    }
    return 0;
}

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

void identify_elem_vec(PmergeMe &p, size_t &turn)
{
    size_t  i = 0;
    int     id = 0;
    size_t  compteur = 0;
    int     turn_limit = static_cast<int>(turn);

    while (i < p.vec.size())
    {
        p.id_vec.push_back(id);
        compteur++;
        if (compteur == turn && id != -1)
        {
            compteur = 0;
            id++;
            if (id >= turn_limit)
                id = -1;
        }
        i++;
    }
    std::cout << "------------- identifiant pour classer vector ------------" << std::endl;
    p.printVector(p.id_vec);
}

void classify_in_main_and_pend(PmergeMe &p)
{
    size_t j = 0; // pour tomber sur le bon elem quand on remove

    for (size_t i = 0; i < p.id_vec.size(); ++i)
    {
        if (p.id_vec[i] != 0 && p.id_vec[i] % 2 == 0)
        {
            p.vec_pend.push_back(p.vec[i - j]);
            p.vec.erase(std::remove(p.vec.begin(), p.vec.end(), p.vec[i - j]), p.vec.end());
            j++;
        }
    }
    std::cout << std::endl;
    std::cout << "----- main -----" << std::endl;
    p.printVector(p.vec);
    std::cout << "----- pend -----" << std::endl;
    p.printVector(p.vec_pend);
}

void put_pend_in_main(PmergeMe &p, size_t turn)
{
    // voir pour binary search
    size_t  pos = turn - 1;
    std::vector<int>::iterator it = p.vec.begin() + pos;
    size_t i = pos;

    while ( it != p.vec.end() )
    {
        std::cout << "pend: " << p.vec_pend[pos] << " *it: " << *it << " +it: "<< *(it + turn) << std::endl;
        if (p.vec_pend[pos] > *it
            && p.vec_pend[pos] < *(it + turn))
        {
            p.vec.insert(it + 1, p.vec_pend.begin(), p.vec_pend.end());
            break;
        }
        
        i = i + pos;
        if (i + turn < p.vec.size())
            it = it + turn;
        else
        {
            std::cout << "echec" << std::endl;
            break;
        }

    }
    p.printVector(p.vec);
        // metre pend a la pos : p.vec[i + pos]
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Need arguments" << std::endl;
        return 1;
    }
    PmergeMe p;
    size_t turn;

    if (parsing(argc, argv, p) == 1)
    {
        std::cerr << "Only positiv int" << std::endl;
        return 1;
    }
    turn = recursive_vec(p, 1, 2, 0);
    std::cout << turn << std::endl;
    identify_elem_vec(p, turn);
    classify_in_main_and_pend(p);
    put_pend_in_main(p, turn); // voir binary search
    
    return 0;
}