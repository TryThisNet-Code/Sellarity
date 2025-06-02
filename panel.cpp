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
	vector<string> addingOptions = {"Enter a new product", "Enter a price for product", "Submit", "Back"};
	vector <string> fOptions = {"Product name", "Product Price", "Back"};
	vector<string> displayOptions = {"Print", "Back"};
	vector<string> graphOptions = {"Product Ratings", "Product Sales", "Back"};
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
	vector<int> cart;
	bool stay = true;
	
	while(stay){
		int response = cui.orderingUI(prodName, prices, ratings, sales);
		
//		if(input == "exit"){
//			break;
//		}else if(input == "checkout"){
//			double payment = 0;
//			double totalCost = 0;
//			
//			cout<<"== CHECK OUT ==\n\n";
//			cout<<"You'r order are: \n";
//			for(int id : cart){
//				cout<<"Product name: "<<prodName[id]<<endl;
//				cout<<"Price: "<<prices[id]<<endl;
//				totalCost += prices[id];
//			}
//			cout<<"Total price: "<<totalCost<<endl;
//			cout<<"Enter your payment";
//			cin>>payment;
//			
//			if(payment < totalCost){
//				cout<<"Insufficient payment\n";
//			}else{
//				cout<<"Purchased Successfully\n";
//				for(int id: cart){
//					sales[id] += prices[id];
//				}
//				system("pause");
//			}
//		}else{
//			try{
//				int id = stoi(input);
//				if(id >= 1 && id <= prodName.size()){
//					cart.push_back(id-1);
//					cout<<prodName[id-1]<<" has been added to the cart\n";
//					system("pause");
//				}else{
//					cout<<"Invalid Input";
//				}
//			}catch(...){
//				cout<<"Invalid Input, please try again";
//			}
//		}
		if(response == 101){
			stay = false;
		}else if(response == 32){
			cui.checkOutUI(cart, checkOutOptions, prodName, prices, sales);
		}else{
			cart.push_back(response);
		}
	}
}

void Panels::clearSkin(){
	system("cls");
}
