#include "Brutal.h"
#include <algorithm>
#include <iostream>

Brutal::Brutal(std::string s, bool t) : Base(s, t){};

std::string Brutal::sortCMYK()
{
	std::string prefix = getResult(shelf).first;
	//std::cout << prefix << std::endl;
	if(trace)
		return brutalSortWithTrace(shelf, prefix, "");
	return brutalSort(shelf, prefix, "");
}