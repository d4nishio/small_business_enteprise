#include "purchase.h"
#include <string> 
#include <iomanip>
#include <sstream>
#include "item.h"

using namespace std;

purchase::purchase()
{
	purchaseID = 0;
	userID = 0;
	date = "";
}

int purchase::countItem() 
{
	int count = 0;
	for (int i = 0; i < items.size(); i++) {
		count += items[i].second;
	}
	return count;
}

double purchase::totalPrice() 
{
	double total = 0;
	for (int i = 0; i < items.size(); i++) 
	{
		total += items[i].first.itemPrice * items[i].second;
	}
	return total;
}

void purchase::insertItem() 
{
	DBConnection db;
	db.prepareStatement("INSERT INTO purchase(userID) VALUES (?)");
	db.stmt->setInt(1, userID);
	db.QueryStatement();
	purchaseID = db.getGeneratedId();
	// get back the generated id to be used during insertion of purchased items

	string purchased = "INSERT INTO item_purchase(purchaseID,itemID,quantity) VALUES "; 
	for (int i = 0; i < items.size(); i++) 
	{
		purchased += "(?,?,?),";
	}
	purchased.erase(purchased.size() - 1); // remove the extra comma at the end
	
	db.prepareStatement(purchased);
	for (int i = 0; i < items.size(); i++) 
	{
		db.stmt->setInt(i * 3 + 1, purchaseID);
		db.stmt->setString(i * 3 + 2, items[i].first.itemID);
		db.stmt->setInt(i * 3 + 3, items[i].second);
	}

	db.QueryStatement();
	db.~DBConnection();
}

void purchase::addItem(item item, int quantity) 
{
	items.push_back({ item,quantity });
}


void purchase::updateStock(string id, int quantity)
{
	DBConnection db;
	db.prepareStatement("UPDATE item SET itemStock=? WHERE itemID=?");
	db.stmt->setInt(1, quantity);
	db.stmt->setString(2, id);

	db.QueryStatement();
	db.~DBConnection();
}




