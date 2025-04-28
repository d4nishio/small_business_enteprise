#include <iostream>
#include <mysql/jdbc.h> 
#include <conio.h>
#include <iomanip>
#include <sstream>
#include <utility>
//custom classes
#include "account.h"
#include "console.h"
#include "purchase.h"
#include "staff.h"
#include "report.h"
using namespace std;

//hackathon

void accountRegistration(); // Function to register new account
void loginPage(); // Function to log in for user and staff(employee & admin)

//employee functions
void empLoginPage(); // Function for employee to login after being directed from loginPage() function
void empPage(staff emp); // Function to display employee page menu
void itemRestock(staff emp); // Function for employee to view and update item stock

//admin functions
void adminLoginPage(); // Function for admin to login after being directed from loginPage() function
void adminPage(staff admin); // Function to display admin page menu
void viewItemStocks(staff admin); // Function to display item stocks
void empRegister(staff admin); // Function for admin to add new employee
void empDelete(staff admin); // Function for admin to remove/delete an employee
void generateSalesReport(staff admin); // Function for admin to generate sales report analysis

//user functions
void userPage(account user); // Function to display user page menu
account userProfile(account user); // Function to display and edit user profile
account userShopping(account user); // Shopping function
purchase browseItems(account user, int category, string &cateName, purchase shoppingCart); // Function to browse and add item
purchase viewCart(account user, purchase shoppingCart); // Function to view shopping cart, remove items from cart and checkout

string loginPassword(string back); // Funtion to hide password from being displayed
bool checkNumeric(string input); // Function to check input year is numeric

//------------------------------------------------------------------------------------------------------------------

int main() // main page
{
    console mainpage;   
    mainpage.navigation = "\n\t\t\t\t\t\t\t\t\t\t\tWELCOME TO GROCERY STORE HOMEPAGE\n";
    mainpage.choices("Register");
    mainpage.choices("Login");
    mainpage.choices("Exit");

    while (1) // while(1) make sure it wont stop until user enter option 3
	{ 
        switch (mainpage.prompt()) 
        {
        case 1:
            accountRegistration();
            break;
        case 2:
			loginPage();
            break;
        case 3:
            return 0;
			break;
        default:
            break;
        }
    }
}

void accountRegistration() // user registration page
{
    account newAccount;
    console registration;

	registration.navigation = "> Registration\n\t\t\t\t\t\t\t\t\t\t\t\t\tREGISTRATION PAGE\n";
	registration.choices("Username");
	registration.choices("Email");
	registration.choices("Password");
	registration.choices("Phone Number");
	registration.choices("Year of Birth");
	registration.choices("Home Address");
	registration.choices("Confirm");
	registration.choices("Back");

	
	string reginput, repassword;
	int i = 0; // to make sure every credentials are entered
	string address;
	while (1) {

		switch (registration.prompt()) {
		case 1:
			cout << "\nEnter username: ";
			cin >> reginput;

			if (reginput.length() < 5) {
				cout << "\nThe username must be at least 5 character long and no spaces";
				_getch();
			}
			else 
			{
				newAccount.username = reginput;
				registration.setValue(0, newAccount.username);
				i++;
			}
			break;
		case 2:
			cout << "\nEnter email: ";
			cin >> newAccount.email;

			if (newAccount.email.find('@') == string::npos)
			{
				cout << "Invalid email format. Email must contain @ symbol." << endl;
				_getch();
			}
			else
			{
				registration.setValue(1, newAccount.email);
				i++;
			}

			break;
		case 3:
			cout << "\nEnter password: ";
			cin >> reginput;

			if (reginput.length() < 6) {
				cout << "The password must be at least be 6 character long";
				_getch();
			}
			else {

				newAccount.password = reginput;
				cout << "\nVerify password: ";
				c:
				cin >> repassword;

				if (repassword == newAccount.password) {
					registration.setValue(2, newAccount.password);
					i++;
				}
				else {
					cout << "\nThe password you entered does not match\n";
					cout.clear();
					_getch();
					cout << "\nEnter password again: ";
					goto c;
				}
			}
			break;
		case 4:
			cout << "\nEnter phone number: ";
			cin >> reginput;

			if (newAccount.phoneNum.find_first_not_of("0123456789") != string::npos)
			{
				cout << "Invalid phone number. Please enter numeric values only." << endl;
			}
			else
			{
				newAccount.phoneNum = reginput;
				registration.setValue(3, newAccount.phoneNum);
				i++;
			}
			break;
		case 5:
			cout << "\nEnter year of birth: ";
			cin >> reginput;

			if (checkNumeric(reginput) && reginput.length() == 4) {

				newAccount.birthYear = stoi(reginput);

				registration.setValue(4, to_string(newAccount.birthYear));
				i++;
			}
			else {
				cout << "Year of birth must be numeric and only 4 digits";
				_getch();
			}
			break;
		case 6:
			cout << "\nEnter home address: ";
			getline(cin, address);

			if (address != "") {
				newAccount.address = address;
				registration.setValue(5, newAccount.address);
				i++;
			}

			break;
		case 7:
			if (i == 6) 
			{
				newAccount.userInsert();
				cout << "\nAccount is succesfully created";
				_getch();
				return;
			}
			else {
				cout << "\nThe credentials you entered is not complete or repeated. Please try again\n";
				i = 0;
				_getch();
			}
			break;
		case 8:
			i = 0;
			return;
		default:
			break;
		}
	}
}

