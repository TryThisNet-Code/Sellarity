#ifndef HELPER_H
#define HELPER_H
#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

class Helper{
	public:
		int getConsoleWidth();
		void centerText(const string& text);
		void drawBorder();
		//functions for adding some thingy/ admin side
		void addProduct(const string& name, const string& price,vector<string>& prodName, vector<double>& prices, vector<double>& ratings, vector<double>& sales);
		int selectProduct(const vector<string>& prodName, const vector<double>& prices, const vector<double>& ratings, const vector<double>& sales);
		void updateProduct(const int& prodID, const int& uChoice, const string& nName, const double& nPrice, vector<string>& prodName, vector<double>& prices);
		bool deleteProduct(const int& prodID, vector<string>& prodName, vector<double>& prices, vector<double>& ratings, vector<double>& sales);
		void drawGraph(const vector<string>& prodName, const vector<double>& ratings);
		void drawLines(const vector<string>& lines);
		//customer sides
		bool printReceipt(const vector<int>& orderID, const vector<string>& prodName, const vector<double>& prices, const double totalCost, const double change);
		void printProdInfo(const vector<string>& prodName,const vector<double>& prices,const vector<double>& ratings,const vector<double>& sales, const double& totalSales);
};

#endif
