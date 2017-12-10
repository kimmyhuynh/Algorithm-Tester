/*=====================================================================
								Kimmy Huynh
						https://github.com/kimmyhuynh
							7kimmy.huynh@gmail.com
							CSE2ALG, Summer 1 2016
 ======================================================================
*/
#ifndef CUSTOMER_RECORD_H
#define CUSTOMER_RECORD_H

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

#include <fstream>
using std::ofstream;

#include <string>
using std::string;
using std::stoi;

#include <sstream> 
using std::stringstream;

class CustomerRecord {
public:
	CustomerRecord() = default;
	CustomerRecord(const string& line);

	int getReceipt() const { return receipt; }
	int getCustomerNumber() const { return customerNumber; }
	const string getPrice() const { return price; }
	bool customerGreater(const CustomerRecord& cr);
	bool receiptGreater(const CustomerRecord& cr);
	friend ofstream& operator << (ofstream& os, const CustomerRecord& cr) {
		os << cr.receipt << "," << cr.customerNumber << "," << cr.price;
		return os;
	}

   CustomerRecord& operator = (const CustomerRecord& cr);

   static void resetComparisons() { noOfComparisons = 0; }
   static unsigned long getComparisons() { return noOfComparisons; }
   static void resetSwaps() { noOfSwaps = 0; }
   static unsigned long getNoOfSwaps() { return noOfSwaps; }
private:
	int receipt = 0;
	int customerNumber = 0;
	string price = "";
   static unsigned long noOfComparisons;
   static unsigned long noOfSwaps;
};
#endif