void loginPage() //main login page
{
	console loginPage;
	account user;
	loginPage.navigation = "> Login\n\t\t\t\t\t\t\t\t\t\t\t\t\tLOG-IN PAGE\n";
	loginPage.choices("Username");
	loginPage.choices("Password");
	loginPage.choices("Login");
	loginPage.choices("Back");

	string pw;
	while (1)
	{
		switch (loginPage.prompt())
		{
		case 1:
			cout << "\nEnter your username: ";
			cin >> user.username;

			//checking whether the user is admin, employee or customer based on their username(admin and employee will enter their ID)
			if (user.username[0] == 'A' && user.username.length() == 4)
			{
				adminLoginPage(); // admin will be redirected to their login function
			}
			else if (user.username[0] == 'E' && user.username.length() == 4)
			{
				empLoginPage();  // employee will be redirected to their login function
			}
			else
			{
				loginPage.setValue(0, user.username);
			}
			break;

		case 2:
			cout << "Insert Password: ";
			user.password = loginPassword(pw);	 // function call to hide password
			
			loginPage.setValue(1, "**********"); // print out these instead of actual password
			break;

		case 3:
			if (user.userLogin())
			{
				cout << endl << "You'll be directed to the User Main Page\n";
				system("pause");
				system("cls");
				userPage(user); //this will bring customer to customer's page when they login
			}
			else
			{
				char retry;
				cout << "The username or password you entered is invalid. Do you wish to try again? (y/n): ";
				cin >> retry;

				if (retry == 'y' || retry == 'Y')
				{
					cin.clear();
					_getch();
				}
				else
				{
					cout << endl << "You'll be directed back to the Home Page\n";
					system("pause");
					return;
				}
			}
			break;

		case 4:
			return;
			break;

		default:
			break;
		}
	}
}

void empLoginPage() //employee login page
{
	console empLog;
	staff emp;
	empLog.navigation = "> Login > Employee Login\n\t\t\t\t\t\t\t\t\t\t\t\tEMPLOYEE LOG-IN PAGE\n";
	empLog.choices("Employee ID");
	empLog.choices("Password");
	empLog.choices("Login");
	empLog.choices("Back");

	string pw;
	while (1)
	{
		switch (empLog.prompt())
		{
		case 1:
			cout << "\nEnter your ID: ";
			cin >> emp.empID;

			empLog.setValue(0, emp.empID);
			break;

		case 2:
			cout << "\nEnter your password: ";
			
			emp.empPasswd = loginPassword(pw); // function call to hide password

			empLog.setValue(1, "**********");
			break;

		case 3:
			if (emp.empLogin())
			{
				cout << endl << "You'll be directed to the Employee Page\n";
				system("pause");
				empPage(emp);
			}
			else
			{
				char retry;
				cout << "The username or password you entered is invalid. Do you wish to try again? (y/n): ";
				cin >> retry;

				if (retry == 'y' || retry == 'Y')
				{
					cin.clear();
					_getch();
				}
				else
				{
					cout << endl << "You'll be directed back to the previous page\n";
					system("pause");
					main();
				}
			}
			break;

		case 4:
			return;
			break;

		default:
			break;
		}
	}
}

void empPage(staff emp)
{
	console empPage;

	empPage.navigation = "> Employee Main Page\n\t\t\t\t\t\t\t\t\t\t\t\tEmployee" + emp.empID + " reporting for work\n";
	empPage.choices("Item view & Restocks");
	empPage.choices("Log out");

	while (1)
	{
		switch (empPage.prompt())
		{
		case 1:
			itemRestock(emp);
			break;

		case 2:
			return;
			break;

		default:
			break;
		}
	}
}

