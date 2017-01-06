#include "Brutal.h"
#include <algorithm>
#include <iostream>

Brutal::Brutal(std::string s) : Base(s, 0){};


std::string ORDER = "CMYK";

std::pair<std::string, std::vector<int>> getResult(std::string shelf)
{
	std::string res;
	std::vector<int> counter(4, 0);
	for (unsigned i = 0; i < shelf.size(); ++i)
		++counter[ORDER.find(shelf[i])];
	int quads = *std::min_element(counter.begin(), counter.end());
	for (int i = 0; i < quads; ++i)
		res += "CMYK";
	for (int i = 0; i < 4; ++i)
		counter[i] -= quads;
	return std::make_pair(res, counter);
}

std::string Brutal::sortCMYK()
{
	std::string prefix = getResult(shelf).first;
	//std::cout << prefix << std::endl;
	return brutalSort(shelf, prefix);
}


std::string Brutal::brutalSort(std::string text, const std::string & prefix)
{
	std::unordered_map<std::string, int> memory;
	std::deque<std::string> open_nodes;
	open_nodes.push_back(text);
	while (!open_nodes.empty())
	{
		text = open_nodes.front();
		open_nodes.pop_front();
		if (text.substr(0, prefix.size()) == prefix)
			return text;
		if (memory.find(text) != memory.end())
			continue;
		memory.emplace(std::make_pair(text, 0));
		std::string tmp(text);
		for(int i = 0; i < int(text.size())-4; ++i)
		{
			move(tmp, i, false);
			open_nodes.push_back(tmp);
			tmp = text;
		}
	}
	return shelf;
}
