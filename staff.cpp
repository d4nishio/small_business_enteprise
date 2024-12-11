#include "staff.h"
#include "DBConnection.h"
#include <vector>
using namespace std;

staff::staff()
{
	//employee credentials
	empID = "";
	empPasswd = "";
	empName = "";

	//admin credentials
	adminID = "";
	adminPasswd = "";

}

//employee
staff::staff(std::string empID, std::string empName, std::string empPasswd)
{
	this->empID = empID;
	this->empName = empName;
	this->empPasswd = empPasswd;
}

//admin
staff::staff(std::string adminID, std::string adminPasswd)
{
	this->adminID = adminID;
	this->adminPasswd = adminPasswd;
}


bool staff::empLogin() // employee login
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM employee WHERE empID=? AND empPasswd=?");
	db.stmt->setString(1, empID);
	db.stmt->setString(2, empPasswd);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			empID = db.res->getInt("empID");
			empPasswd = db.res->getString("empPasswd");
		}
		db.~DBConnection();
		return true;
	}
	else {

		db.~DBConnection();
		return false;
	}
}

bool staff::adminLogin() // admin login
{
	DBConnection db;
	db.prepareStatement("SELECT * FROM admin WHERE adminID=? AND adminPasswd=?");
	db.stmt->setString(1, adminID);
	db.stmt->setString(2, adminPasswd);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			adminID = db.res->getString("adminID");
			adminPasswd = db.res->getString("adminPasswd");
		}
		db.~DBConnection();
		return true;
	}
	else {

		db.~DBConnection();
		return false;
	}
}

void staff::addEmployee() // register an employee
{
	DBConnection db;
	db.prepareStatement("Insert into employee (empID,empName,empPasswd) VALUES (?,?,?)");
	db.stmt->setString(1, empID);
	db.stmt->setString(2, empName);
	db.stmt->setString(3, empPasswd);
	db.QueryStatement();
	db.~DBConnection();
}

void staff::delEmployee()
{
	DBConnection db;
	db.prepareStatement("DELETE FROM employee WHERE empID=?");
	db.stmt->setString(1, empID);
	db.QueryStatement();
	db.~DBConnection();
}

staff::~staff()
{

}