void itemRestock(staff emp)
{
	console viewStock;
	item toRestock;
	vector<item> stocks;
	purchase update;
	int qty;
	int updatedStock = 0;
	string itemID;

	while (1)
	{
		system("cls");

		stocks = item::displayAllItem(); 
		cout << "> Item Restock section\n\t\t\t\t\t\t\t\t\t\t\tITEM VIEW & RESTOCK \n\n";

		viewStock.longline();// print a long line
		cout << "\t\t\t\t\t\t\t ========================================================================================\n";
		cout << "\t\t\t\t\t\t\t | " << setw(7) << left << "Item ID" << " | " << setw(20) << left << "Name" << " | " << setw(9) << left << "Price(RM)" << " | " << setw(30) << left << "Details" << " | " << setw(6) << left << "Stocks" << " | " << endl;
		cout << "\t\t\t\t\t\t\t ========================================================================================\n";

		for (int i = 0; i < stocks.size(); i++)
		{
			cout << fixed << setprecision(2) << "\t\t\t\t\t\t\t | " << setw(7) << left << stocks[i].itemID << " | " << setw(20) << left << stocks[i].itemName << " | " << setw(9) << left << stocks[i].itemPrice << " | " << setw(30) << left << stocks[i].itemDetail << " | " << setw(6) << left << stocks[i].itemStock << " | " << endl;
		}
		cout << "\t\t\t\t\t\t\t ========================================================================================\n";

		cout << endl;
		viewStock.longline();// print a long line

		cout << "Press A key if you decided to re-stock. Press Esc key to return \n";

		char input = '\0';
		input = _getch();
		switch (input)
		{
		case 27: //esc key. employee will return to employee page
			return empPage(emp);
			break;

		case 97: //A key. indicating "add" if employee decided to restock items
			cout << "Enter item ID to be re-stocked: ";
			cin >> itemID;

			toRestock = item::searchItem(itemID);

			cout << "Enter quantity to re-stock    : ";
			cin >> qty;

			if (qty > 0)
			{

				updatedStock = toRestock.itemStock + qty;
				update.updateStock(itemID, updatedStock);

				cout << "Item has been re-stocked.\n";
			}
			else
				cout << "Please enter a valid input.\n";

			_getch();
			break;

		default:
			break;
		}

	}

}

void adminLoginPage() //admin login page
{
	console adminLog;
	staff admin;
	adminLog.navigation = "> Login > Admin Login\n\t\t\t\t\t\t\t\t\t\t\t\tADMIN LOG-IN PAGE\n";
	adminLog.choices("Admin ID");
	adminLog.choices("Password");
	adminLog.choices("Login");
	adminLog.choices("Back");

	string pw;
	while (1)
	{
		switch (adminLog.prompt())
		{
		case 1:
			cout << "\nEnter your ID: ";
			cin >> admin.adminID;

			adminLog.setValue(0, admin.adminID);
			break;

		case 2:
			cout << "\nEnter your password: ";
			
			admin.adminPasswd = loginPassword(pw); // function call to hide password

			adminLog.setValue(1, "**********");
			break;

		case 3:
			if (admin.adminLogin())
			{
				cout << endl << "You'll be directed to the Admin Page\n";
				system("pause");
				adminPage(admin);
				_getch();
			}
			else
			{
				char retry;
				cout << "The username or password you entered is invalid. Do you wish to try again? (y/n): ";
				
				retry = _getch();
				if (retry == 'y' || retry == 'Y')
				{
					cin.clear();
				}
				else
				{
					cout << endl << "You'll be directed back to the previous page\n";
					system("pause");
					return;
				}
			}
			break;

		case 4:
			return;
			break;

		default:
			break;
		}
	}
}

void adminPage(staff admin)
{
	console adminPage;

	adminPage.navigation = "> Admin Main Page\n\t\t\t\t\t\t\t\t\t\t\t\tAdmin " + admin.adminID + " reporting for work\n";
	adminPage.choices("View item Stocks");
	adminPage.choices("Register employee");
	adminPage.choices("Delete employee");
	adminPage.choices("View Sales Report");
	adminPage.choices("Log out");

	while (1)
	{
		switch (adminPage.prompt())
		{
		case 1:
			viewItemStocks(admin);
			break;

		case 2:
			empRegister(admin);
			break;

		case 3:
			empDelete(admin);
			break;
		case 4:
			generateSalesReport(admin);
			break;

		case 5:
			return;
			break;

		default:
			break;
		}
	}
}

