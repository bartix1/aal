#pragma once 

#include "TimeCounter.h"
#include "Generator.h"
#include "First.h"
#include "Second.h"

#include <cmath>
#include <assert.h>
#include <boost/python.hpp>
#include <Python.h>
#include <typeinfo>
#include <tuple>


namespace py = boost::python;

class Diagram
{
public:
	Diagram(Base * b);
	~Diagram();
	void createDiagrams();
private:
	void drawDiagram(std::vector<std::pair<int, double>>& times, std::string y = "time");
	int asymptotic_time_n_2(int x);
	int asymptotic_time_n_logn(int x);
	void createAsymptoticDiagram(int (Diagram::*time_fun)(int));
	void createTimesDiagram();
	void makeTable(int (Diagram::*time_fun)(int));
	std::pair<int, int> getMedians(int i, int (Diagram::*time_fun)(int));

	Base * algorithm;
};

template <typename X, typename Y>
py::list toPythonList(std::vector<std::pair<X, Y>> vector);