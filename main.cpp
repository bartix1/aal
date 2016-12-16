#include <iostream>
#include "Robot.h"
#include <string>
#include "Second.h"
#include <assert.h>
#include "Generator.h"

std::string ORDER = "CMYK";

std::pair<std::string, std::vector<int>> getResult(std::string shelf)
{
	std::string res;
	std::vector<int> counter(4, 0);
	for (unsigned i = 0; i < shelf.size(); ++i)
		++counter[ORDER.find(shelf[i])];
	int quads = *std::min_element(counter.begin(), counter.end());
	for (int i = 0; i < quads; ++i)
		res += "CMYK";
	for (int i = 0; i < 4; ++i)
		counter[i] -= quads;
	return std::make_pair(res, counter);
}

void checkIfCorrect(std::string shelf, std::string sorted)
{
	if (shelf.length() <= 4)
	{
		assert(true);
		return;
	}
	if (shelf.length() == 5)
	{
		bool pos = true;
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 4; ++j)
				if (shelf[(i + j) % 5] != ORDER[j])
				{
					pos = false;
					break;
				}
			if (pos)
			{
				std::string tmp = "CMYK" + shelf.substr((i-1)%5,1);
				assert(sorted == tmp);
				return;
			}
			pos = true;
		}
		assert(true);
		return;
	}
	std::pair<std::string, std::vector<int>> tmp = getResult(shelf);
	assert(sorted.substr(0, tmp.first.length()) == tmp.first);
	std::string tip = sorted.substr(tmp.first.length());
	std::vector<int> counter(4, 0);
	for (unsigned i = 0; i < tip.size(); ++i)
		++counter[ORDER.find(tip[i])];
	assert(counter == tmp.second);
}


int main(int argc, char ** argv)
{
	try {
		Generator gen;
		gen.setLength(5);
		for (int i = 0; i < 1000; ++i)
		{
			std::string shelf = gen.generate();
			Robot r(shelf);
			Second s(shelf);
			std::string res1 = r.sortCMYK();
			std::string res2 = s.sortCMYK();
			checkIfCorrect(shelf, res1);
			checkIfCorrect(shelf, res2);
			if(i%10 == 0)
				std::cout << i/10 + 1 << "% completed...\n";
		}
	}
	catch (MyException e)
	{
		std::cout << e.shelf << std::endl << e.beg << std::endl << e.prefix << std::endl << e.text << std::endl;
		throw;
	}
	system("pause");
}