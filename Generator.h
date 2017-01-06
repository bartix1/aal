#pragma once
#include <string>
#include <ctime>
#include <vector>

class Generator
{
public:
	Generator(int a = 25, int b = 25, int c = 25, int d = 25, int n = 100);

	std::string generate();
	void setParams(int a, int b, int c, int d, int n);
	void setLength(int n);

private:
	static const std::string ORDER;
	int C_prob_;
	int M_prob_;
	int Y_prob_;
	int K_prob_;
	int length;
		
};