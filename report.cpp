#include "report.h"
using namespace std;
using namespace sql;

report::report(ResultSet* data) {
	date = data->getString("date");
	category = data->getInt("category");
	totPrice = data->getDouble("sales");
	itemSold = data->getInt("itemSold");
}


vector<report> report::salesReport(string startDate, string endDate) 
{
	/*
		SELECT p.date AS date, i.itemCategory AS category, SUM(i.itemCategory) as itemSold, SUM(ip.quantity * i.itemPrice) AS sales
		FROM purchase p
		JOIN item_purchase ip ON p.purchaseID = ip.purchaseID
		JOIN item i ON ip.itemID = i.itemID
		WHERE p.date >= ? AND p.date <= ?
		GROUP BY category
	*/

	// query to calculate sales by category and calculate item sold by respective categories
	string query = " SELECT p.date as date, i.itemCategory AS category, SUM(i.itemCategory) as itemSold, SUM(ip.quantity * i.itemPrice) AS sales"
		" FROM purchase p "
		" JOIN item_purchase ip ON p.purchaseID = ip.purchaseID "
		" JOIN item i ON ip.itemID = i.itemID "
		" WHERE p.date >= ? AND p.date <= ? "
		" GROUP BY category";

	// declare vector > execute query > return result in vector 
	vector <report> showSales;

	DBConnection db;

	db.prepareStatement(query);
	db.stmt->setString(1, startDate);
	db.stmt->setString(2, endDate);
	db.QueryResult();


	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			report tmpSale(db.res);
			showSales.push_back(tmpSale);

		}
	}

	db.~DBConnection();
	return showSales;
}