void viewItemStocks(staff admin)
{
	console view;
	vector<item> stocks;
	string urgent;
	int lowestStock = 10;

	while (1)
	{
		system("cls");

		stocks = item::displayAllItem();
		cout << "> View Item Stocks section\n\t\t\t\t\t\t\t\t\t\t\t\tITEM STOCKS \n\n";

		view.longline();// print a long line
		cout << "\t\t\t\t\t\t\t ========================================================================================\n";
		cout << "\t\t\t\t\t\t\t | " << setw(7) << left << "Item ID" << " | " << setw(20) << left << "Name" << " | " << setw(9) << left << "Price(RM)" << " | " << setw(30) << left << "Details" << " | " << setw(6) << left << "Stocks" << " | " << endl;
		cout << "\t\t\t\t\t\t\t ========================================================================================\n";

		for (int i = 0; i < stocks.size(); i++)
		{
			if (stocks[i].itemStock < lowestStock)
				urgent = "Needs re-stocking!";
			cout << fixed << setprecision(2) << "\t\t\t\t\t\t\t | " << setw(7) << left << stocks[i].itemID << " | " << setw(20) << left << stocks[i].itemName << " | " << setw(9) << left << stocks[i].itemPrice << " | " << setw(30) << left << stocks[i].itemDetail << " | " << setw(6) << left << stocks[i].itemStock << " | " << urgent << endl;
			urgent = "";
		}
		cout << "\t\t\t\t\t\t\t ========================================================================================\n";

		cout << endl;
		view.longline();// print a long line

		cout << "Press Esc key to return \n";

		char input = '\0';
		input = _getch();
		switch (input)
		{
		case 27: //esc key. admin will return to admin page
			return;
			break;

		default:
			break;
		}

	}
}

void empRegister(staff admin)
{
	staff newEmp;
	console empRegister;
	int i = 0;

	empRegister.navigation = "> New Employee Registration\n\t\t\t\t\t\t\t\t\t\t\t\tREGISTER NEW EMPLOYEE\n";
	empRegister.choices("ID");
	empRegister.choices("Name");
	empRegister.choices("Password");
	empRegister.choices("Confirm");
	empRegister.choices("Back");

	string input;
	while (18) 
	{
		switch (empRegister.prompt()) {
		case 1:
			cout << "\nEnter employee ID (E### format where '###' represents the employee number): ";
			cin >> input;

			if (input != "")
				i++;
			if (input[0] == 'E' && input.length() == 4)
			{
				newEmp.empID = input;
				empRegister.setValue(0, newEmp.empID);
			}
			else 
			{
				cout << "\nThe username must be E### format where '###' represents the employee number";
				i--;
				_getch();
			}
			break;

		case 2:
			cout << "\nEnter employee's name(all small letter): ";
			cin >> newEmp.empName;

			if (input != "")
				i++;
			empRegister.setValue(1, newEmp.empName);
			break;

		case 3:
			cout << "\nEnter password: ";
			cin >> input;
			if (input.length() >= 6) 
			{
				newEmp.empPasswd = input;
				cout << "\nVerify password: ";
			c:
				cin >> input;
				if (input == newEmp.empPasswd)
				{
					i++;
					empRegister.setValue(2, newEmp.empPasswd);
				}
				else {
					cout << "\nThe password you entered does not match\n";
					cout.clear();
					_getch();
					cout << "\nEnter password again: ";
					goto c;
				}
			}
			else 
			{
				cout << "The password must be at least be 6 character long";
				_getch();
			}
			break;

		case 4:
			if (i >= 3) 
			{
				newEmp.addEmployee();
				cout << "\nAccount is succesfully created";
				_getch();
				return;
			}
			else 
			{
				cout << "\nThe credentials are not complete or repeated. Please try again";
				_getch();
			}
			break;

		case 5:
			return;
			break;

		default:
			break;
		}
	}
}

