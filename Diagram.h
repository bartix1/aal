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



namespace py = boost::python;

class Diagram
{
public:
	Diagram(Base * b);
	~Diagram();
	void createDiagrams();
private:
	void drawDiagram(std::vector<std::pair<int, double>>& times);
	double asymptotic_time_n_2(int x);
	double asymptotic_time_n_logn(int x);
	void createAsymptoticDiagram(double (Diagram::*time_fun)(int));
	void createTimesDiagram();

	Base * algorithm;
};

template <typename X, typename Y>
py::list toPythonList(std::vector<std::pair<X, Y>> vector);