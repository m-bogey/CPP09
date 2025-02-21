#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <utility> // std::pair
#include <cstdlib> // atoi
#include <algorithm> // std::remove
#include <iterator> // std::next

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
        void    recursiveContainer(size_t lvl, Container& c, Container& pend, Container& max)
        {
            size_t x = lvl - 1;
            size_t y = (lvl * 2) - 1;
			size_t compteur = 0;
			size_t xx = x;
			size_t yy = y;
			size_t xxx = x;
			size_t yyy = y;

			if (x >= c.size() || y >= c.size())
				return;

            while (y < c.size())
            {
                if (c[x].first > c[y].first)
                {
                    for (size_t i = 0; i < lvl; ++i)
                        std::swap(c[x - i], c[y - i]);
                }
                x += lvl * 2;
                y += lvl * 2;
				compteur++;
            }
            if (compteur > 1)
                recursiveContainer(lvl * 2, c, pend, max);
			while (yy < c.size())
            {
                if (c[xx].first > c[yy].first)
                {
                    for (size_t i = 0; i < lvl; ++i)
                        std::swap(c[xx - i], c[yy - i]);
                }
                xx += lvl * 2;
                yy += lvl * 2;
				compteur++;
            }

            identifyElemContainer(lvl, c);
			get_pend(c, pend);
/*			std::cout << "--------- lvl = " << lvl << " -----------" << std::endl;
			std::cout << "Main : ";
			printContainer(c);
			std::cout << "Pend : ";
			printContainer(pend);
			std::cout << "-------------------------------" << std::endl;
*/			//jacobsthal(pend, lvl);
			putPendInMain(lvl, c, pend, max);
			
			while (yyy < c.size())
            {
                if (c[xxx].first > c[yyy].first)
                {
                    for (size_t i = 0; i < lvl; ++i)
                        std::swap(c[xxx - i], c[yyy - i]);
                }
                xxx += lvl * 2;
                yyy += lvl * 2;
				compteur++;
            }

        }

        template <typename Container>
        void identifyElemContainer(size_t lvl, Container& c)
        {
			int lvl_int = static_cast<int>(lvl);
            int compteur = 0;
            size_t i = 0;
            int id = 0;
			size_t size = c.size();

            while (i < size)
            {
				if (c.size() - (i) < lvl && compteur == 0)
					id = -1;
                c[i].second = id;
                compteur++;
				if (compteur == lvl_int && id != -1)
				{
					compteur = 0;
					id++;
				}
                i++;
            }
        }

		template <typename Container>
		void get_pend(Container& c, Container& pend)
		{
			typename Container::iterator it;

			for(size_t i = 0; i < c.size(); ++i)
			{
				if ((c[i].second != 0 && c[i].second % 2 == 0) || c[i].second == -1)
				{
					pend.push_back(c[i]);
					it = std::find(c.begin(), c.end(), c[i]);
					if (it != c.end())
						c.erase(it);
					i--;
				}
			}
		}

		template <typename Container>
		void putPendInMain(size_t lvl, Container& c, Container& pend, Container& max)
		{
			int compteur = 0;
			typename Container::iterator it;
			size_t emplacement;

			while (lvl <= pend.size())
			{
				for (size_t i = 0; i < c.size(); ++i)
				{
					if (compteur == static_cast<int>(lvl - 1))
					{
						max.push_back(c[i]);
						compteur = -1;
					}
					compteur++;
				}
				it = std::upper_bound(max.begin(), max.end(), pend[lvl - 1]);			
				if (it == max.end())
					emplacement = c.size();
				else
				{
					emplacement = it - max.begin();
					emplacement *= (lvl);
					if (emplacement > c.size())
						emplacement = c.size();
				}
				c.insert(c.begin() + emplacement, pend.begin(), pend.begin() + lvl);
				pend.erase(pend.begin(), pend.begin() + lvl);
				max.clear();
			}
			while (pend.size() != 0)
			{
				c.push_back(pend[0]);
				pend.erase(pend.begin());
			}
		}

		template <typename Container>
		void	jacobsthal(Container& pend, size_t lvl)
		{
			size_t size = pend.size();
			size_t nb1 = 3;
			size_t nb2 = 5;
			size_t sum = nb1 * 2 + nb2;
			size_t x;
			size_t y;

			if (size >= lvl * 2)
			{
				for(size_t i = 0; i < lvl; ++i)
					std::swap(pend[(lvl - 1) - i], pend[(lvl * 2 - 1) - i]);
			}
			if (size >= lvl * 4)
			{
				for(size_t i = 0; i < lvl; ++i)
					std::swap(pend[(lvl * 3 - 1) - i], pend[(lvl * 4 - 1) - i]);
			}
			while (sum <= size) // 11 5 
			{
				x = nb2;
				y = sum;
				while (x < y)
				{
					for(size_t i = 0; i < lvl; ++i)
						std::swap(pend[(lvl * x - 1) - i], pend[(lvl * y - 1) - i]);
					x++;
					y--;
				}
				if (sum == size)
					break;
				nb1 = nb2;
				nb2 = sum;
				sum = nb1 * 2 + nb2;
				if (sum > size)
					sum = size;
			}
		}

        template <typename Container>
        void printContainer(const Container& container)
        {
            typename Container::const_iterator it;
            for(it = container.begin(); it != container.end(); ++it)
                std::cout << it->first << " ";
            std::cout << std::endl;
        //    for(it = container.begin(); it != container.end(); ++it)
        //        std::cout << it->second << " ";
        //    std::cout << std::endl;
        }
};

#endif