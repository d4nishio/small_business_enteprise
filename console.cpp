#include "console.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

console::console() 
{
	navigation = "";					//Shows what page user is currently in.
	askInput = "Select your option";	//Ask user to enter their choice.
	bullet = ">";						//Bullet point.
}

int console::prompt() 
{
	int selected = -1;
	do
	{
		system("cls");					// clear console
		cout << navigation << endl;		// print out the respective page

		longline();

		for (int i = 0; i < options.size(); i++) //loop trhough each option 
		{
			cout << setw(1) << left << i + 1 << setw(1) << left << bullet << setw(20) << left << options[i].first;// put bullet ">" to each option, set all to left side. eg:1>Register
			if (options[i].second != "") {
				cout << setw(1) << right << " : " << setw(180) << left << options[i].second;
			}
			cout << endl;
		}
		cout << endl;

		longline();

		cout << askInput << endl;		// print out "Select your option"

		selected = _getch() - '0';
	} while (selected < 1 || selected > options.size());
	return selected;
}

void console::choices(string option) 
{
	options.push_back({ option,"" });
}

void console::setValue(int index, string value) 
{
	if (index >= 0 && index < options.size()) 
	{
		options[index].second = value;
	}
}

void console::longline()
{
	for (int i = 0; i < 211; i++)
	{
		cout << "=";				//print long line
	}
	cout << endl << endl;
}

console::~console() 
{
	options.clear();
}