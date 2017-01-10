#include "Diagram.h"

template <typename X, typename Y>
py::list toPythonList(std::vector<std::pair<X, Y>> vector) {
	typename std::vector<std::pair<X, Y>>::iterator iter;
	py::list list;
	for (iter = vector.begin(); iter != vector.end(); ++iter) {
		py::list tmp;
		tmp.append((*iter).first);
		tmp.append((*iter).second);
		list.append(tmp);
	}
	return list;
}

Diagram::Diagram(Base * b)
{
	if(typeid(*b) == typeid(First))
		algorithm = new First(b);
	else
		algorithm = new Second(b);
}

Diagram::~Diagram()
{
	if(algorithm)
		delete algorithm;
}


void Diagram::drawDiagram(std::vector<std::pair<int, double>>& times, std::string y)
{
	try
	{
		setenv("PYTHONPATH", ".", 1);
		Py_Initialize();
		py::object main_module = py::import("main");
	    py::object create_f = main_module.attr("createDiagram");
	    py::list vec = toPythonList(times);
	    create_f(vec, y);
	}
	catch(boost::python::error_already_set e)
	{
		PyErr_Print();
	}
}

void Diagram::createDiagrams()
{
	createTimesDiagram();
	if (typeid(*algorithm) == typeid(First))
		createAsymptoticDiagram(&Diagram::asymptotic_time_n_2);
	else
		createAsymptoticDiagram(&Diagram::asymptotic_time_n_logn);
}


double Diagram::asymptotic_time_n_2(int x)
{
	// n^2 * 10
	TimeCounter t;
	t.start_timer();
	for(int i = 0; i < x; ++i)
		for(int j = 0; j < x; ++j)
			for(int k = 0; k < log(x); ++k);
	t.stop_timer();
	return t.getTime()/10;
}


double Diagram::asymptotic_time_n_logn(int x)
{
	// n* log(n) * 100
	TimeCounter t;
	t.start_timer();
	for(int i = 0; i < x; ++i)
		for(int j = 0; j < log(x); ++j);
	t.stop_timer();
	return t.getTime()*100;
}


void Diagram::createTimesDiagram()
{
	Generator gen;
	TimeCounter t;
	std::vector<std::pair<int, double>> times;
	for (int i = 20; i<5000; i+=20)
	{
		gen.setLength(i);
		std::string shelf = gen.generate();
		algorithm->reset(shelf);
		t.start_timer();
		algorithm->sortCMYK();
		t.stop_timer();
		times.push_back(std::make_pair(i, t.getTime()));
		if(i%1000 == 0)
			std::cout << "Already done: " << i << "/5000" << std::endl;
	}
	drawDiagram(times);
}


void Diagram::createAsymptoticDiagram(double (Diagram::*time_fun)(int))
{
	Generator gen;
	TimeCounter t;
	std::vector<std::pair<int, double>> times;
	for (int i = 100; i<3000; i+=20)
	{
		gen.setLength(i);
		std::string shelf = gen.generate();
		algorithm->reset(shelf);
		t.start_timer();
		algorithm->sortCMYK();
		t.stop_timer();
		double asympt = (this->*time_fun)(i);
		times.push_back(std::make_pair(i, t.getTime()/asympt));
		if(i%1000 == 0)
			std::cout << "Already done: " << i << "/3000" << std::endl;
	}
	drawDiagram(times, "ratio");
}