void empDelete(staff admin)
{
	console deletion;
	staff toDelete;
	char input = 0;
	int i = 0;

	deletion.navigation = "> Employee Deletion\n\t\t\t\t\t\t\t\t\t\t\t\tDELETE AN EMPLOYEE\n";
	deletion.choices("Employee ID");
	deletion.choices("Delete");
	deletion.choices("Back");

	while (18)
	{
		switch (deletion.prompt()) {
		case 1:
			cout << "\nEnter employee ID to be deleted: ";
			cin >> toDelete.empID;

			if (toDelete.empID != "")
				i++;
			deletion.setValue(0, toDelete.empID);
			break;

		case 2:
			cout << "Confirm deletion? : ";
			cin >> input;

			if (i >= 1)
			{
				if (input == 'y' || input == 'Y')
				{
					toDelete.delEmployee();
					cout << "Employee has been deleted.\n";
				}
				else
					break;
			}
			else
				cout << "\nNo employee ID is entered.";

			_getch();
			break;
		case 3:
			return;
			break;

		default:
			break;
		}
	}
}

void generateSalesReport(staff admin)
{
	console sales;
	string startDate, endDate, cateName="";
	stringstream show;
	vector<report> displaySales;
	double total = 0;

	sales.navigation = "> Sales Report display\n\t\t\t\t\t\t\t\t\t\t\t\tSALES REPORT ANALYSIS\n";
	sales.choices("Start Date");
	sales.choices("End Date");
	sales.choices("Confirm");
	sales.choices("Back");

	while (18)
	{

		switch (sales.prompt())
		{
		case 1:
			cout << "Enter start date in YYYY-MM-DD sequences: ";
			cin >> startDate;
			sales.setValue(0, startDate);
			break;
		case 2:
			cout << "Enter end date in YYYY-MM-DD sequences: ";
			cin >> endDate;
			sales.setValue(1, endDate);
			break;
		case 3:
			displaySales.clear();
			displaySales = report::salesReport(startDate, endDate);

			show << "\t\t\t\t\t\t\t\t\t\t =================================================" << endl;
			show << "\t\t\t\t\t\t\t\t\t\t | " << setw(20) << left << "Category" << " | " << setw(9) << left << "Item Sold" << " | " << setw(10) << "Sales(RM)" << left << " | " << endl;
			show << "\t\t\t\t\t\t\t\t\t\t =================================================" << endl;

			for (int i = 0; i < displaySales.size(); i++)
			{
				if (displaySales[i].category == 1)
					cateName = "Household Utilities";
				else if (displaySales[i].category == 2) 
					cateName = "Vegetables";
				else if (displaySales[i].category == 3) 
					cateName = "Meats & Fish";
				else if (displaySales[i].category == 4)
					cateName = "Baked Goods";
				else if (displaySales[i].category == 5)
					cateName = "Spices";

				show << fixed << setprecision(2) << "\t\t\t\t\t\t\t\t\t\t | " << setw(20) << left << cateName << " | " << setw(9) << left << displaySales[i].itemSold << " | " << setw(10) << left << displaySales[i].totPrice << " | " << endl;
				total += displaySales[i].totPrice;
			}

			show << "\t\t\t\t\t\t\t\t\t\t =================================================" << endl;
			show << fixed << setprecision(2) << endl << "\t\t\t\t\t\t\t\t\t\t   " << setw(17) << left << "Total Sales : RM " << total << endl;
			sales.askInput = show.str();
			_getch();
			show.clear();
			break;
		case 4:
			return;
			break;
		}
	}
}

void userPage(account user)
{
	console userPage;
	userPage.navigation = "> User Main Page\n\t\t\t\t\t\t\t\t\t\t\t    HELLO THERE, " + user.username + "\n\t\t\t\t\t\t\t\t\t\t\t    What's on your mind today?\n";
	userPage.choices("Check Profile");
	userPage.choices("Go Shopping");
	userPage.choices("Log Out");

	while (1)
	{
		switch (userPage.prompt())
		{
		case 1:
			system("cls");
			user = userProfile(user);
			break;
			
		case 2:
			user = userShopping(user);
			break;
		
		case 3:
			return;
			break;
		default:
			break;
		}
	}
}

