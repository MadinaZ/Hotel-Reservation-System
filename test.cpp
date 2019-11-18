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


struct RoomInfo
{
	int endDate;
	int customerNum;
};

struct Rooms
{
	int startDate;
	int userNum;
	string note;
};

struct RoomTypes
{
	string name;
	double price;
	int  cap;
	bool alloccupied;
	DynamicArray<Rooms> roomList;
	PriorityQueue<RoomInfo> roomStatus;
	bool operator<(const RoomInfo& a, const RoomInfo& b)
	{
		return (a.endDate < b.endDate);
	}
};


struct Hotel
{
	string name;
	string city;
	int star;
	double rate;
	double min_price(int);
	PriorityQueue<RoomTypes> roomTypes;
	bool operator<(const RoomTypes& a, const RoomTypes& b)
	{
		return (a.cap > b.cap);
	}
};

double Hotel::min_price(int num_ppl)
{
	while(roomTypes.cap < num_ppl)
		roomTypes.pop();
	return roomTypes.top().price;
}



int main()
{













	return 0;
}
