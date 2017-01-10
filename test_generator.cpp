#include <iostream>
#include <fstream>
#include "Generator.h"

int main(int argc, char *argv[])
{
	if(argc != 1 && argc != 7)
	{
		std::cout << "Usage ./app or ./app prob_C prob_M prob_Y prob_K len amount" << std::endl;
		return 1;
	}

	std::ofstream file;
	int prob_C, prob_M, prob_Y, prob_K, len, amount; 
	if(argc == 7)
	{
		prob_C = atoi(argv[1]);
		prob_M = atoi(argv[2]);
		prob_Y = atoi(argv[3]);
		prob_K = atoi(argv[4]);
		len    = atoi(argv[5]);
		amount = atoi(argv[6]);
	}
	else
	{
		prob_C = prob_M = prob_Y = prob_K = 25;
		len = 500;
		amount = 10000;
	}

	file.open("test_file.txt");
	Generator gen(prob_C, prob_M, prob_Y, prob_K, len);
	for(int i = 0; i < amount; ++i)
	{
		std::string shelf = gen.generate();
		file << shelf << "\n";
	}
	std::cout << "TESTS GENERATED" << std::endl;
}