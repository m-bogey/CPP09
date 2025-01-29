#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>

class BCE
{
    private:
        BCE(const BCE & o);
        BCE& operator=(const BCE & o);
    public:
        std::map<std::string, float> DataCSV;
        BCE();
        ~BCE();
};

#endif