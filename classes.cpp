#include <iostream>
#include <map>
#include <iterator>
#include "classes.h"

using namespace std;

LinearInterpolator::LinearInterpolator()
{

}

void LinearInterpolator::insert(double x, double y)
{
	if (pointsmap.count(x) > 0) //the x-value is already present in the map
	{
		cout << "The x-value already exists. Since two x-values for a given y is not allowed in linear lines this point will not be added." << endl;
	}
	else //the x-value isn't already in the map so we can add it. It should automatically be ordered by low-to-high x-values
	{
		pointsmap.insert(pair<double, double>(x, y));
	}
}

double LinearInterpolator::value(double x)
{
	map<double, double>::iterator lowerpoint = pointsmap.begin();
	map<double, double>::iterator higherpoint = prev(pointsmap.end());
	
	if ((x < lowerpoint->first) || (x > higherpoint->first)) // the given value of x lies outside of the known range of points 
	{
		double y_sum = 0.0;
		cout << "The given value of x lies outside of the boundary of known values, so a y-value cannot be computed. Returning the average of given y-values." << endl;
		for (map<double, double>::iterator it = pointsmap.begin(); it != pointsmap.end(); ++it)
		{
			y_sum += it->second;
		}
		return y_sum / pointsmap.size();
	}
	

	for (map<double, double>::iterator it = pointsmap.begin(); it != pointsmap.end(); ++it)
	{
		//we are going through the map value by value using iterators
		if (it->first == x) //if the x value at the iterator equals the given x-value, our returned y value is just the previously entered y
		{
			return it->second;
		}
		if (it->first < x)  //if the x value at the iterator is greater than the lower point, set the lower point to the iterator
		{
			lowerpoint = it;
		}
		if (it->first > x) //if the x value at the iterator is less than the higher point, set the higher point to the iterator and break the loop
		{
			higherpoint = it;
			break;
		}

	}

	//after the for loop, we should have correct iterators for the lower point and the higher point values surrounding the given x-value

	//get the needed values from the iterators
	double x1 = lowerpoint->first;
	double y1 = lowerpoint->second;
	double x2 = higherpoint->first;
	double y2 = higherpoint->second;

	//calculate y-value

	double y = y1 + ((x - x1) * ((y2 - y1) / (x2 - x1)));
	return y;

}


Histogram::Histogram(double min, double max, double bin)
{
	xmin = min;
	xmax = max;
	bins = bin;
	underflow = 0;
	overflow = 0;
	initializemap();
}
Histogram::Histogram(double min, double max)
{
	xmin = min;
	xmax = max;
	//since bin number wasn't given, set it to a default value
	bins = 10;
	underflow = 0;
	overflow = 0;
	initializemap();
}
void Histogram::initializemap()
{
	double binwidth = (xmax - xmin) / bins;
	//find the right-hand x-values for each bin and stick them in the results map
	for (int i = 1; i <= bins; ++i)
	{
		double rightx = xmin + (i * binwidth);
		resultsmap.insert(pair<double, int>(rightx, 0));
	}
}
void Histogram::add(double x)
{
	//find what bin to increase by 1
	if (x < xmin) //x is less then the minimum, so increase underflow by 1
	{
		underflow += 1;
	}
	else if (x > xmax) //x is greater than the maximum, so increase overflow by 1
	{
		overflow += 1;
	}
	else
	{
		//loop through the map; if the x is less than the right-hand x value, break the loop and add to that bin
		for (map<double, int>::iterator it = resultsmap.begin(); it != resultsmap.end(); ++it)
		{
			if (x < it->first)
			{
				it->second += 1;
				break;
			}
		}
	}
}

map<double, int> Histogram::getResults()
{
	//the work for this is done when points are added, so we can just return the resultsmap
	return resultsmap;
}

void Histogram::writeResultsToStream()
{
	cout << "Printing histogram data" << endl;
	for (map<double, int>::iterator it = resultsmap.begin(); it != resultsmap.end(); ++it)
	{
		cout << it->first << "\t" << it->second << '\n';
	}
	cout << "There were " << underflow << " underflow values and " << overflow << " overflow values. " << endl;
}
