#include <iostream>
#include <vector>
#include "panel.h"
#include <string>
#include "helper.h"
#include "customerUI.h"
#include <sstream>
#include <iomanip>
#include <conio.h>

using namespace std;

Panels cPanel;
Helper cHelper;

int CustomerUserInterface::orderingUI(int& oItem,const vector<string>& prodName, const vector<double>& prices, const vector<double>& ratings, const vector<double>& sales){
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	const int SPACE = 32;
	const int E = 101;
	int selected = 0;
	int item = oItem;
	bool stay = true;
	
	while(stay){
		cPanel.clearSkin();
		
		cHelper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		cHelper.centerText("SELECT WHICH PRODUCT YOU WANT TO ORDER\n\n");
		
		ostringstream header;
		header<<left
			<<setw(6)<<"ID: "
			<<setw(18)<<"Product Name"
			<<setw(18)<<"Product Price"
			<<setw(18)<<"Product Ratigs"
			<<setw(18)<<"Product Sales";
		
		cHelper.centerText(header.str() + "\n");
		cHelper.centerText(string(42, '-') + "\n");
		
		for(int i = 0; i < prodName.size(); i++){
			ostringstream row;
			
			row <<fixed<<left
				<<setw(6)<<to_string(i+1)
				<<setw(18)<< prodName[i]
				<<setw(18)<<setprecision(2)<< prices[i]
				<<setw(18)<<setprecision(2)<< ratings[i]
				<<setw(18)<<setprecision(2)<< sales[i];
			
			if(i == selected){
		        cHelper.centerText(">" + row.str() + "<\n");
		    }else{
		        cHelper.centerText(" " + row.str() + "\n");
		    }
		}
		ostringstream guideA, guideB, guideC;
		
		cout<<'\n';
		
		guideA<<left<<setw(10)<<"PRESS SPACE TO CHECKOUT";
		guideB<<left<<setw(10)<<"PRESS E TO EXIT";
		guideC<<left<<setw(10)<<"CART "<<item;
		
		cHelper.centerText(guideC.str()+"\n");
		cHelper.centerText(guideA.str()+"\n");
		cHelper.centerText(guideB.str()+"\n");
		
		cout<<'\n';
		cout<<'\n';
		cHelper.drawBorder();
		
		int key = _getch();
		
	    if(key == 0 || key == 224){
	        key = _getch();
	        if (key == UP) selected = (selected - 1 + prodName.size()) % prodName.size();
	        if (key == DOWN) selected = (selected + 1) % prodName.size();
	    }else if (key == ENTER){
	    	oItem++;
	    	return selected;
	    }else if(key == SPACE){
	    	stay = false;
	    	return 32;
		}else if(key == E){
			stay = false;
			return 101;
		}
	}
}

void CustomerUserInterface::checkOutUI(vector<int>& orders,const vector<string>& options, const vector<string>& prodName, const vector<double>& prices, vector<double>& ratings, vector<double>& sales){
	vector<int> ratingCount(prodName.size(), 0);
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	int selected = 0;
	double payment = 0;
	bool stay = true;
	double change = 0;
	
	while(stay){
		cPanel.clearSkin();
		
		cHelper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		double totalCost = 0;
		vector<string> lines;
		//building of lines array
	    lines.push_back("");
	    lines.push_back("Your order:");
	    lines.push_back("");
	    
	    for(int orderID:orders){
	    	ostringstream name, price;
	    	name<<left<<setw(15)<<"Product name: "<<prodName[orderID];
	    	price<<left<<setw(15)<<"Price: "<<fixed<<setprecision(2)<<prices[orderID];
	    	
	    	totalCost += prices[orderID];
	    	lines.push_back(name.str());
	    	lines.push_back(price.str());
	    	lines.push_back("");
		}
		
		ostringstream total;
		total<<"Total Price: "<<fixed<<setprecision(2)<<totalCost;
		lines.push_back("-----------------------------");
		lines.push_back(total.str());
		
		//printing of array lines
		cHelper.centerText("== CHECK OUT==");
		cHelper.centerText("");
		cHelper.centerText("");
		cHelper.drawLines(lines);
		
		//selectings
		for(int i = 0; i < options.size(); i++){
			string label = options[i];
			if(label == "Enter payment" && payment != 0){
				ostringstream labels;
				labels<<fixed<<setprecision(2)<<payment;
				label += ": " + labels.str();
			}
			
			if(i == selected){
				cHelper.centerText("> " + label + " <\n");
			}else{
				cHelper.centerText(" " + label + "\n");
			}
		}
		
		cout<<'\n';
		cout<<'\n';
		cHelper.drawBorder();
		
		int key = _getch();
		
		if(key == 0 || key == 224){
			key = _getch();
			if (key == UP) selected = (selected - 1 + options.size()) % options.size();
	        if (key == DOWN) selected = (selected + 1) % options.size();
		}else if(key == ENTER){
			if(options[selected] == "Enter payment"){
				cPanel.clearSkin();
				cHelper.centerText("Enter your payment: ");
				cin>>payment;
			}else if(options[selected] == "Submit"){
				if (payment < totalCost) {
			        cHelper.centerText("Insufficient payment\n");
			        system("pause");
			    } else {
			        cHelper.centerText("Purchased Successfully\n");
			        
			        change = payment - totalCost;
			        //distributing of the purchase in the total sales
			        for (int orderID:orders) {
			            sales[orderID] += prices[orderID];
			        }
			        system("pause");
			        rateItems(orders, prodName, prices, ratings, ratingCount);
			        
			        cout<<'\n';
			        bool success = cHelper.printReceipt(orders, prodName, prices, totalCost, change);
				
					if(success){
						cHelper.centerText("Receipt printed to 'receipt.txt'\n");
						stay = false;
						orders.clear();
					}else{
						cHelper.centerText("Failed to print receipt\n");
					}
			        system("pause");
			    }
			}else if(options[selected] == "Back"){
				stay = false;
			}
		}
	}
}

void CustomerUserInterface::rateItems(const vector<int>& orders, const vector<string>& prodName, const vector<double>& prices, vector<double>& ratings, vector<int>& ratingCount){
	cPanel.clearSkin();
	
	cHelper.drawBorder();
	cout<<'\n';
	cout<<'\n';
	
	cHelper.centerText("Rate the product you purchased(1-5)\n\n");
	
	set<int> products = {orders.begin(), orders.end()};
	
	for(int product:products){
		double rating;
		
		do{
			ostringstream line;
			line<<"Rate product "<<prodName[product]<<": ";
			cHelper.centerText(line.str());
			cin>>rating;
			
			if(rating < 1 || rating > 5){
				cHelper.centerText("Invalid rating pls enter 1-5 only");
			}
		}while(rating < 1 || rating > 5);
		
		ratings[product] = (ratings[product] * ratingCount[product] + rating) / (ratingCount[product] + 1);
    	ratingCount[product]++;
	}
	cout<<'\n';
	cHelper.centerText("Thank you for your feedback!\n");
	
	cout<<'\n';
	cout<<'\n';
	cHelper.drawBorder();
}
