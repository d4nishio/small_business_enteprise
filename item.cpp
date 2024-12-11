#include "item.h"
#include <vector> 
using namespace std;

item::item() {
	itemID = "";
	itemName = "";
	itemPrice = 0;
	itemDetail = "";
	itemCategory = 0;
	itemStock = 0;
}

item::item(sql::ResultSet* data) {
	itemID = data->getString("itemID");
	itemName = data->getString("itemName");
	itemPrice = data->getDouble("itemPrice");
	itemCategory = data->getInt("itemCategory");
	itemDetail = data->getString("itemDetail");
	itemStock = data->getInt("itemStock");
}

vector<item> item::displayAllItem()
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM item");

	vector<item> items;
	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		while (db.res->next()) {
			item displayItem(db.res);
			items.push_back(displayItem);
		}
	}

	db.~DBConnection();
	return items;

}

vector<item> item::displayCategory(int itemCategory) 
{
	
	string query = "SELECT * FROM item WHERE itemCategory =?";
	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setInt(1, itemCategory);

	vector<item> items;
	db.QueryResult();
	if (db.res->rowsCount() > 0) {
		while (db.res->next()) {
			item showItem(db.res);
			items.push_back(showItem);
		}
	}

	db.~DBConnection();
	return items;
}

item item::searchItem(string itemID) 
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM item WHERE itemID=?");
	db.stmt->setString(1, itemID);
	db.QueryResult();

	item result;
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			item found(db.res);
			result = found;
		}
	}
	db.~DBConnection();
	return result;
}


item::~item() 
{

}
