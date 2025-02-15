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
            identifyElemContainer(lvl, c);
			get_pend(c, pend);
			putPendInMain(lvl, c, pend, max);
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
			typename Container::iterator it;

			for(size_t i = 0; i < c.size(); ++i)
			{
				if (c[i].second != 0 && c[i].second % 2 == 0)
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
        void printContainer(const Container& container)
        {
            typename Container::const_iterator it;
            for(it = container.begin(); it != container.end(); ++it)
                std::cout << it->first << " ";
            std::cout << std::endl;
//            for(it = container.begin(); it != container.end(); ++it)
//                std::cout << it->second << " ";
//            std::cout << std::endl;
        }
};

#endif