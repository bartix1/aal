#pragma once

#include "Base.h"

class Brutal : public Base
{
public:
	Brutal(std::string);

	virtual std::string sortCMYK();
	std::string brutalSort(std::string text, const std::string & prefix);

};