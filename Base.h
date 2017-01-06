#pragma once
#include <string>
#include <vector>
#include <unordered_map>	
#include <iostream>
#include <deque>

class Base
{
public:
	Base(std::string shelf, bool trace );
	Base(const Base * b);
	virtual ~Base() {};
	virtual std::string sortCMYK() = 0;
	std::vector<std::string> getHistory() const;
	void reset(std::string);

	bool isTracing() const;
	std::string getShelf() const;

protected:
	static std::string ORDER;
	std::string shelf;

	std::string lessThanSixSort();
	std::string sortLastSix(std::string &, const std::string &);
	void move(std::string &, int, bool record = true);

private:
	std::string sortLastSixBody(std::string text, const std::string &, std::string);
	std::string sortLastSixBodyWithTrace(std::string, const std::string &, std::string);
	std::vector<std::string> moves_history;
	bool trace;
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