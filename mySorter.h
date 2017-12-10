/*=====================================================================
								Kimmy Huynh
						https://github.com/kimmyhuynh
							7kimmy.huynh@gmail.com
							CSE2ALG, Summer 1 2016
 ======================================================================
*/
#ifndef MYSORTER_H
#define MYSORTER_H
#include <vector>
using std::vector;
#include "CustomerRecord.h"

void swap(vector<CustomerRecord>& records, int i, int j) {
	CustomerRecord temp = records[i];
	records[i] = records[j];
	records[j] = temp;
}
void bubbleSortCustomer(vector<CustomerRecord>& records) {
	bool swapped = true;
	for(int i = 0; i < records.size() && swapped; ++i) {
		swapped = false;
		for(int j = 0; j < records.size() - 1 - i; ++j) {
			if(records[j].customerGreater(records[j + 1])) {
				swap(records, j + 1, j);
				swapped = true;
			}
		}
	}
}
void bubbleSortReceipt(vector<CustomerRecord>& records) {
	bool swapped = true;
	for(int i = 0; i < records.size() && swapped; ++i) {
		swapped = false;
		for(int j = 0; j < records.size() - 1 - i; ++j) {
			if(records[j].receiptGreater(records[j + 1])) {
				swap(records, j + 1, j);
				swapped = true;
			}
		}
	}
}
void selectionSortCustomer(vector<CustomerRecord>& records) {
	for(int i = 0; i < records.size() - 1; ++i) {
		int maxIndex = 0, j = 0;
		for(j = 0; j < records.size() - 1 - i; ++j) {
			if(records[j].customerGreater(records[maxIndex])) {
				maxIndex = j;
			}
		}
		swap(records, maxIndex, j);
	}
}
void selectionSortReceipt(vector<CustomerRecord>& records) {
	for(int i = 0; i < records.size() - 1; ++i) {
		int maxIndex = 0, j = 0;
		for(j = 0; j < records.size() - 1 - i; ++j) {
			if(records[j].receiptGreater((records[maxIndex]))) {
				maxIndex = j;
			}
		}
		swap(records, maxIndex, j);
	}
}
void insertionSortCustomer(vector<CustomerRecord>& records) {
	for(int i = 1; i < records.size(); ++i) {
		for(int j = i; j > 0 && records[j - 1].customerGreater(records[j]); --j) {
			swap(records, j - 1, j);
		}
	}
}
void insertionSortReceipt( vector<CustomerRecord>& records) {
	for(int i = 1; i < records.size(); ++i) {
		for(int j = i; j > 0 && records[j - 1].receiptGreater(records[j]); --j) {
			swap(records, j - 1, j);
		}
	}
}
int Median3(vector<CustomerRecord>& records, int low, int high) {
   int mid = (low + high) / 2;
   CustomerRecord pivot = records[mid];
   swap(records, mid, high);

   while(low < high ) {
      while(low < high && !records[low].receiptGreater(pivot)) {
            ++low;
      }
      if(low < high) {
         swap(records, low, high);
         --high;
      }
      while(high > low && records[high].receiptGreater(pivot)) {
         --high;
      }
      if(high > low) {
         swap(records, low, high);
         ++low;
      }
   }
   return low;
}
int Median3Customer(vector<CustomerRecord>& records, int low, int high) {
   int mid = (low + high) / 2;
   CustomerRecord pivot = records[mid];
   swap(records, mid, high);

   while(low < high ) {
      while(low < high && !records[low].customerGreater(pivot)) {
            ++low;
      }
      if(low < high) {
         swap(records, low, high);
         --high;
      }
      while(high > low && records[high].customerGreater(pivot)) {
         --high;
      }
      if(high > low) {
         swap(records, low, high);
         ++low;
      }
   }
   return low;
}
void quickSortCustomer(vector<CustomerRecord>& records, int low, int high) {
   if(low >= high) {
      return;
   }
   int pivot = Median3Customer(records, low, high);
   quickSortCustomer(records, low, pivot - 1);
   quickSortCustomer(records, pivot + 1, high);
   
}
void quickSortReceipt(vector<CustomerRecord>& records, int low, int high) {
   if(low >= high) {
      return;
   }
   int pivot = Median3(records, low, high);
   quickSortReceipt(records, low, pivot - 1);
   quickSortReceipt(records, pivot + 1, high);
}
void mergeCustomer(vector<CustomerRecord>& records, int low, int middle, int high, vector<CustomerRecord>& temp) {
	for(int i = low; i <= high; ++i) {
		temp[i] = records[i];
	}
	int i = low;
	int j = middle + 1;
	int k = low;

	while(i <= middle && j <= high) {
		if(!temp[i].customerGreater(temp[j])) {
			records[k] = temp[i];
			++i;
		} else {
			records[k] = temp[j];
			++j;
		}
		++k;
	}
	while(i <= middle) {
		records[k] = temp[i];
		++k;
		++i;
	}
}
void mergeSortCustomer(vector<CustomerRecord>& records, int low, int high,
     vector<CustomerRecord>& temp) {
	if(low < high) {
		int middle = (low + high) / 2;
		mergeSortCustomer(records, low, middle, temp);
		mergeSortCustomer(records, middle + 1, high, temp);
		mergeCustomer(records, low, middle, high, temp);
	}
}
void mergeSortReceipt(vector<CustomerRecord>& records, int low, int middle, int high, vector<CustomerRecord>& temp) {
	for(int i = low; i <= high; ++i) {
		temp[i] = records[i];
	}
	int i = low;
	int j = middle + 1;
	int k = low;

	while(i <= middle && j <= high) {
		if(!temp[i].receiptGreater(temp[j])) {
			records[k] = temp[i];
			++i;
		} else {
			records[k] = temp[j];
			++j;
		}
		++k;
	}
	while(i <= middle) {
		records[k] = temp[i];
		++k;
		++i;
	}
}
void mergeSortReceipt(vector<CustomerRecord>& records, int low, int high,
     vector<CustomerRecord>& temp) {
	if(low < high) {
		int middle = (low + high) / 2;
		mergeSortReceipt(records, low, middle, temp);
		mergeSortReceipt(records, middle + 1, high, temp);
		mergeSortReceipt(records, low, middle, high, temp);
	}
}
#endif
