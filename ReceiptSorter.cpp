/*=====================================================================
                      Kimmy Huynh
            https://github.com/kimmyhuynh
              7kimmy.huynh@gmail.com
              CSE2ALG, Summer 1 2016
 ======================================================================
*/
#include "ReceiptSorter.h"

int main() {
   CRVEC records;
	int choice = -1;
	bool receiptSort = false;
    string sampleSize = loadData(records);
    if(sampleSize.length() == 0) {
       return -1;
    }
	while(choice != static_cast<int>(TOP_SORT::EXIT)) {
        displayAlgorithmMainMenu();
        cout << "Enter choice >> ";
        cin >> choice;
        cin.ignore(100000, '\n');
        processChoice(choice, records, receiptSort, sampleSize);
	}
}
string loadData(CRVEC& records) {
	ifstream fin;
   string filename = "sample4194304_input.txt";
	fin.open(filename);
   string sampleSize = "";
   if(fin.fail()) {
      std::cerr << "\nUnable to open input file, program closing" << endl;
      return sampleSize;
   }
   string::size_type firstDigit = filename.find_first_not_of("sample");
   string::size_type lastDigit = filename.find("_");
   sampleSize = filename.substr(firstDigit, (lastDigit - firstDigit));
	string temp;
	while(getline(fin, temp)) {
      records.emplace_back(temp);
	}
	fin.close();
   return sampleSize;
}
void writeData(ofstream& fout, const CRVEC& records) {
      if(fout.is_open()) {
		   for(auto custRecord : records) {
			    fout << custRecord << endl;
		   }
		   fout.close();
      }
}
void displayAlgorithmMainMenu() {
	cout << "1. Sort by receipt and output to a text file" << endl;
	cout << "2. Sort by customer number while maintaining receipt number " <<
	        "and output to a text file" << endl;
	cout << "3. Exit program" << endl;
}
void processChoice(int choice, CRVEC& records, bool& receiptSort,
                   const string& sampleSize) {
	if(choice == static_cast<int>(TOP_SORT::CUST_SORT) && !receiptSort) {
		cout << "Must select an algorithm from main menu 1 first" << endl;
		return;
	}
	if(choice == static_cast<int>(TOP_SORT::RECEIPT_SORT)) {
		receiptSort = true;
		runReceiptAlgorithm(records, sampleSize);
	} else if(choice == static_cast<int>(TOP_SORT::CUST_SORT)) {
		runCustomerAlgorithm(records, sampleSize);
	} else if(choice == static_cast<int>(TOP_SORT::EXIT)) {

	} else {
		cerr << "Invalid main menu choice" << endl;
	}	
}
void displayAlgorithmMenu() {
	cout << "1. Bubble Sort" << endl;
	cout << "2. Quick Sort" << endl;
	cout << "3. Merge Sort" << endl;
	cout << "4. STL Sort" << endl;
	cout << "5. Return to main menu" << endl;
}
void runReceiptAlgorithm(CRVEC& records, const string& sampleSize) {
	int choice = -1;
	while(choice != static_cast<int>(RN_SORT::RECALGEXIT)) {
		displayAlgorithmMenu();
		cout << "Enter choice >> ";
		cin >> choice;
		cin.ignore(100000, '\n');
		processReceiptChoice(choice, records, sampleSize);
	}
}
void processReceiptChoice(int choice, CRVEC& records, const string& sampleSize) {
	switch(choice) {
		case static_cast<int>(RN_SORT::RECALG1):
			receiptBubbleSort(records, sampleSize);
			break;
		case static_cast<int>(RN_SORT::RECALG2):
			receiptQuickSort(records, sampleSize);
			break;	
		case static_cast<int>(RN_SORT::RECALG3):
			receiptMergeSort(records, sampleSize);
			break;
		case static_cast<int>(RN_SORT::RECALG4):
			receiptSTLSort(records, sampleSize);
			break;
		case static_cast<int>(RN_SORT::RECALGEXIT):
			break;		
		default:
			cout << "Invalid receipt number sort menu choice" << endl;
			break;		
	}
}
void receiptBubbleSort(CRVEC& records, const string& sampleSize) {
	ofstream fout;
   openOutputFile(fout);
   std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
   startTime = std::chrono::steady_clock::now();
   bubbleSortReceipt(records);
   endTime = std::chrono::steady_clock::now();
   cout << "\nRunning Bubble sort receipt with sample size " << sampleSize << endl;
   cout << "\nTime with steady clock: " << std::fixed << setprecision(10) << std::chrono::duration<double>(endTime - startTime).count() << " seconds" << endl;
   cout << "\nNumber of comparisons: " << CustomerRecord::getComparisons() << endl << endl;
   CustomerRecord c;
   c.resetComparisons();
   cout << "Number of swaps: " << CustomerRecord::getNoOfSwaps() << endl << endl;
   c.resetSwaps();
   writeData(fout, records);
}
void receiptQuickSort(CRVEC& records, const string& sampleSize) {
	ofstream fout;
   openOutputFile(fout);
   std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
   startTime = std::chrono::steady_clock::now();
   quickSortReceipt(records, 0, records.size() - 1);
   endTime = std::chrono::steady_clock::now();
   cout << "\nRunning Quick Sort receipt with sample size " << sampleSize << endl;
   cout << "\nTime with steady clock: " << std::fixed << setprecision(10) << std::chrono::duration<double>(endTime - startTime).count() << " seconds" << endl;
   cout << "\nNumber of comparisons: " << CustomerRecord::getComparisons() << endl << endl;
   CustomerRecord c;
   c.resetComparisons();
   cout << "Number of swaps: " << CustomerRecord::getNoOfSwaps() << endl << endl;
   c.resetSwaps();
   writeData(fout, records);
}
void receiptMergeSort(CRVEC& records, const string& sampleSize) {
	ofstream fout;
   openOutputFile(fout);
   CRVEC temp(records.size());
   std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
   startTime = std::chrono::steady_clock::now();
   mergeSortReceipt(records, 0, records.size() - 1, temp);
   endTime = std::chrono::steady_clock::now();
   cout << "\nRunning Merge Sort receipt with sample size " << sampleSize << endl;
   cout << "\nTime with steady clock: " << std::fixed << setprecision(10) << std::chrono::duration<double>(endTime - startTime).count() << " seconds" << endl;
   cout << "\nNumber of comparisons: " << CustomerRecord::getComparisons() << endl << endl;
   CustomerRecord c;
   c.resetComparisons();
   cout << "Number of swaps: " << CustomerRecord::getNoOfSwaps() << endl << endl;
   c.resetSwaps();
   writeData(fout, records);
}
void receiptSTLSort(CRVEC& records, const string& sampleSize) {
	ofstream fout;
   openOutputFile(fout);
   std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
   startTime = std::chrono::steady_clock::now();
   sortReceipt sr;
   sort(records.begin(), records.end(), sr);
   endTime = std::chrono::steady_clock::now();
   cout << "\nRunning STL Sort receipt with sample size " << sampleSize << endl;
   cout << "\nTime with steady clock: " << std::fixed << setprecision(10) << std::chrono::duration<double>(endTime - startTime).count() << " seconds" << endl;
   cout << "\nNumber of comparisons: " << sortReceipt::getComparisons() << endl << endl;
   CustomerRecord c;
   sr.resetComparisons();
   cout << "Number of swaps: " << CustomerRecord::getNoOfSwaps() << endl << endl;
   c.resetSwaps();
   writeData(fout,records);
}
void runCustomerAlgorithm(CRVEC& records, const string& sampleSize) {
	int choice = -1;
	while(choice != static_cast<int>(CN_SORT::CUSTALGEXIT)) {
		displayAlgorithmMenu();
		cout << "Enter choice >> ";
		cin >> choice;
		cin.ignore(100000, '\n');
		processCustomerChoice(choice, records, sampleSize);
	}
}
void processCustomerChoice(int choice, CRVEC& records, const string& sampleSize) {
	switch(choice) {
		case static_cast<int>(CN_SORT::CUSTALG1):
			customerBubbleSort(records, sampleSize);
			break;
		case static_cast<int>(CN_SORT::CUSTALG2):
			customerQuickSort(records, sampleSize);
			break;	
		case static_cast<int>(CN_SORT::CUSTALG3):
			customerMergeSort(records, sampleSize);
			break;
		case static_cast<int>(CN_SORT::CUSTALG4):
			customerSTLSort(records, sampleSize);
			break;
		case static_cast<int>(CN_SORT::CUSTALGEXIT):
			break;		
		default:
			cout << "Invalid customer record sort menu choice" << endl;
			break;		
	}
}
void customerBubbleSort(CRVEC& records, const string& sampleSize) {
	ofstream fout;
   openOutputFile(fout);
   std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
   startTime = std::chrono::steady_clock::now();
   bubbleSortCustomer(records);
   endTime = std::chrono::steady_clock::now();
   cout << "\nRunning Bubble sort customer with sample size " << sampleSize << endl;
   cout << "\nTime with steady clock: " << std::fixed << setprecision(10) << std::chrono::duration<double>(endTime - startTime).count() << " seconds" << endl;
   cout << "\nNumber of comparisons: " << CustomerRecord::getComparisons() << endl << endl;
   CustomerRecord c;
   c.resetComparisons();
   cout << "Number of swaps: " << CustomerRecord::getNoOfSwaps() << endl << endl;
   c.resetSwaps();
   writeData(fout, records);
}
void customerQuickSort(CRVEC& records, const string& sampleSize) {
	ofstream fout;
   openOutputFile(fout);
   std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
   startTime = std::chrono::steady_clock::now();
   quickSortCustomer(records, 0, records.size() - 1);
   endTime = std::chrono::steady_clock::now();
   cout << "\nRunning Quick Sort customer with sample size " << sampleSize << endl;
   cout << "\nTime with steady clock: " << std::fixed << setprecision(10) << std::chrono::duration<double>(endTime - startTime).count() << " seconds" << endl;
   cout << "\nNumber of comparisons: " << CustomerRecord::getComparisons() << endl << endl;
   CustomerRecord c;
   c.resetComparisons();
   cout << "Number of swaps: " << CustomerRecord::getNoOfSwaps() << endl << endl;
   c.resetSwaps();
   writeData(fout, records);
}
void customerMergeSort(CRVEC& records, const string& sampleSize) {
	ofstream fout;
   openOutputFile(fout);
   std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
   startTime = std::chrono::steady_clock::now();
   CRVEC temp(records.size());
   mergeSortCustomer(records, 0, records.size() - 1, temp);
   endTime = std::chrono::steady_clock::now();
   cout << "\nRunning Merge Sort customer with sample size " << sampleSize << endl;
   cout << "\nTime with steady clock: " << std::fixed << setprecision(10) << std::chrono::duration<double>(endTime - startTime).count() << " seconds" << endl;
   cout << "\nNumber of comparisons: " << CustomerRecord::getComparisons() << endl << endl;
   CustomerRecord c;
   c.resetComparisons();
   cout << "Number of swaps: " << CustomerRecord::getNoOfSwaps() << endl << endl;
   c.resetSwaps();
   writeData(fout, records);
}
void customerSTLSort(CRVEC& records, const string& sampleSize) {
	ofstream fout;
   openOutputFile(fout);
   std::chrono::time_point<std::chrono::steady_clock> startTime, endTime;
   startTime = std::chrono::steady_clock::now();
   sortCustomer sc;
   sort(records.begin(), records.end(), sc);
   endTime = std::chrono::steady_clock::now();
   cout << "\nRunning STL Sort customer with sample size " << sampleSize << endl;
   cout << "\nTime with steady clock: " << std::fixed << setprecision(10) << std::chrono::duration<double>(endTime - startTime).count() << " seconds" << endl;
      cout << "\nNumber of comparisons: " << sortCustomer::getComparisons() << endl << endl;
    CustomerRecord c;
    sc.resetComparisons();
    cout << "Number of swaps: " << CustomerRecord::getNoOfSwaps() << endl << endl;
    c.resetSwaps();
    writeData(fout, records);
}
void openOutputFile(ofstream& fout) {
	cout << "Please enter an output file name and press enter >> ";
	string filename;
	getline(cin, filename);
	fout.open(filename.c_str());
	if(fout.fail()) {
		cerr << "Cannot open output file" << endl;
		}
}
