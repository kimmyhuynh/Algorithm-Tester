/*=====================================================================
								Kimmy Huynh
						https://github.com/kimmyhuynh
							7kimmy.huynh@gmail.com
							CSE2ALG, Summer 1 2016
 ======================================================================
*/
#include "CustomerRecord.h"

unsigned long CustomerRecord::noOfComparisons = 0;
unsigned long CustomerRecord::noOfSwaps = 0;

CustomerRecord::CustomerRecord(const string& line) {
	stringstream ss(line);
	string token;
	int count = 0;

	while(std::getline(ss, token, ',')) {
		if(count == 0) {
			receipt = stoi(token);
		} else if(count == 1) {
			customerNumber = stoi(token);
		} else {
			price = token;
		}
		++count;
	}
}
CustomerRecord& CustomerRecord::operator = (const CustomerRecord& cr) {
    ++noOfSwaps;
    receipt = cr.receipt;
    customerNumber = cr.customerNumber;
    price = cr.price;

    return *this;
}
bool CustomerRecord::customerGreater(const CustomerRecord& cr) {
   ++noOfComparisons;
	if(customerNumber > cr.customerNumber) {
		return true;
	} else if(customerNumber == cr.customerNumber) {
		return receipt > cr.receipt;
	}
	return false;
}
bool CustomerRecord::receiptGreater(const CustomerRecord& cr) {
   ++noOfComparisons;
	return receipt > cr.receipt;
}
