#pragma once
#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include "DBConnection.h"

class report
{
public:
	std::string date;
	double totPrice;
	int category, itemSold;

	report(sql::ResultSet* data);

	static std::vector<report> salesReport(std::string startDate, std::string endDate);

	~report() 
	{

	};
};


#endif

