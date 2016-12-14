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
	virtual std::string sortCMYK() = 0;
	std::vector<std::string> getHistory() const;


protected:
	static std::string ORDER;
	const std::string shelf;

	std::string lessThanSixSort();
	std::string sortLastSix(std::string &, const std::string &);
	void move(std::string &, int, bool record = true);

private:
	std::string sortLastSixBody(std::string text, const std::string &, std::vector<std::string>, std::string);
	std::vector<std::string> moves_history;
	bool trace;
};