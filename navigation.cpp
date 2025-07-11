#include <iostream>
#include <chrono>
#include <thread>
#include "navigation.h"
#include <conio.h>
#include <sstream>
#include <iomanip>
#include "panel.h"
#include "helper.h"
#include "customerUI.h"
#include "account_logic.h"

using namespace std;

//main menu
Panels panel;
Helper helper;

int UserInterface::landingScreen(const vector<string>& options){
	
	int selected = 0;
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	
	while(true){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		helper.centerText("SELLARITY\n");
		helper.centerText("Sales Management System\n\n");
		
		for(int i = 0; i < options.size(); i++){
			string line;
			if(i == selected){
				line = ">   " + options[i] + "   <";
			}else{
				line = " "+options[i];
			}
			
			if(line.empty()) {
		        helper.centerText("\n");
		        continue;
    		}
			
			helper.centerText(line + "\n");
		}
		
		cout<<'\n';
		cout<<'\n';
		helper.drawBorder();
		
		int key = _getch();
		
		if(key == 224){
			key = _getch();
			if (key == UP){
	        	do {
            		selected = (selected - 1 + options.size()) % options.size();
        		} while (options[selected].empty());
			}
	        if (key == DOWN){
	        	do {
		            selected = (selected + 1) % options.size();
		        } while (options[selected].empty());
			} 
		}else if(key == ENTER){
			if (options[selected].empty()) {
		        continue;
		    }
		    
			return selected + 1;
		}
	}
}
//login to admin panel
void UserInterface::loginAdmin(const vector<string>& options, const vector<vector<string>>& adminAcc){
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	string aUsername="", aPass="";
	int selected = 0;
	bool stay = true;
	
	while(stay){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		helper.centerText("== LOGIN AS ADMIN ==\n\n");
		
		for(int i = 0; i < options.size();i++){
			string label = options[i];
			if(label == "Enter Username" && !aUsername.empty()){
				label += ": " + aUsername;
			}else if(label == "Enter Password" && !aPass.empty()){
				label += ": " + string(aPass.length(), '*');
			}
			
			if(label.empty()) {
		        helper.centerText("\n");
		        continue;
    		}
			
			if(i == selected){
				helper.centerText(">" + label + "<\n");
			}else{
				helper.centerText(" " + label + "\n");
			}
			
		}
		
		cout<<'\n';
		cout<<'\n';
		helper.drawBorder();
		
		int key = _getch();
			
		if(key == 0 || key==224){
			key = getch();
	        if (key == UP){
	        	do {
            		selected = (selected - 1 + options.size()) % options.size();
        		} while (options[selected].empty());
			}
	        if (key == DOWN){
	        	do {
		            selected = (selected + 1) % options.size();
		        } while (options[selected].empty());
			} 
		}else if(key == ENTER){
			if (options[selected].empty()) {
		        continue;
		    }
			
			if(options[selected] == "Enter Username"){
				panel.clearSkin();
				helper.centerText("Enter Username: ");
				getline(cin,aUsername);
			}else if(options[selected] == "Enter Password"){
				panel.clearSkin();
				helper.centerText("Enter Password: ");
				getline(cin,aPass);
			}else if(options[selected] == "Log In"){
				bool found = false;
				
				for(int i = 0; i < adminAcc.size(); i++){
					if(aUsername == adminAcc[i][0] && aPass == adminAcc[i][1]){
						panel.clearSkin();
						Panels admin;
						admin.adminPanel();
						found = true;
						break;
					}
				}
					
				if(!found){
					helper.centerText("Invalid username or password.\n");
	                helper.centerText("Try again? (Y/N): ");
	                char retry;
	                cin >> retry;
	                if (toupper(retry) != 'Y') {
	                    stay = false;
	                }
				}else{
					helper.centerText("Continue as admin? (Y/N): ");
	                char again;
	                cin >> again;
	                if (toupper(again) != 'Y') {
	                    stay = false;
	                }
				}
			}else if(options[selected] == "Back"){
				stay = false;
			}
		}
	}
}
//login as customer
void UserInterface::loginCustomer(const vector<string>& options, const vector<vector<string>>& customerAcc){
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	string cUsername = "", cPass = "";
	int selected = 0;
	bool stay = true;
	
	while(stay){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		helper.centerText("== LOGIN AS CUSTOMER ==\n\n");
		
		for(int i = 0; i < options.size(); i++){
			string label = options[i];
			
			if(label == "Enter Username" && !cUsername.empty()){
				label += ": " + cUsername;
			}else if(label == "Enter Password" && !cPass.empty()){
				label += ": " + string(cPass.length(), '*');
			}
			
			if(label.empty()) {
		        helper.centerText("\n");
		        continue;
    		}
			
			if(i == selected){
				helper.centerText(">" + label + "<\n");
			}else{
				helper.centerText(" " + label + "\n");
			}
		}
		
		cout<<'\n';
		cout<<'\n';
		helper.drawBorder();
		
		int key = _getch();
		
		if(key == 0 || key==224){
			key = getch();
	        if (key == UP){
	        	do {
            		selected = (selected - 1 + options.size()) % options.size();
        		} while (options[selected].empty());
			}
	        if (key == DOWN){
	        	do {
		            selected = (selected + 1) % options.size();
		        } while (options[selected].empty());
			} 
		}else if(key == ENTER){
			if (options[selected].empty()) {
		        continue;
		    }
			
			if(options[selected] == "Enter Username"){
				panel.clearSkin();
				helper.centerText("Enter Username: ");
				cin>>cUsername;
			}else if(options[selected] == "Enter Password"){
				panel.clearSkin();
				helper.centerText("Enter Password: ");
				cin>>cPass;
			}else if(options[selected] == "Log In"){
				bool found = false;
				
				for(int i = 0; i < customerAcc.size(); i++){
					if(cUsername == customerAcc[i][0] && cPass == customerAcc[i][1]){
						panel.clearSkin();
						Panels customer;
						customer.customerPanel();
						found = true;
						break;
					}
				}
					
				if(!found){
					helper.centerText("Invalid username or password.\n");
	                helper.centerText("Try again? (Y/N): ");
	                char retry;
	                cin >> retry;
	                if (toupper(retry) != 'Y') {
	                    stay = false;
	                }
				}else{
					helper.centerText("Continue as Customer? (Y/N): ");
	                char again;
	                cin >> again;
	                if (toupper(again) != 'Y') {
	                    stay = false;
	                }
				}
			}else if(options[selected] == "Back"){
				stay = false;
			}
		}
	}
}
//register customer
void UserInterface::registerCustomer(const vector<string>& options,vector<vector<string>>& customerInfo, vector<vector<string>>& customerAcc){
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	int selected = 0;
	string username = "";
	string userpass = "";
	string userRname = "";
	string userContact = "";
	bool stay = true;
	
	while(stay){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		helper.centerText("== REGISTRATION ==\n\n");
		
		for(int i = 0; i < options.size(); i++){
			string label = options[i];
			if(label == "Enter a username" && !username.empty()){
				label += ": " + username;
			}else if(label == "Enter Name" && !userRname.empty()){
				label += ": " + userRname;
			}else if(label == "Enter Contact" && !userContact.empty()){
				label += ": " + userContact;
			}else if(label == "Enter password" && !userpass.empty()){
				label += ": " + string(userpass.length(), '*');
			}
			
			if(label.empty()) {
		        helper.centerText("\n");
		        continue;
    		}
			
			if(i == selected){
				helper.centerText(">" + label + "<\n");
			}else{
				helper.centerText(" " + label + "\n");
			}
		}
		
		cout<<'\n';
		cout<<'\n';
		helper.drawBorder();
		
		int key = _getch();
		
		if(key == 0 || key == 224){
			key = getch();
			if (key == UP){
	        	do {
            		selected = (selected - 1 + options.size()) % options.size();
        		} while (options[selected].empty());
			}
	        if (key == DOWN){
	        	do {
		            selected = (selected + 1) % options.size();
		        } while (options[selected].empty());
			} 
		}else if(key == ENTER){
			if (options[selected].empty()) {
		        continue;
		    }
			
			if(options[selected] == "Enter a username"){
				panel.clearSkin();
				helper.centerText("Enter a username: ");
				getline(cin, username);//
			}else if(options[selected] == "Enter Name"){
				panel.clearSkin();
				helper.centerText("Enter customer name: ");
				getline(cin, userRname);//
			}else if(options[selected] == "Enter Contact"){
				panel.clearSkin();
				helper.centerText("Enter you Contact No#: ");
				getline(cin, userContact);
			}else if(options[selected] == "Enter password"){
				panel.clearSkin();
				helper.centerText("Enter you password: ");
				getline(cin, userpass);
			}else if(options[selected] == "Submit"){
				AccountLogic aLogic;
				aLogic.createUser(username, userRname, userContact, userpass,customerInfo, customerAcc);
				break;
			}else if(options[selected] == "Back"){
				stay = false;
			}
		}
	}
}
//admin panel
int UserInterface::adminPanelUI(const vector<string>& options){
	int selected = 0;
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	
	while(true){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		helper.centerText("== ADMIN PANEL ==\n\n");
		
		for(int i = 0; i < options.size(); i++){
			string line;
			if(i == selected){
				line = ">   " + options[i] + "   <";
			}else{
				line = " "+options[i];
			}
			helper.centerText(line + "\n");
		}
		
		cout<<'\n';
		cout<<'\n';
		helper.drawBorder();
		
		int key = _getch();
		
		if(key == 224){
			key = _getch();
			if(key == UP){
				selected = (selected-1 + options.size()) % options.size();
			}else if(key == DOWN){
				selected = (selected + 1) % options.size();
			}
		}else if(key == ENTER){
			return selected + 1;
		}
	}
}
//adding panel
void UserInterface::addPanel(const vector<string>& options,vector<string>& prodName, vector<double>& price, vector<double>& rating, vector<double>& sale){
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	int selected = 0;
	string nProdName = "";
	string nPrice = "";
	bool stay = true;
	
	while(stay){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		helper.centerText("[ YOU ARE ADDING A PRODUCT ]\n\n");
		
		for(int i = 0; i < options.size(); i++){
			string label = options[i];
			if(label == "Enter a new product" && !nProdName.empty()){
				label += ": " + nProdName;
			}else if(label == "Enter a price for product" && !nPrice.empty()){
				label += " " + nProdName + ": " + nPrice;
			}
			
			if(label.empty()) {
		        helper.centerText("\n");
		        continue;
    		}
			
			if(i == selected){
				helper.centerText(">" + label + "<\n");
			}else{
				helper.centerText(" " + label + "\n");
			}
		}
		
		cout<<'\n';
		cout<<'\n';
		helper.drawBorder();
		
		int key = _getch();
		
		if(key == 0 || key == 224){
			key = getch();
			if (key == UP){
	        	do {
            		selected = (selected - 1 + options.size()) % options.size();
        		} while (options[selected].empty());
			}
	        if (key == DOWN){
	        	do {
		            selected = (selected + 1) % options.size();
		        } while (options[selected].empty());
			} 
		}else if(key == ENTER){
			if (options[selected].empty()) {
		        continue;
		    }
			
			if(options[selected] == "Enter a new product"){
				panel.clearSkin();
				helper.centerText("Enter a new product name: ");
				getline(cin, nProdName);
			}else if(options[selected] == "Enter a price for product"){
				panel.clearSkin();
				helper.centerText("Enter price for " + nProdName + ": ");
				getline(cin, nPrice);
			}else if(options[selected] == "Submit"){
				helper.addProduct(nProdName, nPrice, prodName, price, rating, sale);
				break;
			}else if(options[selected] == "Back"){
				stay = false;
			}
		}
	}
}
//update panel
void UserInterface::updatePanel(const vector<string>& options,vector<string>& prodName, vector<double>& price, const vector<double>& ratings, const vector<double>& sales){
	ostringstream oss;
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	int selected = 0;
	string nProdName = "";
	double nPrice = 0;
	int updateChoice;
	int itemSelected;
	bool stay = true;
	
	while(stay){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		helper.centerText("[ YOU ARE UPDATING A PRODUCT ]\n\n");
		
		helper.centerText("SELECT WHAT YOU WANT TO UPDATE\n\n");
		
		for(int i = 0; i < options.size(); i++){
			string line;
			if(i == selected){
				line = ">   " + options[i] + "   <";
			}else{
				line = " "+options[i];
			}
			
			if(line.empty()) {
		        helper.centerText("\n");
		        continue;
    		}
			
			helper.centerText(line + "\n");
		}
		
		cout<<'\n';
		cout<<'\n';
		helper.drawBorder();
		
		int key = _getch();
		
		if(key == 224){
			key = _getch();
			if (key == UP){
	        	do {
            		selected = (selected - 1 + options.size()) % options.size();
        		} while (options[selected].empty());
			}
	        if (key == DOWN){
	        	do {
		            selected = (selected + 1) % options.size();
		        } while (options[selected].empty());
			} 
		}else if(key == ENTER){
			if (options[selected].empty()) {
		        continue;
		    }
			
			if(options[selected] == "Product name"){
				itemSelected = helper.selectProduct(prodName, price, ratings, sales);
				updateChoice = 1;
				
				panel.clearSkin();
				helper.centerText("Enter a new product name for "+ prodName[itemSelected] + ": ");
				getline(cin, nProdName);
				helper.updateProduct(itemSelected, updateChoice, nProdName, 0, prodName, price);
			}else if(options[selected] == "Product Price"){
				itemSelected = helper.selectProduct(prodName, price, ratings, sales);
				updateChoice = 2;
				
				panel.clearSkin();
				oss<<fixed<<setprecision(2);
				oss<<"Enter a new price for "<<prodName[itemSelected]<<"("<<to_string(price[itemSelected])<<"): ";
				helper.centerText(oss.str());
				cin>>nPrice;
				helper.updateProduct(itemSelected, updateChoice, "", nPrice, prodName, price);
			}else if(options[selected] == "Back"){
				stay = false;
			}
		}
		
	}
}
//delete panel
void UserInterface::deletePanel(vector<string>& prodName, vector<double>& price, vector<double>& ratings, vector<double>& sales){
	int selected = 0;
	string oProdName;
	int itemSelected;
	bool stay = true;
	char resume;
	
	while(stay){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		helper.centerText("[ YOU ARE DELETING A PRODUCT ]\n\n");
		
		helper.centerText("SELECT WHAT YOU WANT TO DELETE\n\n");
		
		itemSelected = helper.selectProduct(prodName, price, ratings, sales);
		stay = helper.deleteProduct(itemSelected, prodName, price, ratings, sales);
		
		cout<<'\n';
		cout<<'\n';
		helper.drawBorder();
		
		helper.centerText("Continue Deleting?(Y/N): ");
		cin>>resume;
		
		if(toupper(resume) == 'Y'){
			stay = true;
		}
	}
}
//display products
void UserInterface::displayPanel(const vector<string>& options,vector<string>& prodName, vector<double>& price, vector<double>& ratings, vector<double>& sales){
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	int selected = 0;
	bool stay = true;
	double totalSales = 0;
	
	while(stay){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n'<<'\n';
		
		helper.centerText("PRODUCT INVENTORY\n\n");
		
		ostringstream header;
		header<<left
			<<setw(6)<<"ID: "
			<<setw(18)<<"Product Name"
			<<setw(18)<<"Product Price"
			<<setw(18)<<"Product Ratigs"
			<<setw(18)<<"Product Sales";
		
		helper.centerText(header.str() + "\n");
		helper.centerText(string(42, '-') + "\n");
		
		for(int i = 0; i < prodName.size(); i++){
			ostringstream row;
			
			row <<fixed<<left
				<<setw(6)<<to_string(i+1)
				<<setw(18)<< prodName[i]
				<<setw(18)<<setprecision(2)<< price[i]
				<<setw(18)<<setprecision(2)<< ratings[i]
				<<setw(18)<<setprecision(2)<< sales[i];
			
			helper.centerText(" " + row.str() + "\n");
			
			totalSales += sales[i];
		}
		
		for(int i = 0; i < options.size(); i++){
			string line;
			if(i == selected){
				line = ">   " + options[i] + "   <";
			}else{
				line = " " + options[i];
			}
			helper.centerText(line + "\n");
		}
		
		cout<<'\n'<<'\n';
		helper.drawBorder();
		
		int key = _getch();

	    if(key == 0 || key == 224){
	        key = _getch();
	        if (key == UP) selected = (selected - 1 + prodName.size()) % prodName.size();
	        if (key == DOWN) selected = (selected + 1) % prodName.size();
	    }else if (key == ENTER){
	    	if(options[selected] == "Print"){
	    		helper.printProdInfo(prodName, price, ratings, sales, totalSales);
	    		
	    		helper.centerText("Product Information successfully printed to 'productInfoFile.txt'\n");
	    		system("pause");
			}else if(options[selected] == "Back"){
				stay = false;
			}
	    }
	}
}
//display bargraph
void UserInterface::diplayGraph(const vector<string>& options, vector<string>& prodName, vector<double>& ratings, vector<double>& sales){
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	const int bLetterE = 69;
	const int sLetterE = 101;
	int selected = 0;
	bool stay = true;
	
	while(stay){
		panel.clearSkin();
		
		helper.drawBorder();
		cout<<'\n';
		cout<<'\n';
		
		helper.centerText("[ GRAPHS OF THE PRODUCT ]\n\n");
		
		helper.centerText("SELECT WHAT YOU WANT TO UPDATE\n\n");
		
		for(int i = 0; i < options.size(); i++){
			string line;
			if(i == selected){
				line = ">   " + options[i] + "   <";
			}else{
				line = " "+options[i];
			}
			
			if(line.empty()) {
		        helper.centerText("\n");
		        continue;
    		}
			
			helper.centerText(line + "\n");
		}
		
		cout<<'\n';
		cout<<'\n';
		helper.drawBorder();
		
		int key = _getch();
		
		if(key == 224){
			key = _getch();
			if (key == UP){
	        	do {
            		selected = (selected - 1 + options.size()) % options.size();
        		} while (options[selected].empty());
			}
	        if (key == DOWN){
	        	do {
		            selected = (selected + 1) % options.size();
		        } while (options[selected].empty());
			}
		}else if(key == ENTER){
			if (options[selected].empty()) {
		        continue;
		    }
			
			if(options[selected] == "Product Ratings"){
				helper.drawGraph(prodName, ratings);
				
				cout<<'\n';
				helper.centerText("Press any key to EXIT");
				key = _getch();
			}else if(options[selected] == "Product Sales"){
				helper.drawGraph(prodName, sales);
				
				cout<<'\n';
				helper.centerText("Press any key to EXIT");
				key = _getch();
			}else if(options[selected]== "Back"){
				stay = false;
			}
		}
	}
}
