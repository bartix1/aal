#include "Base.h"

std::string Base::ORDER = "CMYK";

Base::Base(std::string s, bool t) : shelf(s), trace(t)
{
	moves_history.push_back(s);
}

std::vector<std::string> Base::getHistory() const
{
	return moves_history;
}
;

std::string Base::sortLastSix(std::string &text, const std::string & prefix)
{
	std::unordered_map<std::string, int> memory;
	std::vector<std::string> route;
	std::string beg = text.substr(0, text.length() - 6);
	std::string last_six = text.substr(text.length() - 6);
	if(trace)
		return sortLastSixBodyWithTrace(last_six, prefix, route, beg);
	return sortLastSixBody(last_six, prefix, route, beg);
}


std::string Base::sortLastSixBody(std::string text, const std::string & prefix, std::vector<std::string> route, std::string beg)
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
		move(tmp, 0, false);
		open_nodes.push_back(tmp);
		tmp = text;
		move(tmp, 1, false);
		open_nodes.push_back(tmp);
	}
	throw;
}


std::string Base::sortLastSixBodyWithTrace(std::string text, const std::string & prefix, std::vector<std::string> route, std::string beg)
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
		move(tmp, 0, false);
		open_nodes.push_back(tmp);
		tmp_v.push_back(tmp);
		routes.push_back(tmp_v);
		tmp = text;
		tmp_v = x;
		move(tmp, 1, false);
		open_nodes.push_back(tmp);
		tmp_v.push_back(tmp);
		routes.push_back(tmp_v);
	}
	throw;
}




void Base::move(std::string & text, int pos, bool valid)
{
	text = text.substr(0, pos) + text.substr(pos + 4) + text.substr(pos, 4);
	if (trace && valid)
		moves_history.push_back(text);
}

std::string Base::lessThanSixSort() 
{ 
	if (shelf.length() < 4)
		return shelf;
	if (shelf.length() == 4 && shelf == "CMYK")
		return shelf;
	if (shelf.length() == 4 && shelf != "CMYK")
		throw ;
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
		throw;
	}

		
};	