#include "Base.h"

std::string Base::ORDER = "CMYK";

Base::Base(std::string s, bool t) : shelf(s), trace(t)
{
	//moves_history.push_back(s);
}

Base::Base(const Base * b) : Base(b->getShelf(), b->isTracing()){}


std::vector<std::string> Base::getHistory() const
{
	return moves_history;
}


std::string Base::sortLastSix(std::string &text, const std::string & prefix)
{
	std::string beg = text.substr(0, text.length() - 6);
	std::string last_six = text.substr(text.length() - 6);
	if(trace)
		return brutalSortWithTrace(last_six, prefix, beg);
	return brutalSort(last_six, prefix, beg);
}


std::string Base::brutalSort(std::string text, const std::string & prefix, std::string beg)
{
	std::unordered_map<std::string, int> memory;
	std::deque<std::string> open_nodes;
	open_nodes.push_back(text);
	while (!open_nodes.empty())
	{
		text = open_nodes.front();
		open_nodes.pop_front();
		if (text.substr(0, prefix.size()) == prefix)
			return beg + text;
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
	throw MyException(shelf, text, prefix, beg);
}

#include <iostream>
std::string Base::brutalSortWithTrace(std::string text, const std::string & prefix, std::string beg)
{
	std::unordered_map<std::string, int> memory;
	std::deque<std::string> open_nodes;
	std::deque<std::vector<std::string>> routes;
	open_nodes.push_back(text);
	std::vector<std::string> x(1, text);
	routes.push_back(x);
	while (!open_nodes.empty())
	{
		text = open_nodes.front();
		open_nodes.pop_front();
		x = routes.front();
		routes.pop_front();
		if (text.substr(0, prefix.size()) == prefix)
		{
			for (auto it = ++x.begin(); it != x.end(); ++it)
				moves_history.push_back(beg + *it);

			return beg + text;
		}
		if (memory.find(text) != memory.end())
			continue;
		memory.emplace(std::make_pair(text, 0));
		std::string tmp(text);
		std::vector<std::string> tmp_v(x);
		for(int i = 0; i < int(text.size())-4; ++i)
		{
			tmp_v.push_back(tmp.substr(0, i) + " | " + tmp.substr(i));
			move(tmp, i, false);
			open_nodes.push_back(tmp);
			//tmp_v.push_back(tmp.substr(0, i) + " | " + tmp.substr(i));
			routes.push_back(tmp_v);
			tmp = text;
			tmp_v = x;
		}

	}
	throw;
}


void Base::move(std::string & text, int pos, bool valid)
{
	if (trace && valid)
		moves_history.push_back(text.substr(0, pos) + " | " + text.substr(pos));
	
	text = text.substr(0, pos) + text.substr(pos + 4) + text.substr(pos, 4);
}

std::string Base::lessThanSixSort() 
{ 
	if (shelf.length() == 5)
	{
		std::string text(shelf);
		if (text.substr(0, 4) == "CMYK")
			return text;
		for (int i = 0; i < 4; ++i)
		{
			move(text, 0);
			if (text.substr(0, 4) == "CMYK")
				return text;
		}
		moves_history.clear();
		moves_history.push_back(shelf);
		return shelf;
	}
	return shelf;

}

void Base::reset(std::string s, bool t)
{
	shelf = s;
	trace = t;
	moves_history.clear();
	moves_history.push_back(s);
}	

bool Base::isTracing() const
{
	return trace;
}

std::string Base::getShelf() const
{
	return shelf;
}



std::pair<std::string, std::vector<int>> getResult(std::string shelf)
{
	std::string ORDER = "CMYK";
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