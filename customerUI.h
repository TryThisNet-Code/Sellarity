#ifndef CUSTOMERUI_H
#define CUSTOMERUI_H

using namespace std;

class CustomerUserInterface{
	public:
		int orderingUI(const vector<string>& prodName, const vector<double>& prices, const vector<double>& ratings, const vector<double>& sales);
};

#endif
