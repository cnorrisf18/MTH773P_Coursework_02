#pragma once

#include <iostream>
#include <iterator>
#include <map>

using namespace std;

class LinearInterpolator
{
public:

	LinearInterpolator();
	void insert(double x, double y); //add a single point to the private map
	double value(double x); //calculate and return the y-value at a given x

private:

	map<double, double> pointsmap; //this holds the points entered by the insert function
};

class Histogram
{
public:

	Histogram(double xmin, double xmax, double bins);
	Histogram(double xmin, double xmax);
	void initializemap();
	void add(double x);
	map<double, int> getResults();
	double underflow;
	double overflow;
	void writeResultsToStream();
	
private:
	double xmin;
	double xmax;
	double bins;
	map<double, int> resultsmap; //this holds all values of x in their respective bin number. The double is the right-hand x-value and the int is the number of points in that bin
};