account userProfile(account user)
{
	account disp = user;
	console userProfile;
	char choice = 0;

	cout << "> Profile\n\t\t\t\t\t\t\t\t\t\t\t\tMY PROFILE\n\n"; // display user's account details
	
	userProfile.longline();

	cout << setw(20) << left << "Username " << setw(2) << ": " << disp.username;
	cout << endl << setw(20) << left << "Email " << setw(2) << ": " << disp.email;
	cout << endl << setw(20) << left << "Phone Number " << setw(2) << ": " << disp.phoneNum;
	cout << endl << setw(20) << left << "Year of Birth " << setw(2) << ": " << disp.birthYear;
	cout << endl << setw(20) << left << "Home Address " << setw(2) << ": " << disp.address;
	cout << endl << endl;
	
	userProfile.longline();
	
	cout << "1>Edit \n2>Back\n\nSelect your choice\n";

	choice = _getch() - '0';

	while(69)
	{
		switch (choice)
		{
		case 1:
			goto edit; // edit profile
			break;

		case 2:
			return user; // back to user profile
			break;

		default:
			break;
		}
	}

	edit:
	
	userProfile.navigation = "> Profile > Edit\n\t\t\t\t\t\t\t\t\t\t\t\tEDIT PROFILE\n"; // where users are brought if they wish to edit their account
	string input;
	bool valid = true;

	userProfile.choices("Username");
	userProfile.choices("Email");
	userProfile.choices("Password");
	userProfile.choices("Phone Number");
	userProfile.choices("Year of Birth");
	userProfile.choices("Home Address");
	userProfile.choices("Save");
	userProfile.choices("Cancel Edit");
	userProfile.choices("Delete My Account");

	while (1) 
	{
		userProfile.setValue(0, disp.username);
		userProfile.setValue(1, disp.email);
		userProfile.setValue(2, disp.password);
		userProfile.setValue(3, disp.phoneNum);
		userProfile.setValue(4, to_string(disp.birthYear));
		userProfile.setValue(5, disp.address);
		
		switch (userProfile.prompt()) 
		{
			case 1:
				cout << "\nEnter username: ";
				cin >> disp.username;
				if (disp.username.length() <= 4) {
					cout << "The new username must be at least 4 character long";
					_getch();
				}
				else {
					userProfile.setValue(0, disp.username);
				}
				break;

			case 2:
				cout << "\nEnter email: ";
				cin >> disp.email;
				userProfile.setValue(1, disp.email);
				break;

			case 3:
				cout << "\nEnter password: ";
				cin >> input;
				if (input.length() < 6) {
					cout << "The password must be at least be 6 character long";
					_getch();
				}
				else {
					disp.password = input;
				c:
					cout << "\nVerify password: ";
					cin >> input;
					if (input == disp.password) {
						userProfile.setValue(2, disp.password);
					}
					else {
						cout << "The password you entered does not match\n";
						goto c;
					}
				}
				break;

			case 4:
				cout << "\nEnter phone number: ";
				cin >> disp.phoneNum;

				userProfile.setValue(3, disp.phoneNum);
				break;

			case 5:
				cout << "\nEnter year of birth: ";
				cin >> input;

				if (checkNumeric(input) && input.length() == 4) {

					disp.birthYear = stoi(input);

					userProfile.setValue(4, to_string(disp.birthYear));
				}
				else {
					cout << "Year of birth must be only 4 digits";
					_getch();
				}
				break;

			case 6:
				cout << "\nEnter home address: ";
				cin >> disp.address;

				userProfile.setValue(5, disp.address);
				break;

			case 7:
				user = disp;
				user.userUpdate();
				cout << "Your account has been updated";
				_getch();

			case 8:
				disp = user;
				return user;
				break;

			case 9:
				char confirm;
				cout << "Your account will be deleted. Are you sure? (y/n)\n";

				confirm = _getch();
				if (confirm == 'Y' || confirm == 'y') {
					user = disp;
					user.userRemove();
					system("pause");
					main();
				}

			default:
				break;
		}
	}
}

