#pragma once
#include <string>
#include <ctime>
#include <vector>

class Generator
{
public:
	Generator(unsigned a = 25, unsigned b = 25, unsigned c = 25, unsigned d = 25, unsigned n = 100);

	std::string generate();
	void setParams(unsigned a, unsigned b, unsigned c, unsigned d, unsigned n);
	void setLength(unsigned n);

private:
	static const std::string ORDER;
	unsigned C_prob_;
	unsigned M_prob_;
	unsigned Y_prob_;
	unsigned K_prob_;
	unsigned length;
		
};