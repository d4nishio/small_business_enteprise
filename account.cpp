#include "account.h"
#include "DBConnection.h" 
using namespace std;

account::account() 
{	
	//user credentials
	userID = 0;
	username = "";
	email = "";
	password = "";
	phoneNum = "";
	birthYear = 0;
	address = "";
}

//user
account::account(int userID, int birthYear, std::string username, std::string password, std::string phoneNum, std::string email, std::string address) 
{
	this->userID = userID;
	this->username = username;
	this->email = email;
	this->password = password;
	this->phoneNum = phoneNum;
	this->birthYear = birthYear;
	this->address = address;
}

bool account::userLogin() // user login
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM user WHERE username=? AND userPasswd=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			userID = db.res->getInt("userID");
			username = db.res->getString("username");
			email = db.res->getString("email");
			password = db.res->getString("userPasswd");
			phoneNum = db.res->getString("phoneNum");
			birthYear = db.res->getInt("birthYear");
			address = db.res->getString("address");

		}
		db.~DBConnection();
		return true;
	}
	else {

		db.~DBConnection();
		return false;
	}
}

void account::userInsert() // insert the inputs about user account to be made
{

	DBConnection db;
	db.prepareStatement("Insert into user (username,email,userPasswd,phoneNum,birthYear,address) VALUES (?,?,?,?,?,?)");
	db.stmt->setString(1, username);
	db.stmt->setString(2, email);
	db.stmt->setString(3, password);
	db.stmt->setString(4, phoneNum);
	db.stmt->setInt(5, birthYear);
	db.stmt->setString(6, address);
	db.QueryStatement();
	db.~DBConnection();
}

void account::userUpdate() // update user's account
{
	DBConnection db;
	db.prepareStatement("UPDATE user SET username=?, email=?, userPasswd=?, phoneNum=?, birthYear=?, address=? WHERE userID=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, email);
	db.stmt->setString(3, password);
	db.stmt->setString(4, phoneNum);
	db.stmt->setInt(5, birthYear);
	db.stmt->setString(6, address);
	db.stmt->setInt(7, userID);
	db.QueryStatement();
	db.~DBConnection();
}

void account::userRemove() // delete user's account
{
	DBConnection db;
	db.prepareStatement("DELETE FROM user WHERE userID=?");
	db.stmt->setInt(1, userID);
	db.QueryStatement();
	db.~DBConnection();
}

account::~account() 
{

}
