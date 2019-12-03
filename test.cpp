#include "AssociativeArray.h"
#include "DynamicArray.h"
#include "StaticArray.h"
#include "Queue.h"
#include "PriorityQueue.h"



#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

#include <cmath>


struct RoomInfo
{
  int startDate;
	int endDate;
	int customerNum;
};

struct Rooms
{
  int room_num;
  string note;
  PriorityQueue<RoomInfo> eachRoom; // sorted by endDate, pop customers based on endDate
	bool operator<(const RoomInfo& a, const RoomsInfo b) { return (a.endDate < b.endDate); }
};

struct RoomTypes
{
	string name;
	double baseprice; // per night
	double price() { return baseprice * num_rooms / roomList.size(); } //per night
	int cap; // max ppl per room
	int num_rooms;
	DynamicArray<Rooms> roomList; // 101,102,103... and so on
	//PriorityQueue<RoomInfo> roomStatus;
};


struct Hotel
{
	string name;
	string city;
	int star;
	double rate;
	double min_price(int);
	PriorityQueue<RoomTypes> roomTypes;
  bool operator<(const RoomTypes& a, const RoomTypes& b) { return (a.cap > b.cap); }
};

double Hotel::min_price(int num_ppl)
{
	while(roomTypes.cap < num_ppl)
		roomTypes.pop();
	return roomTypes.top().price();
}



int main()
{




  AssociativeArray<string, Hotel> hotels;

  ifstream fin;
  fin.open("newHotel.txt");


	if(!fin)
	{
		cerr << "fin error";
		exit(EXIT_FAILURE);
	}

	string buf;

	fin >> buf; cout << buf;




	return 0;
}
