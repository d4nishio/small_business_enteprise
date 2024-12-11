#pragma once
#ifndef PURCHASE_H
#define PURCHASE_H

#include <string>
#include <vector>
#include "item.h"

class purchase
{
public:

	int purchaseID, userID;
	std::string date;
	std::vector<std::pair<item, int>> items; // pair of item and its quantity, represents the item_purchase table
	purchase();
	int countItem();
	double totalPrice();
	void addItem(item item, int quantity);
	void insertItem();
	void updateStock(std::string id, int quantity);
};

#endif

