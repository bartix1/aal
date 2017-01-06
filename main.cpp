#include <iostream>
#include <cstdlib> 
#include <fstream>
#include <boost/program_options.hpp>

#include "Diagram.h"

namespace po = boost::program_options;

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
				int x = i-1;
				if (x < 0)
					x = 4;
				std::string tmp = "CMYK" + shelf.substr(x,1);
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


void printHistory(std::vector<std::string> history)
{
	for(auto it = history.begin(); it != history.end(); ++it)
		std::cout << *it << std::endl;
}


Base * chooseAlg(po::variables_map vm, bool h)
{
	if (vm["algorithm"].as<int>() == 1)
		return new First("", h);
	if (vm["algorithm"].as<int>() == 2)
		return new Second("", h);
	throw;
}

std::vector<std::string> readData(std::string f_name)
{
	std::ifstream file;
	file.open(f_name);
	std::vector<std::string> to_process;
	if(!file.is_open())
	{
		std::cout << "Unable to open file" << std::endl;
		return to_process;
	}
	std::string line;
	while(getline(file, line))
		to_process.push_back(line);
	return to_process;
}

int main(int argc, char ** argv)
{
	po::options_description desc("Allowed options");
	desc.add_options()
	    ("help", "produce help message")
	    ("file", po::value<std::string>(), "import data from file")
	    ("diagram", "create time diagram")
	    ("verbose", "show all steps")
	    ("algorithm", po::value<int>(), "choose algorithm")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	if (vm.count("help")) {
	    std::cout << desc << "\n";
	    return 1;
	}

	Base * alg = chooseAlg(vm, false);

	if(vm.count("diagram"))
	{
		Diagram diag(alg);
		diag.createDiagrams();
		return 0;
	}

	if(vm.count("file")) {
		std::vector<std::string> to_process = readData(vm["file"].as<std::string>());
		int len = to_process.size();
		int part = len/10;
		int j = 0;
		for(auto i = to_process.begin(); i != to_process.end(); ++i)
			{
				alg->reset(*i);
				checkIfCorrect(*i, alg->sortCMYK()); 
				if(part == j)
				{
					part+=len/10;
					std::cout << "Tested: " << j << "/" << len << std::endl;
				}
				++j;
			}
		std::cout << "ALL TESTS PASSED" << std::endl;
		delete alg;
		return 0;
	}

	std::string shelf = argv[argc-1];

	if(vm.count("verbose")) {
		alg = chooseAlg(vm, true);
		alg->reset(shelf);
		alg->sortCMYK();
 		printHistory(alg->getHistory());
	}

	else
	{
		alg = chooseAlg(vm, false);
		alg->reset(shelf);
		std::string result = alg->sortCMYK();
		std::cout << result << std::endl;
	}

	delete alg;
	return 0;
}
