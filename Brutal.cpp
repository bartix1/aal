#include "Brutal.h"

Brutal::Brutal(std::string s, bool t) : Base(s, t){};

std::string Brutal::sortCMYK()
{
	std::string prefix = getResult(shelf).first;
	if(trace)
		return brutalSortWithTrace(shelf, prefix, "");
	return brutalSort(shelf, prefix, "");
}