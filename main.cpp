#include <iostream>
#include <map>
#include <iterator>
#include "classes.h"
#include <random>

using namespace std;

int main() 
{
	//test the LinearInterpolator Class
	LinearInterpolator MyLinear;

	//insert points
	MyLinear.insert(1.2, 5.6);
	MyLinear.insert(5.0, 4.3);
	MyLinear.insert(.9, 11.0);
	MyLinear.insert(-4.0, -4.0);

	double testvalue = MyLinear.value(0);
	cout << testvalue << endl;

	//test inserting duplicate x values
	MyLinear.insert(5, 4.3);
	MyLinear.insert(.9, 10);

	//test inserting x values that are outside the previous range
	testvalue = MyLinear.value(-10);
	cout << testvalue << endl;
	MyLinear.insert(2, 1000);
	testvalue = MyLinear.value(50);
	cout << testvalue << endl;

	//test given points
	LinearInterpolator SecondLinear;

	//insert points
	SecondLinear.insert(-1.1, 3.7);
	SecondLinear.insert(.9, 2.2);
	SecondLinear.insert(5.2, 5.5);
	
	cout << SecondLinear.value(.2) << endl;

	SecondLinear.insert(-.2, 6);

	cout << SecondLinear.value(.2) << endl;
	
	//test the Histogram class
	Histogram MyHistogram(0,1);

	srand(time(NULL));
	//insert numbers
	for (int i = 0; i < 1000000; ++i)
	{
		double randomnumber = rand() / double(RAND_MAX);
		MyHistogram.add(randomnumber);
	}
	//insert overflow and underflow values
	MyHistogram.add(-1);
	MyHistogram.add(2);
	MyHistogram.add(5);
	MyHistogram.add(-113);
	//print out the histogram data
	

	map<double, int> Data = MyHistogram.getResults();

	MyHistogram.writeResultsToStream();
}