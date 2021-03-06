#pragma once
#include "Base.h"

class First : public Base
{
public:
	First(std::string shelf = "", bool t = false);
	First(const Base * b);
	~First(){};
	virtual std::string sortCMYK();

private:
	void takeFewFours(std::string & text, int &pos, int &L, int count);
	void loopNearEnd(std::string & text, int &pos, int &L, int x);
	void moveToEnd(std::string & text, int &pos, int &L, int x);
	std::string findPrefix(const std::string & text, int L);
	std::string brutal(std::string & , int );
};