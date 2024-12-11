#pragma once
#ifndef STAFF_H
#define STAFF_H
#include <vector>
#include <string>
class staff
{
public:
	std::string empID, empName, empPasswd, adminID, adminPasswd;
	
	staff();

	//employee account
	staff(std::string empID, std::string empName, std::string empPasswd);

	//admin account
	staff(std::string adminID, std::string adminPasswd);

	//functions for employee
	bool empLogin();

	//functions for admin
	bool adminLogin();
	void addEmployee();
	void delEmployee();

	~staff();
};

#endif
