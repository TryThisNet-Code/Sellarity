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

int main(){
	Panels panels;
	Helper helper;
	UserInterface ui;
	
	vector<string> mainMenu = {" Log in as Admin", " Log in as Customer","", " Exit"};
	vector<string> loginMenu = {"Enter Username", "Enter Password","", "Log In", "Back"};
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
			case 3:
				exit(0);
				break;
		}
	}
	return 0;
}

