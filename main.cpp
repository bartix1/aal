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
/*	Generator gen;
	gen.setLength(1000);
	for(int i =0; i < 100; ++i)
	{
		std::string shelf = gen.generate();
		Robot r(shelf);
		Second s(shelf);
		std::string res1 = r.sortCMYK();
		std::string res2 = s.sortCMYK();
		checkIfCorrect(shelf, res1);
		checkIfCorrect(shelf, res2);
		std::cout << i+1  << "% completed...\n";
	} */
	std::string shelf = "CMKCMYYYK";
	Robot r(shelf);
	Second s(shelf);
	std::string res1 = r.sortCMYK();
	std::string res2 = s.sortCMYK();
	checkIfCorrect(shelf, res1);
	checkIfCorrect(shelf, res2);
	std::cout << res2 << std::endl << std::endl;
	auto x = s.getHistory();
	for (std::vector<std::string>::iterator it = x.begin(); it != x.end(); ++it)
		std::cout << *it << std::endl;
	system("pause");
}