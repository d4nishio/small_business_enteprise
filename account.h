#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
class account
{
public:
	int userID, birthYear;
	std::string username, password, phoneNum, email, address;
	account();

	//customer account
	account(int userID, int birthYear, std::string username, std::string password, std::string phoneNum, std::string email, std::string address);

	//functions for customer
	bool userLogin();
	void userInsert();
	void userUpdate();
	void userRemove();
	
	~account();
};

#endif