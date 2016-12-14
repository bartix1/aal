#pragma once
#include "Base.h"

class Robot : public Base
{
public:
	Robot(std::string shelf, bool t = false);
	virtual std::string sortCMYK();

private:
	void takeFewFours(std::string & text, int &pos, int &L, int count);
	void loopNearEnd(std::string & text, int &pos, int &L, int x);
	void moveToEnd(std::string & text, int &pos, int &L, int x);
	std::string findPrefix(const std::string & text, int L);
	std::string brutal(std::string & , int );
};