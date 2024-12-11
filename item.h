#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include "DBConnection.h"

class item
{
	public:
		int itemCategory, itemStock;
		std::string itemName, itemDetail, itemID;
		double itemPrice;

		item();
		item(sql::ResultSet* data);
		static std::vector<item> displayCategory(int category);
		static std::vector<item> displayAllItem();
		static item searchItem(std::string itemID);

		~item();
};


#endif
