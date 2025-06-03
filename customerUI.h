#ifndef CUSTOMERUI_H
#define CUSTOMERUI_H
#include <set>
#include <vector>

using namespace std;

class CustomerUserInterface{
	public:
		int orderingUI(int& item, const vector<string>& prodName, const vector<double>& prices, const vector<double>& ratings, const vector<double>& sales);
		void checkOutUI(vector<int>& orders,const vector<string>& options, const vector<string>& prodName, const vector<double>& prices, vector<double>& ratings, vector<double>& sales);
		void rateItems(const vector<int>&orders, const vector<string>& prodName, const vector<double>& prices, vector<double>& ratings, vector<int>& ratingCount);
};

#endif
