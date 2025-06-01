#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <vector>
#include <string>

using namespace std;

class UserInterface {
	
	public:
		int landingScreen(const vector<string>& options);
		void loginAdmin(const vector<string>& options, const vector<vector<string>>& adminAcc);
		void loginCustomer(const vector<string>& options, const vector<vector<string>>& customerAcc);
		int adminPanelUI(const vector<string>& options);
		//admin panel
		void addPanel(const vector<string>& options, vector<string>& prodName, vector<double>& price, vector<double>& rating, vector<double>& sale);
		void updatePanel(const vector<string>& options, vector<string>& prodName, vector<double>& price, const vector<double>& ratings, const vector<double>& sales);
		void deletePanel(vector<string>& prodName, vector<double>& price, vector<double>& ratings, vector<double>& sales);
		void displayPanel(const vector<string>& options, vector<string>& prodName, vector<double>& price, vector<double>& ratings, vector<double>& sales);
		void diplayGraph(const vector<string>& options, vector<string>& prodName, vector<double>& ratings, vector<double>& sales);
};

#endif
