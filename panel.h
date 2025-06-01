#ifndef PANEL_H
#define PANEL_H

#include <vector>
#include <string>

using namespace std;

class Panels{
	
	public:
		void adminPanel();	
		void customerPanel();
		void clearSkin();
		void printArrays(const vector<string> &arr);
		void printArrays(const vector<double> &arr);
		void printArrays(const vector<double> &arr1, const vector<double> &arr2, const vector<double> &arr3, const vector<string> &arr4);
};

#endif
