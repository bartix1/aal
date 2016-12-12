#pragma once
#include <iostream>

class Robot
{
public:
	Robot(std::string shelf);
	std::string sortCMYK();

private:
	static const ORDER = 'CMYK';
	const std::string shelf;

	void takeFewFours(std::string & text, int &pos, int &L, int count);
	void loopNearEnd(std::string & text, int &pos, int &L, int x);
	void moveToEnd(std::string & text, int &pos, int &L);
	std::string lessThanSixSort() {};
	std::string brutal(std::string & , int );
};