account userShopping(account user)
{
	purchase shoppingCart;
	shoppingCart.userID = user.userID;
	console shop;
	string cateName;
	string totPrice;
	int browse[5]{};

	shop.choices("Household Utilities");
	shop.choices("Vegetables");
	shop.choices("Meats & Fish");
	shop.choices("Baked Goods");
	shop.choices("Spices");
	shop.choices("View Shopping Cart");
	shop.choices("Back");

	while (1)
	{
		totPrice = to_string(shoppingCart.totalPrice()); // take total price and turn it into string
		shop.navigation = "> Shopping\n\n\t\t\t\t\t\t\t\t\t\t\t\t     SHOPPING PAGE" 
			"\n\t\t\t\t\t\t\t\t\t\t\t    Select from a variety of goods!\nItem(s) selected: " 
			+ to_string(shoppingCart.countItem()) + "\nTotal Price: RM" + totPrice.erase(totPrice.size() - 4);
																		//erase unwanted decimals(similar to fixed precision)
		switch (shop.prompt())
		{
		case 1:
			cateName = "Household Utilities";
			shoppingCart = browseItems(user, 1, cateName, shoppingCart);
			break;
		case 2:
			cateName = "Vegetables";
			shoppingCart = browseItems(user, 2, cateName, shoppingCart);
			break;
		case 3:
			cateName = "Meats & Fish";
			shoppingCart = browseItems(user, 3, cateName, shoppingCart);
			break;
		case 4:
			cateName = "Baked Goods";
			shoppingCart = browseItems(user, 4, cateName, shoppingCart);
			break;
		case 5:
			cateName = "Spices";
			shoppingCart = browseItems(user, 5, cateName, shoppingCart);
			break;
		case 6:
			shoppingCart =viewCart(user, shoppingCart);
			break;
		case 7:
			return user;
			break;
		}
	}
}
 
purchase browseItems(account user, int category, string &cateName, purchase shoppingCart)
{
	console p;
	vector<item> browse;
	item selectedItem;

	// these two lines act as parameters to be passed to different functions
	int qty; // add item and quantities in shopping cart
	string itemID;
	int recentStock=0; // update quantity of items shown once user add it into their cart
	string id;

	while (1) 
	{	
		system("cls");

		browse = item::displayCategory(category); //search for category in database based on user's choice

		p.navigation = "> " + cateName +" section\n\t\t\t\t\t\t\t\t\tSee something you like? Enter its ID to add into your cart! \n\n"; //cateName = category name based on user's choice
		cout << p.navigation; //shows what category user chose and other text

		p.longline();// print a long line
		cout << "\t\t\t\t\t\t\t ========================================================================================\n";
		cout << "\t\t\t\t\t\t\t | " << setw(7) << left << "Item ID" << " | " << setw(20) << left << "Name" << " | " << setw(9) << left << "Price(RM)" << " | " << setw(30) << left << "Details" << " | " << setw(6) << left << "Stocks" << " | " << endl;
		cout << "\t\t\t\t\t\t\t ========================================================================================\n";

		for (int i = 0; i < browse.size(); i++)
		{
			cout << fixed << setprecision(2) << "\t\t\t\t\t\t\t | " << setw(7) << left << browse[i].itemID << " | " << setw(20) << left << browse[i].itemName << " | " << setw(9) << left << browse[i].itemPrice << " | " << setw(30) << left << browse[i].itemDetail << " | " << setw(6) << left << browse[i].itemStock << " | " << endl;
		}
		cout << "\t\t\t\t\t\t\t ========================================================================================\n";
	
		cout << endl;
		p.longline();// print a long line

		cout << "Press A key to add item. Press Esc key to return \n";

		char input = '\0';
		input = _getch();
		switch (input)
		{
		case 27: //esc key. user will return to shopping page
			return shoppingCart;
			break;

		case 97: //A key. indicating "add" if user wants to add item into their cart
			cout << "Enter item ID to add: ";
			cin >> itemID;
			selectedItem = item::searchItem(itemID);

			if (selectedItem.itemCategory == category)
			{
				if (selectedItem.itemStock != 0)
				{
					cout << "Enter quantity: ";
					cin >> qty;

					if (qty > 0 && qty <= selectedItem.itemStock)
					{
						shoppingCart.addItem(selectedItem, qty);

						recentStock = selectedItem.itemStock - qty; // update recent stock after user add item into cart
						id = itemID;
						shoppingCart.updateStock(id, recentStock); 

						cout << "Item has been added to your cart.\n";
					}
					else
						cout << "Please enter a valid input.\n";
				}
				else
					cout << "Item is out of stock.";
			}
			else
				cout << "Please enter a valid input.\n";
				
			_getch();
			break;

		default:
			break;
		}
		
	}

}

