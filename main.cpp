#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "panel.h"
#include <string>
#include "navigation.h"
#include "helper.h"

using namespace std;

vector<vector<string>> adminAcc = {{"admin", "12345678"}};
vector<vector<string>> userAcc = {{"user1", "12345678"}};
vector<vector<string>> customerInfo = {{"Franz Angels", "09332452663"}, 
									   {"Christian Bautis", "09352452323"}, 
									   {"Kurt Craig", "09337452363"}, 
									   {"Georgy Angelo", "09132452883"}, 
									   {"Rhodmar Villanueva", "09332452323"}};

int main(){
	Panels panels;
	Helper helper;
	UserInterface ui;
	
	vector<string> mainMenu = {" Log in as Admin", " Log in as Customer", "","Don't have an account Register here","", "Exit"};
	vector<string> loginMenu = {"Enter Username", "Enter Password","", "Log In", "Back"};
	vector<string> registerMenu = {"Enter a username", "Enter Name", "Enter Contact","Enter password","", "Submit","Back"};
	int choice;
	
	while(true){
		//for mainMenu
		
		int choice = ui.landingScreen(mainMenu);
		
		switch(choice){
			case 1://admin panel login
				ui.loginAdmin(loginMenu, adminAcc);
				break;
			case 2://crustomer panel login
				ui.loginCustomer(loginMenu, userAcc);
				break;
			case 4:
				//register customer
				ui.registerCustomer(registerMenu, customerInfo ,userAcc);
				break;
			case 6:
				exit(0);
				break;
		}
	}
	return 0;
}

