#include "Generator.h"

const std::string Generator::ORDER = "CMYK";

Generator::Generator(unsigned a, unsigned b, unsigned c, unsigned d, unsigned n)
{
	srand(time(NULL));
	setParams(a, b, c, d, n);
}

void Generator::setParams(unsigned a = 25, unsigned b = 25, unsigned c = 25, unsigned d = 25, unsigned n = 100)
{
	C_prob_ = a;
	M_prob_ = b;
	Y_prob_ = c;
	K_prob_ = d;
	length = n;
}

void Generator::setLength(unsigned n)
{
	length = n;
}

std::string Generator::generate()
{
	int total = C_prob_ + M_prob_ + Y_prob_ + K_prob_;
	std::string result = "";
	std::vector<unsigned> nums = { C_prob_, M_prob_, Y_prob_, K_prob_};
	for (int i = 0; i < length; ++i)
	{
		int j = 0;
		int x = rand() % total;
		do
		{
			x -= nums[j];
			++j;
		} while (x > 0);
		result += ORDER[j-1];
	}
	return result;
}