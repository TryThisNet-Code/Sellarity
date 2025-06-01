#include <vector>
#include "panel.h"
#include "navigation.h"
#include "helper.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <conio.h>

using namespace std;

Panels sPanel;
//function to get console width
int Helper::getConsoleWidth(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns = 80; // default width
    
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return columns;
}
//function to center the text
void Helper::centerText(const string& text){
	int width = getConsoleWidth();
    int padding = max(0, static_cast<int>(width - text.length()) / 2);
    cout << string(padding, ' ') << text;
}
//add product func
void Helper::addProduct(const string& name, const string& price,vector<string>& prodName, vector<double>& prices, vector<double>& ratings, vector<double>& sales){
	try{
		string productName = name;
		double prodPrice = stod(price);
		
		prodName.push_back(productName);
		prices.push_back(prodPrice);
		ratings.push_back(0);
		sales.push_back(0);
		
		centerText(productName + " has been added to the product list\n");
		system("pause");
		
		
	}catch(const std::invalid_argument& e){
		centerText("Invalid input. Please enter a valid number.\n");
		system("pause");
	}
}
//function for seleted a product
int Helper::selectProduct(const vector<string>& prodName, const vector<double>& prices, const vector<double>& ratings, const vector<double>& sales){
	const int ENTER = 13;
	const int UP = 72;
	const int DOWN = 80;
	int selected = 0;
	bool stay = true;
	
	while(stay){
		sPanel.clearSkin();
		
		centerText("SELECT WHICH PRODUCT YOU WANT TO UPDATE\n\n");
		
		ostringstream header;
		header<<left
			<<setw(6)<<"ID: "
			<<setw(18)<<"Product Name"
			<<setw(18)<<"Product Price"
			<<setw(18)<<"Product Ratigs"
			<<setw(18)<<"Product Sales";
		
		centerText(header.str() + "\n");
		centerText(string(42, '-') + "\n");
		
		for(int i = 0; i < prodName.size(); i++){
			ostringstream row;
			
			row <<fixed<<left
				<<setw(6)<<to_string(i+1)
				<<setw(18)<< prodName[i]
				<<setw(18)<<setprecision(2)<< prices[i]
				<<setw(18)<<setprecision(2)<< ratings[i]
				<<setw(18)<<setprecision(2)<< sales[i];
			
			if(i == selected){
		        centerText(">" + row.str() + "<\n");
		    }else{
		        centerText(" " + row.str() + "\n");
		    }
		}
		
		int key = _getch();

	    if(key == 0 || key == 224){
	        key = _getch();
	        if (key == UP) selected = (selected - 1 + prodName.size()) % prodName.size();
	        if (key == DOWN) selected = (selected + 1) % prodName.size();
	    }else if (key == ENTER){
	    	return selected;
	        stay = false;
	    }
	}
}
//update product
void Helper::updateProduct(const int& prodID, const int& uChoice, const string& nName, const double& nPrice, vector<string>& prodName, vector<double>& prices){
	try{
		string oName;
		double oPrice;
		
		oName = prodName[prodID];
		oPrice = prices[prodID];
		
		switch(uChoice){
			case 1:
				prodName[prodID] = nName;
				centerText("Successfully changed the name of " + oName + " to " + nName + "!\n");
				system("pause");
				break;
			case 2:
				prices[prodID] = nPrice;
				centerText("Successfully change the price of " + prodName[prodID] +"("+to_string(oPrice)+")" + " to " + to_string(nPrice) + "\n");
				system("pause");
				break;
		}
		
	}catch(const std::invalid_argument& e){
		centerText("Invalid input. Please enter a valid number or text.\n");
		system("pause");
	}
}
//delete product
bool Helper::deleteProduct(const int& prodID, vector<string>& prodName, vector<double>& prices, vector<double>& ratings, vector<double>& sales){
	try{
		string oName = prodName[prodID];
		
		centerText(oName + " has been removed to the product list\n");
		
		//process of deleting a product
		prodName.erase(prodName.begin() + (prodID));
		prices.erase(prices.begin() + (prodID));
		ratings.erase(ratings.begin() + (prodID));
		sales.erase(sales.begin() + (prodID));
		
		return false;
	}catch(const std::invalid_argument& e){
		centerText("Invalid input. Please enter a valid text.\n");
		system("pause");
	}
}
//draw ratings graph
void Helper::drawRatingGraph(const vector<string>& prodName, const vector<double>& ratings){
	double maxRating = *max_element(ratings.begin(), ratings.end());
    int maxBarLength = 25;
	
	//find the longest lines
    size_t nameWidth = 0;
    for (const auto& name : prodName) nameWidth = max(nameWidth, name.length());

    // build all lines
    vector<string> lines;
    for (size_t i = 0; i < prodName.size(); i++) {
        int bars = static_cast<int>((ratings[i] / maxRating) * maxBarLength);
        ostringstream line;
        line << left << setw(static_cast<int>(nameWidth)) << prodName[i] << " | "
             << string(bars, '*') << " "
             << fixed << setprecision(1) << ratings[i];
        lines.push_back(line.str());
    }

    // add the scale thingy
    string dashes = string(maxBarLength, '-');
    string scale = "0     5     10    15    20    25";
    string prefix = string(nameWidth + 3, ' ');
    lines.push_back(prefix + dashes);
    lines.push_back(prefix + scale);

    // find the long one for good centering
    size_t maxLineLength = 0;
    for (const auto& l : lines)maxLineLength = max(maxLineLength, l.length());

    sPanel.clearSkin();
    centerText("== Product Ratings Bar Graph ==");
    cout << "\n\n";
	
	//printing
    for (const auto& l : lines) {
        int padding = max(0, (getConsoleWidth() - static_cast<int>(maxLineLength)) / 2);
        cout << string(padding, ' ') << l << '\n';
    }
}
//draw sales graph
void Helper::drawSalesGraph(const vector<string>& prodName, const vector<double>& sales){
	double maxSales = *max_element(sales.begin(), sales.end());
    int maxBarLength = 25;
	
	//find the longest lines
    size_t nameWidth = 0;
    for(const auto& name : prodName) nameWidth = max(nameWidth, name.length());

    // build all lines
    vector<string> lines;
    for (size_t i = 0; i < prodName.size(); i++) {
        int bars = static_cast<int>((sales[i] / maxSales) * maxBarLength);
        ostringstream line;
        line << left << setw(static_cast<int>(nameWidth)) << prodName[i] << " | "
             << string(bars, '*') << " "
             << fixed << setprecision(1) << sales[i];
        lines.push_back(line.str());
    }

    // add the scale thingy
    string dashes = string(maxBarLength, '-');
    string scale = "0     5     10    15    20    25";
    string prefix = string(nameWidth + 3, ' ');
    lines.push_back(prefix + dashes);
    lines.push_back(prefix + scale);

    // find the long one for good centering
    size_t maxLineLength = 0;
    for (const auto& l : lines) maxLineLength = max(maxLineLength, l.length());

    sPanel.clearSkin();
    centerText("== Product Ratings Bar Graph ==");
    cout<<"\n\n";
	
	//printing
    for (const auto& l : lines) {
        int padding = max(0, (getConsoleWidth() - static_cast<int>(maxLineLength)) / 2);
        cout << string(padding, ' ') << l << '\n';
    }
}

