#pragma once
#include <string>
#include <vector>
#include <unordered_map>	
#include <iostream>
#include <deque>
#include <algorithm>

class Base
{
public:
	Base(std::string shelf, bool trace = false);
	Base(const Base * b);
	virtual ~Base() {};
	virtual std::string sortCMYK() = 0;
	std::vector<std::string> getHistory() const;
	void reset(std::string, bool = false);

	bool isTracing() const;
	std::string getShelf() const;

protected:
	static std::string ORDER;
	std::string shelf;
	std::vector<std::string> moves_history;
	bool trace;

	std::string lessThanSixSort();
	std::string sortLastSix(std::string &, const std::string &);
	void move(std::string &, int, bool record = true);
	std::string brutalSort(std::string text, const std::string &, std::string);
	std::string brutalSortWithTrace(std::string, const std::string &, std::string);
};

class MyException
{
public:
	MyException(std::string s, std::string t, std::string p, std::string b) : shelf(s), text(t), prefix(p), beg(b) {};

	std::string shelf;
	std::string text;
	std::string prefix;
	std::string beg;
};

std::pair<std::string, std::vector<int>> getResult(std::string shelf);