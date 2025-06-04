#ifndef ACCOUNT_LOGIC_H
#define ACCOUNT_LOGIC_H
#include <vector>
#include <string>

using namespace std;

class AccountLogic{
	public:
		void createUser(const string& username,const string& userRname,const string& userContact,const string& userpass,vector<vector<string>>& customerInfo, vector<vector<string>>& accounts);
};

#endif
