#include "Brutal.h"
#include <algorithm>
#include <iostream>

Brutal::Brutal(std::string s, bool t) : Base(s, t){};

std::string Brutal::sortCMYK()
{
	std::string prefix = getResult(shelf).first;
	std::string text;
	if(trace)
	{
		text = brutalSortWithTrace(shelf, prefix, "");
		moves_history.push_back(text);
	}
	text = brutalSort(shelf, prefix, "");
	return text;
}