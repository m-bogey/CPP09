#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>

class BCE
{
    private:
    public:
        std::map<std::string, float> DataCSV;
        BCE();
        BCE(const BCE & o);
        BCE& operator=(const BCE & o);
        ~BCE();
};

#endif