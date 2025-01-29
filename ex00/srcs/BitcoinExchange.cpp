#include "BitcoinExchange.hpp"

BCE::BCE()
{}
BCE::BCE(const BCE & o)
{
	DataCSV = o.DataCSV;
}
BCE& BCE::operator=(const BCE & o)
{
	(void)o;
	return *this;
}
BCE::~BCE()
{}