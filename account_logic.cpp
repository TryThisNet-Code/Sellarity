#include <iostream>
#include "panel.h"
#include <string>
#include "helper.h"
#include "account_logic.h"
#include <stdexcept>

Panels aPanel;
Helper aHelper;

void AccountLogic::createUser(const string& username,const string& userRname,const string& userContact,const string& userpass,vector<vector<string>>& customerInfo, vector<vector<string>>& accounts){
	try{
		accounts.push_back({username,userpass});
		
		aHelper.centerText("Successfully registered user" + username + "\n");
		system("pause");
	}catch(const invalid_argument& e){
		aHelper.centerText("Invalid input. Please enter a valid input.\n");
		system("pause");
	}
}
