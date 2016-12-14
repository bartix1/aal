#pragma once
#include "Base.h"
#include <algorithm>
#include <set>

class Second : public Base
{
public:
	Second(std::string s, bool t = false);
	virtual std::string sortCMYK();
	
private:
	void arrangeNextFours(std::string &text, int pos, std::set<char> prev);
	void arrangeTip(std::string &text, std::set<char> &prev, int pos, int quads);
	bool findOneElement(std::set<char> &prev, std::vector<char> &list);
	int make_quads(std::string &text);
};