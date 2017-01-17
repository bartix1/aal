#include "Diagram.h"

double avg(const std::vector<double> & times)
{
	double sum = 0;
	for(auto it : times)
		sum += it;
	return sum/times.size();
}

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

std::pair<int, int> Diagram::getMedians(int i, int (Diagram::*time_fun)(int))
{
	int asympt_med = (this->*time_fun)(i);
	return std::make_pair(i, asympt_med);
}

#include <iostream>
void Diagram::makeTable(int (Diagram::*time_fun)(int))
{
	Generator gen;
	TimeCounter t;
	int start, end, step, med;
	double median, med_asympt, result;
	std::vector<std::pair<int, double>> times;
	if(typeid(*algorithm) == typeid(First))
	{
		start = step = 500;
		end = 5000;
		med = 2500;
	}
	else
	{
		start = step = 1000;
		end = 10000;
		med = 5000;
	}

	for (int i = start; i< end; i+=step)
	{
		gen.setLength(i);
		std::vector<double> results;
		for (int j = 0; j < 10; ++j)
		{
			std::string shelf = gen.generate();
			algorithm->reset(shelf);
			t.start_timer();
			algorithm->sortCMYK();
			t.stop_timer();
			results.push_back(t.getTime());
		}
		result = avg(results);
		times.push_back(std::make_pair(i, result));
		if(i == med)
		{
			median = result;
			med_asympt = (this->*time_fun)(i);
		}

	}
	for (auto it : times)
		std::cout << it.first << " " << it.second << " " 
		<< (it.second * med_asympt) / (median * (this->*time_fun)(it.first)) << std::endl;
}



void Diagram::createDiagrams()
{
	//createTimesDiagram();
	if (typeid(*algorithm) == typeid(First))
	{
		//createAsymptoticDiagram(&Diagram::asymptotic_time_n_2);
		makeTable(&Diagram::asymptotic_time_n_2);
	}
	else
	{
		//createAsymptoticDiagram(&Diagram::asymptotic_time_n_logn);
		makeTable(&Diagram::asymptotic_time_n_logn);
	}
}


int Diagram::asymptotic_time_n_2(int n)
{
	return n*n*log(n);
}


int Diagram::asymptotic_time_n_logn(int n)
{
	return n*log(log(n));
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

void Diagram::createAsymptoticDiagram(int (Diagram::*time_fun)(int))
{
	Generator gen;
	TimeCounter t;
	std::vector<std::pair<int, double>> times;
	double median, result = 0;
	int med_asympt;
	for (int i = 800; i<3800; i+=50)
	{
		std::vector<double> results;
		gen.setLength(i);
		for (int j = 0; j < 10; ++j)
		{
			std::string shelf = gen.generate();
			algorithm->reset(shelf);
			t.start_timer();
			algorithm->sortCMYK();
			t.stop_timer();
			results.push_back(t.getTime());
		}
		result = avg(results);
		times.push_back(std::make_pair(i, result));
		if(i%1000 == 0)
			std::cout << "Already done: " << i << "/4000" << std::endl;
		if(i == 2300)
		{
			median = result;
			med_asympt = (this->*time_fun)(i);
		}
	}
	for (auto it = times.begin(); it < times.end(); ++it)
		(*it).second = ((*it).second * med_asympt) / (median * (this->*time_fun)((*it).first));

	drawDiagram(times, "ratio");
}