purchase viewCart(account user, purchase shoppingCart)
{
	console view;
	view.navigation = "> Your Shopping Cart\n";
	item update;
	stringstream store;
	vector<item> items;
	
	view.choices("Confirm Pruchase");
	view.choices("Empty Shopping Cart");
	view.choices("Back");

	store << " =======================================================================================================\n"; //line
	store << " | " << setw(7) << left << "Item ID" << " | " << setw(20) << left << "Items" << " | " << setw(20) << left << "Price(RM)" << " | " <<
	setw(20) << left << "Quantity" << " | " << setw(20) << left << "Subtotal(RM)" << " | " << endl ;
	store << " =======================================================================================================\n";

	for (int i = 0; i < shoppingCart.items.size(); i++) //display all the items that are purchased
	{
		store << fixed << setprecision(2) << " | " << setw(7) << left << shoppingCart.items[i].first.itemID << " | " << setw(20) << left << shoppingCart.items[i].first.itemName 
			<< " | " << setw(20) << left << shoppingCart.items[i].first.itemPrice << " | " << setw(20) << left << shoppingCart.items[i].second << " | " 
			<< setw(20) << left << (shoppingCart.items[i].first.itemPrice * shoppingCart.items[i].second) << " | " << endl;
	}
	store << " =======================================================================================================\n";
	store << " | " <<setw(7) << left << "TOTAL: " << " | " << setw(3) << left << "RM " << setw(86) << left << shoppingCart.totalPrice() << " | " << endl << endl;;
	
	view.askInput = "Purchase summary: \n" + store.str() + "\n\nSelect your option"; // reuse the askInput function to print purchase summary
	view.askInput;
	
	char input, retry = 0;
	double amount=0, balance;
	int attempt = 0;
	while (1)
	{
		switch (view.prompt())
		{
		case 1:
			if (!shoppingCart.items.empty())
			{
				cout << "Done with your purchase? (Y/N): ";
				input = _getch();
				if (input == 'Y' || input == 'y')
				{
					do
					{
						attempt++;
						cout << "\nEnter amount to pay : RM ";
						cin >> amount;

						if (amount >= shoppingCart.totalPrice())
						{
							balance = amount - shoppingCart.totalPrice();
							shoppingCart.insertItem();
							cout << "Balance : RM " << balance << endl;
							cout << "\n\n==================================================================================";
							cout << "\n Your purchase has been finalized. Your order will be packed and delivered to : \n" << user.address;
							cout << "\n==================================================================================\n\n";
							retry = 'n';
							goto success;
						}
						else
						{
							cout << "\nAmount is invalid or insufficient.";

							if (attempt == 3)
							{
								cout << "\nToo much unsuccesful attempts. Cancelling payment.";

								for (int i = 0; i < shoppingCart.items.size(); i++) //restore the prior item stocks
								{
									string id = shoppingCart.items[i].first.itemID;
									update = item::searchItem(id);
									int recentStock = update.itemStock + shoppingCart.items[i].second;
									shoppingCart.updateStock(id, recentStock);
								}
								_getch();
							}
						}
						cout << "\nDo you wish to continue? (Y/N): ";
						retry = _getch();

					} while (retry == 'y' || retry == 'Y');
				success:
					cout << "Redirecting you back to the Shopping Page.\n";
					system("pause");
					userShopping(user); //return to shopping page with empty cart
					break;
				}
				else
					break;
			}
			else
			{
				cout << "Cannot check out with an empty cart.";
				_getch();
			}
			break;

		case 2:
			cout << "Your cart will be emptied and you'll be redirected to the shopping page (Y/N): ";
			cin >> input;
			if (input == 'Y' || input == 'y')
			{
				for (int i = 0; i < shoppingCart.items.size(); i++) //restore the prior item stocks
				{
					string id = shoppingCart.items[i].first.itemID;
					update = item::searchItem(id);
					int recentStock = update.itemStock + shoppingCart.items[i].second;
					shoppingCart.updateStock(id, recentStock);
				}
				userShopping(user); //return back to shopping page
			}
			break;

		case 3:
			return shoppingCart;
		}
	}
}

bool checkNumeric(string input)
{
	for (int i = 0; i < input.length(); i++) {
		// loop through the string and if the character at index is not digit return false
		if (!isdigit(input.at(i))) {
			return false;
		}
	}
	// if loop finishes means all is digit so return true
	return true;
}

string loginPassword(string back)
{
	string pw = "";
	char input = '\0';
	while (1)
	{
		input = _getch();
		switch (input)
		{
		case 13://enter key(ascii code)
			return pw;
			break;
		case 27://esc key(ascii code)
			return back;
			break;
		case 8://backspace key
			if (pw.length() > 0)
			{
				pw.erase(pw.size() - 1);
				cout << "\b \b";
			}
			break;
		default://all keys including alphabets, numbers and special symbol(except space)
			if (input > 32 && input <= 126)
			{
				pw += input;
				cout << "*"; // desplay * instead of the input
				break;
			}
		}
	}
}
