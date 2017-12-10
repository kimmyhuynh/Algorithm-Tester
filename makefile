# makefile for ALG Assignment A

CC = g++
LIBS = -g

algA:CustomerRecord.o ReceiptSorter.o sortReceipt.o sortCustomer.o
	$(CC) $(LIBS) -o algA CustomerRecord.o ReceiptSorter.o sortReceipt.o sortCustomer.o -std=c++11

CustomerRecord.o:CustomerRecord.cpp 
	$(CC) $(LIBS) -c CustomerRecord.cpp -std=c++11
	
ReceiptSorter.o:ReceiptSorter.cpp
	$(CC) $(LIBS) -c ReceiptSorter.cpp -std=c++11
	
sortReceipt.o: sortReceipt.cpp
	$(CC) $(LIBS) -c sortReceipt.cpp -std=c++11

sortCustomer.o: sortCustomer.cpp
	$(CC) $(LIBS) -c sortCustomer.cpp -std=c++11

all:algA clean
clean:
	rm *.o			
