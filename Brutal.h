#pragma once

#include "Base.h"

class Brutal : public Base
{
public:
	Brutal(std::string = "", bool = false);

	virtual std::string sortCMYK();
};