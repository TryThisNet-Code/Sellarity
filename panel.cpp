#include <iostream>
#include <algorithm>
#include <iomanip>
#include "panel.h"
#include "navigation.h"
#include "helper.h"
#include "customerUI.h"

using namespace std;

vector<string> prodName = {"foods", "pagkain", "tabemono"};
vector<double> prices = {33,33.33, 32};
vector<double> ratings = {5.0, 3.3, 4.4};
vector<double> sales = {44545, 454545,4545454};

void Panels::adminPanel(){
	UserInterface ui;
	
	vector<string> options = {"Add a new product", "Update a product", "Delete a product", "View product revenue", "View sales bar graph", "Exit"};
	vector<string> addingOptions = {"Enter a new product", "Enter a price for product", "", "Submit", "Back"};
	vector <string> fOptions = {"Product name", "Product Price","", "Back"};
	vector<string> displayOptions = {"Print", "Back"};
	vector<string> graphOptions = {"Product Ratings", "Product Sales","", "Back"};
	
	while(true){
		int choice = ui.adminPanelUI(options);
		
		switch(choice){
			case 1://adding a product
				ui.addPanel(addingOptions, prodName, prices, ratings, sales);
				break;
			case 2://updating a product
				ui.updatePanel(fOptions, prodName, prices, ratings, sales);
				break;
			case 3://deleting product
				ui.deletePanel(prodName, prices, ratings, sales);
				break;
			case 4://displaying product infos
				ui.displayPanel(displayOptions, prodName, prices, ratings, sales);
				break;
			case 5://showbargraph
				ui.diplayGraph(graphOptions, prodName, ratings, sales);
				break;
			case 6:
				return;
			break;
		}
	}
}

void Panels::customerPanel(){
	CustomerUserInterface cui;
	vector<string> checkOutOptions = {"Enter payment","Submit", "Back"};
	bool stay = true;
	int numItem=0;
	
	vector<int> cart;
	while(stay){
		
		int response = cui.orderingUI(numItem, prodName, prices, ratings, sales);

		if(response == 101){
			stay = false;
		}else if(response == 32){
			cui.checkOutUI(cart, checkOutOptions, prodName, prices, ratings, sales);
		}else{
			cart.push_back(response);
			numItem = cart.size();
		}
	}
}

void Panels::clearSkin(){
	system("cls");
}
