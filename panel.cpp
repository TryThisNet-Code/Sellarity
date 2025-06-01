#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "panel.h"
#include "navigation.h"
#include "helper.h"

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
			case 5:{//showbargraph
				double maxRating = *max_element(ratings.begin(), ratings.end());
				while(true){
					clearSkin();
					
					int vChoice;
					//choice
			        cout<<"Choice which bar graph you wanted to view\n";
			        cout<<"[1] Ratings\n";
			        cout<<"[2] Sales\n";
			        cout<<"Enter your choice: ";
			        cin>>vChoice;
			        
			        if(vChoice == 1){//determine choice on which bar graph should we print
			        	clearSkin();
			        	
			        	double maxRating = *max_element(ratings.begin(), ratings.end());
			        	int maxBarLength = 25;
			        	
			        	cout<<"== Product Ratings Bar Graph ==\n\n";
			        	for(size_t i = 0; i < prodName.size(); i++){
			        		cout<<setw(10)<< prodName[i]<<" | ";
			        		int bars = static_cast<int>((ratings[i]/maxRating) * maxBarLength);
			        		cout<<string(bars, '*')<<" "<<fixed<<setprecision(1)<<ratings[i]<<'\n';
						}
						
						cout << "            " << string(maxBarLength, '-') << "\n";
        				cout << "            0     5     10    15    20    25\n";
					}else{
						clearSkin();
			        	
			        	double maxSales = *max_element(sales.begin(), sales.end());
			        	int maxBarLength = 25;
			        	
			        	cout<<"== Product Sales Bar Graph ==\n\n";
			        	for(size_t i = 0; i < prodName.size(); i++){
			        		cout<<setw(10)<< prodName[i]<<" | ";
			        		int bars = static_cast<int>((sales[i]/maxSales) * maxBarLength);
			        		cout<<string(bars, '*')<<" "<<fixed<<setprecision(1)<<sales[i]<<'\n';
						}
						
						cout << "            " << string(maxBarLength, '-') << "\n";
        				cout << "            0     5     10    15    20    25\n";
					}
					
					char eChoice;
					
					cout<<"Press any key to continue\n";
					cout<<"Press E to exit: ";
					cin>>eChoice;
					if(toupper(eChoice) == 'E'){
						break;
					}
				}
				break;
			}
			case 6:
				return;
			break;
		}
	}
	
}

void Panels::customerPanel(){
	vector<int> cart;
	
	while(true){
		string input;
		
		clearSkin();
		
		for(int i = 0; i < prodName.size(); i++){
			cout<<"==================\n";
			cout<<"Product: "<<prodName[i]<<endl;
			cout<<"Price: "<<prices[i];
			cout<<"ID: "<<i+1;
			cout<<"\n==================\n";
		}
		cout<<"Enter the ID of the product you want to order: \n";
		cout<<"Enter \"checkout\" to go to checkout\n";
		cout<<"Enter \"exit\" to exit\n";
		cout<<"Enter your choice: ";
		cin>>input;
		
		if(input == "exit"){
			break;
		}else if(input == "checkout"){
			double payment = 0;
			double totalCost = 0;
			
			cout<<"== CHECK OUT ==\n\n";
			cout<<"You'r order are: \n";
			for(int id : cart){
				cout<<"Product name: "<<prodName[id]<<endl;
				cout<<"Price: "<<prices[id]<<endl;
				totalCost += prices[id];
			}
			cout<<"Total price: "<<totalCost<<endl;
			cout<<"Enter your payment";
			cin>>payment;
			
			if(payment < totalCost){
				cout<<"Insufficient payment\n";
			}else{
				cout<<"Purchased Successfully\n";
				for(int id: cart){
					sales[id] += prices[id];
				}
				system("pause");
			}
		}else{
			try{
				int id = stoi(input);
				if(id >= 1 && id <= prodName.size()){
					cart.push_back(id-1);
					cout<<prodName[id-1]<<" has been added to the cart\n";
					system("pause");
				}else{
					cout<<"Invalid Input";
				}
			}catch(...){
				cout<<"Invalid Input, please try again";
			}
		}
	}
}

void Panels::clearSkin(){
	system("cls");
}

void Panels::printArrays(const vector<double> &arr1, const vector<double> &arr2, const vector<double> &arr3, const vector<string> &arr4){
	for(int i = 0; i < arr1.size(); i++){
		cout<<"ID "<<i+1<<left<<": "<<setw(18)<<arr4[i]<<setw(18)<<arr1[i]<<setw(18)<<arr2[i]<<setw(18)<<arr3[i]<<endl;
	}
}
