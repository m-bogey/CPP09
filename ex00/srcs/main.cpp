#include "BitcoinExchange.hpp"
#include <sstream>
#include <fstream>
#include <cstdlib> //atof

int parsing(std::string line);

int main(int argc, char **argv)
{
	(void)argv;
    if(argc != 2)
    {
        std::cerr << "Need 1 file !" << std::endl;
        return 1;
    }
	std::ifstream file(argv[1]);
	if (!file)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	std::ifstream fileDataCSV("data.csv");
	if (!fileDataCSV)
	{
		std::cerr << "Error: could not open .csv." << std::endl;
		file.close();
		return 1;
	}

	BCE b;
	std::string line;
	while (std::getline(fileDataCSV, line))
	{
		b.DataCSV[line.substr(0,10)] = atof(line.substr(11).c_str());
	}
	//for (std::map<std::string, float>::iterator it = b.DataCSV.begin();it != b.DataCSV.end(); ++it)
	//	std::cout << it->first << " " << it->second << std::endl;

	std::map<std::string, float>::iterator it;

	while (std::getline(file, line))
	{
		if (line.compare("date | value") == 0)
			continue;
		if (parsing(line) == 1)
		{
			it = b.DataCSV.lower_bound(line.substr(0, 10));
			if (it->first != line.substr(0, 10))
			{
				if (it != b.DataCSV.begin())
				{
					it--;
					std::string test = it->first;
				}
			}
			std::cout << it->first << " => " << line.substr(13) << " = " << atof(line.substr(13).c_str()) * it->second << std::endl;
		}
	}



	file.close();
	fileDataCSV.close();

	return (0);
}

int check_char_end_line(std::string line)
{
	if ((line[13] < '0' || line[13] > '9') && line[13] != '-')
		return 0;
	for (int i = 14; line[i]; ++i)
	{
		if (line[i] < '0' || line[i] > '9')
			return 0;
	}
	return 1;
}

int check_date(std::string line)
{
	for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7)
		{
			if (line[i] != '-')
				return 0;
		}
		else
		{
			if (line[i] < '0' || line[i] > '9')
				return 0;
		}
	}

	int year = std::atoi(line.substr(0, 4).c_str());
	int month = std::atoi(line.substr(5, 2).c_str());
	int day = std::atoi(line.substr(8, 2).c_str());

	if (year < 2009 || year > 2026)
		return 0;
	if (month < 1 || month > 12)
		return 0;
	int days_in_month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (month == 2 && (year % 4 == 0)) // voir le calcul bix
		days_in_month[1] = 29;
	if (day < 1 || day > days_in_month[month - 1])
		return 0;

	if (year == 2009 && month == 1 && day == 1)
		return 0;

	return 1;
}

int parsing(std::string line)
{
	if (line.size() < 14 || line.substr(10, 3).compare(" | ") != 0)
	{
		std::cout << "Error : bad input => " << line << std::endl;
		return (0);
	}
	if (check_char_end_line(line) == 0)
	{
		std::cout << "Error : bad input => " << line << std::endl;
		return (0);
	}
	if (check_date(line) == 0)
	{
		std::cout << "Error : bad input => " << line << std::endl;
		return (0);
	}
	if (line[13] == '-')
	{
		std::cout << "Error: not a positive number" << std::endl;
		return 0;
	}
	if (line.size() > 17 || (line.size() == 17 && line.substr(13).compare("1000") != 0))
	{
		std::cout << "Error: too large a number." << std::endl;
		return (0);
	}
	
	return (1);
}