#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <utility> // std::pair
#include <cstdlib> // atoi
#include <algorithm> // std::remove

class PmergeMe
{
    private:
        PmergeMe(const PmergeMe & o);
        PmergeMe& operator=(const PmergeMe & o);
    public:
        PmergeMe();
        ~PmergeMe();

        template <typename Container>
        void    fillContainer(int argc, char **argv, Container& container)
        {
            int i = 1;

            while (i < argc)
            {
                container.push_back(std::make_pair(atoi(argv[i]), 0));
                i++;
            }
        }

        template <typename Container>
        void    recursiveContainer(size_t lvl, Container& c, Container& pend)
        {
            size_t x = lvl - 1;
            size_t y = (lvl * 2) - 1;

            while (y < c.size())
            {
                if (c[x].first > c[y].first)
                {
                    for (size_t i = 0; i < lvl; ++i)
                        std::swap(c[x - i], c[y - i]);
                }
                x += lvl * 2;
                y += lvl * 2;
            }
            if (lvl * 2 < c.size())
                recursiveContainer(lvl * 2, c, pend);
            identifyElemContainer(lvl, c);
            std::cout<<"size c = "<< c.size() << " lvl = " << lvl << std::endl;
        //    printContainer(c);
		//	printContainer(pend);
			get_pend(c, pend);
			std::cout << "------- debut --------" << std::endl;
		//	printContainer(c);
		//	printContainer(pend);
			std::cout << "------- fin --------" << std::endl;
			putPendInMain(lvl, c, pend);
			printContainer(c);
			printContainer(pend);
        }

        template <typename Container>
        void identifyElemContainer(size_t lvl, Container& c)
        {
            size_t compteur = 0;
            size_t i = 0;
            size_t id = 0;
			size_t size = c.size();

            while (i < size)
            {
                c[i].second = id;
                compteur++;
				if (compteur == lvl)
				{
					compteur = 0;
					id++;
				}
                i++;
            }
        }

		template <typename Container>
		void get_pend( Container& c, Container& pend)
		{
			for(size_t i = 0; i < c.size(); ++i)
			{
				if (c[i].second != 0 && c[i].second % 2 == 0)
				{
					pend.push_back(c[i]);
					c.erase(std::remove(c.begin(), c.end(), c[i]), c.end());
					i--;
				}
			}
		}

		template <typename Container>
		void putPendInMain(size_t lvl, Container& c, Container& pend)
		{
			if (lvl >= pend.size())
			{
				// faire un binary sur les max/lvl
				// insert les element dans main et retire de pend
			}

			while (pend.size() != 0)
			{
				c.push_back(pend[0]);
				pend.erase(std::remove(pend.begin(), pend.end(), pend[0]), pend.end());
			}
		}

        template <typename Container>
        void printContainer(const Container& container)
        {
            typename Container::const_iterator it;
            for(it = container.begin(); it != container.end(); ++it)
                std::cout << it->first << " ";
            std::cout << std::endl;
            for(it = container.begin(); it != container.end(); ++it)
                std::cout << it->second << " ";
            std::cout << std::endl;
        }
};

#endif