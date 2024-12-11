#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>
#include <utility>
class console
{
	public:
		std::string navigation, askInput, bullet;
		console();
		void choices(std::string option);
		void setValue(int index, std::string value);
		int prompt();
		void longline();
		~console();
	private:
		std::vector<std::pair<std::string, std::string>> options;
		// [ {"1","2"}  ,{"1","2"}  ]

};

#endif
