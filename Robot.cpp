#include "Robot.h"

Robot::Robot(std::string s) : shelf(s);

std::string Robot::sortCMYK()
{
	if (shelf.size < 6)
		return lessThanSixSort();

	int pos, L = 0, 0;
	size_t x;
	std::string text(shelf);
	while (text.size - pos > 6)
	{
		int x = text.find(shelf, pos);
		if (x == std::string::npos)
			return text;
		if ((x - i) % 4 == 0)
			takeFewFours(text, pos, L, (x-i)/4);
		else if (n - x > 4)
			moveToEnd(text, pos, L);
		else
			loopNearEnd(text, pos, L, x);
	}
	return brutal(text, L);
}

void Robot::takeFewFours(std::string & text, int &pos, int &L, int count)
{
	for (int i = 0; i < count, ++i)
		move(text, pos);
	
	pos += 1;
	L += 1;
}

void Robot::moveToEnd(std::string & text, int &pos, int &L)
{
	move(text, pos);
	int x = text.size - 4;
	int y = 4 - (x - pos) % 4;
	if (y != 4)
	{
		move(text, x-y);
		x += y;
	}
	takeFewFours(text, pos, L, (x-pos)/4);
}

void Robot::loopNearEnd(std::string & text, int &pos, int &L, int x)
{
	while ((x - pos) % 4 != 0)
	{
		move(text, text.size - 5);
		x += 1;
		if (x == text.size)
			x = text.size - 5;
	}
	takeFewFours(text, pos, L, (x - pos) % 4);
}

std::string Robot::findPrefix(const std::string & text, int L)
{

}

std::string Robot::brutal(std::string & text, int L)
{
	std::string prefix = findPrefix(text, L);
	std::string lastLetters = robot(text.substr(text.size - 6, 6), prefix);
	return text.replace(text.size - 6, 6, lastLetters);
}