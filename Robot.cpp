#include "Robot.h"

Robot::Robot(std::string s, bool t) : Base(s, t) {};

std::string Robot::sortCMYK()
{
	if (int(shelf.size()) < 6)
		return lessThanSixSort();

	int pos, L;
	pos = L = 0;
	std::string text(shelf);
	while (int(text.size()) - pos > 6)
	{
		int x = text.find(ORDER[L], pos);
		if (x == std::string::npos)
			return text;
		if ((x - pos) % 4 == 0)
			takeFewFours(text, pos, L, (x-pos)/4);
		else if (int(text.size()) - x > 4)
			moveToEnd(text, pos, L, x);
		else
			loopNearEnd(text, pos, L, x);
	}
	return brutal(text, L);
}

void Robot::takeFewFours(std::string & text, int &pos, int &L, int count)
{
	for (int i = 0; i < count; ++i)
		move(text, pos);
	
	pos += 1;
	L = (L + 1) % 4;
}

void Robot::moveToEnd(std::string & text, int &pos, int &L, int x)
{
	move(text, x);
	x = int(text.size()) - 4;
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
		move(text, int(text.size()) - 5);
		x += 1;
		if (x == int(text.size()))
			x = int(text.size()) - 5;
	}
	takeFewFours(text, pos, L, (x - pos) / 4);
}

std::string Robot::findPrefix(const std::string & text, int L)
{
	std::vector<int> counter(4, 0);
	for (int i = 0; i < 6; ++i)
		++counter[ORDER.find(text[i])];

	std::string prefix, tmp;
	for (int i = 0; i < 6; ++i)
	{
		if (counter[L] > 0)
		{
			tmp += ORDER[L];
			counter[L] -= 1;
			L += 1;
			if (L == 4)
			{
				prefix += tmp;
				tmp = "";
				L = 0;
			}
		}
		else
			break;
	}
	return prefix;
}

std::string Robot::brutal(std::string & text, int L)
{
	std::string prefix = findPrefix(text.substr(text.length()-6), L);
	std::unordered_map<std::string, int> memory;
	return sortLastSix(text, prefix);
}
