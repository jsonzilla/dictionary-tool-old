#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <utility>

typedef unsigned long long ull;

const std::string ERRORPARAMETER = "error: parameter";
const std::string ERROROPENING = "error: openin";

void InsertCount(const std::string& token,
		std::map<std::string, ull>& dict) {
	std::map<std::string, ull>::iterator it = dict.find(token);
	if (it != dict.end()) {
		(it->second)++;
	} else {
		dict.insert(std::pair<std::string, ull>(token, 1));
	}
}

int main(int ac, char* av[]) {
	if (ac != 2) {
		std::cout << ERRORPARAMETER << std::endl;
		return 8;
	}

	std::ifstream file;
	file.open(av[1]);

	if (!file.is_open()) {
		std::cout << ERROROPENING << std::endl;
		return 1;
	}

	std::map<std::string, ull> dict;
	std::string line;

	while (std::getline(file, line))
	{
		std::string::iterator prev;
		std::string::iterator pos = std::find_if(line.begin(), line.end(), isalpha);
		while (pos != line.end())
		{
			prev = std::find_if_not(pos, line.end(), isalpha);
			std::string token(pos, prev);
			std::transform(token.begin(), token.end(), token.begin(), ::tolower);

			InsertCount(token, dict);

			pos = std::find_if(prev, line.end(), isalpha);
		}
	}

	for (auto &w : dict) {
		std::cout << w.second << "," << w.first << std::endl;
	}

	file.close();

	return 0;
}
