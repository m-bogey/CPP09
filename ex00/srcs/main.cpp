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

int parsing(std::string line)
{
	if (line.size() < 14 || line.substr(10, 3).compare(" | ") != 0)
	{
		std::cout << "Error : bad input => " << line << std::endl;
		return (0);
	}
	if (line.size() > 17 || (line.size() == 17 && line.substr(13).compare("1000") != 0))
	{
		std::cout << "Error: too large a number." << std::endl;
		return (0);
	}
	
	return (1);
}