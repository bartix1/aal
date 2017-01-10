#include "Generator.h"

const std::string Generator::ORDER = "CMYK";

Generator::Generator(int a, int b, int c, int d, int n)
{
	srand(time(NULL));
	setParams(a, b, c, d, n);
}

void Generator::setParams(int a, int b, int c, int d, int n)
{
	C_prob_ = a;
	M_prob_ = b;
	Y_prob_ = c;
	K_prob_ = d;
	length = n;
}

void Generator::setLength(int n)
{
	length = n;
}

std::string Generator::generate()
{
	int total = C_prob_ + M_prob_ + Y_prob_ + K_prob_;
	std::string result = "";
	std::vector<int> nums = { C_prob_, M_prob_, Y_prob_, K_prob_};
	for (int i = 0; i < length; ++i)
	{
		int j = 0;
		int x = rand() % total;
		do
		{
			x -= nums[j];
			++j;
		} while (x >= 0);
		result += ORDER[j-1];
	}
	return result;
}