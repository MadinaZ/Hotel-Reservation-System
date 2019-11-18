#include "AssociativeArray.h"
#include "DynamicArray.h"
#include "StaticArray.h"
#include "Queue.h"
#include "PriorityQueue.h"


#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

#include <cmath>



struct Rooms
{
	int startDate;
	int userNum;
	string note;
};

struct Roomtypes
{
	double price;
	int cap;
	bool alloccupied;
	DynamicArray<Rooms> roomList;
};

struct Roomstatus
{
	int endDate;
	int customerNum;
};

class Hotel
{
	string name;
	string city;
	int star;
	double rate;
	double min_price();
	StaticArray<Roomtypes, 5> roomtypes;
};

double Hotel::min_price()
{
	return 0.2;
}



int main()
{
	PriorityQueue<Roomstatus> roomSta;












	return 0;
}
