#include "AssociativeArray.h"
#include "DynamicArray.h"
#include "PriorityQueue.h"
#include "BinarySearchTree.h"
#include "StaticPQ.h"
#include "StaticArray.h"

#include "Hotels.h"
#include "ReserveInfo.h"
//#include "RoomManage.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>
#include <set>
using namespace std;

#include <cmath>



struct Rooms
{
  int room_num;
  string note;
  //StaticPQ<RoomInfo,10> eachRoom; // sorted by endDate, pop customers based on endDate / 400 is enough for 365 days?

  Rooms():room_num(33),note(){};//,eachRoom(){};
  Rooms(int a):room_num(a),note(){}; //,eachRoom(){};

  Rooms& operator=(const Rooms& ori)
  {
  	if(this == &ori) return *this;

  	room_num = ori.room_num;
  	note = ori.note;
  	//eachRoom = ori.eachRoom;

  	return *this;
  }
};
bool operator<(const Rooms& a, const Rooms& b) { return (a.room_num < b.room_num); }


//bool operator<(const RoomInfo& a, const RoomInfo& b) { return (a.endDate < b.endDate); }

struct RoomTypes
{
  string name_rt;
  double baseprice; // per night
  int cap; // max ppl per room
  int num_rooms;

  double price() { return baseprice * num_rooms / roomList.capacity(); } // need update //per night
  //DynamicArray<Rooms> roomList; // 101,102,103... and so on
  StaticArray<Rooms,100> roomList;
  //PriorityQueue<RoomInfo> roomStatus;

  RoomTypes():name_rt(),baseprice(),cap(),num_rooms(),roomList(){};
  RoomTypes(string a,double b,int c,int d):name_rt(a),baseprice(b),cap(c),num_rooms(d), roomList(){};

  RoomTypes& operator=(const RoomTypes& ori)
	{
  	if(this == &ori) return *this;

  	name_rt = ori.name_rt;
  	baseprice = ori.baseprice;
  	cap = ori.cap;
  	num_rooms = ori.num_rooms;
  	roomList = ori.roomList;

  	return *this;
	}

};
bool operator<(const RoomTypes& a, const RoomTypes& b) { return (a.cap > b.cap); }


struct Hotel
{
  string name_h;
  string city;
  int star;
  double rate;
  double min_price(int);
  StaticPQ<RoomTypes,10> roomTypes;

  Hotel():name_h(),city(),star(),rate(){};
  Hotel(string a,string b,int c,double d):name_h(a),city(b),star(c),rate(d), roomTypes(){};

  Hotel& operator=(const Hotel& ori)
  {
  	if(this == &ori) return *this;

  	name_h = ori.name_h;
  	city = ori.city;
  	star = ori.star;
  	rate = ori.rate;
  	roomTypes = ori.roomTypes;

  	return *this;
  }
};
bool operator<(const Hotel& a, const Hotel& b) { return (a.city < b.city); }


double Hotel::min_price(int num_ppl)
{
 // while(roomTypes.top().cap < num_ppl)
  //  roomTypes.pop();
 // return roomTypes.top().baseprice;

	return 0.011; // test need uddate@@@@@@@
}




void reserve();


int main()
{


	BinarySearchTree<string, list<Hotel> > hotels;
	//AssociativeArray<string, set<Hotel> > hotels2;  //key: city


	ifstream inHotel("newHotel.dat", ios::in | ios::binary);



	Hotels hotel;
  inHotel.seekg(0);
  inHotel.read(reinterpret_cast <char*>(&hotel), sizeof(Hotels));



  while(!inHotel.eof() && inHotel)
  {
    //cout << hotel.name<< hotel.star << endl;

    Hotel temp(hotel.name,hotel.city,hotel.star,hotel.rate); // create temp hotel


    //store 7 types info
    RoomTypes temp1(hotel.type1,hotel.baseprice[0],hotel.cap[0],hotel.num_rooms[0]);
    RoomTypes temp2(hotel.type2,hotel.baseprice[1],hotel.cap[1],hotel.num_rooms[1]);
    RoomTypes temp3(hotel.type3,hotel.baseprice[2],hotel.cap[2],hotel.num_rooms[2]);
    RoomTypes temp4(hotel.type4,hotel.baseprice[3],hotel.cap[3],hotel.num_rooms[3]);
    RoomTypes temp5(hotel.type5,hotel.baseprice[4],hotel.cap[4],hotel.num_rooms[4]);
    RoomTypes temp6(hotel.type6,hotel.baseprice[5],hotel.cap[5],hotel.num_rooms[5]);
    RoomTypes temp7(hotel.type7,hotel.baseprice[6],hotel.cap[6],hotel.num_rooms[6]);


    for(int i = 0 ; i < temp1.num_rooms; i++)
    	temp1.roomList[i].room_num = i;
    for(int i = 0 ; i < temp2.num_rooms; i++)
    	temp2.roomList[i].room_num = i;
    for(int i = 0 ; i < temp3.num_rooms; i++)
    	temp3.roomList[i].room_num = i;
    for(int i = 0 ; i < temp4.num_rooms; i++)
    	temp4.roomList[i].room_num = i;
    for(int i = 0 ; i < temp5.num_rooms; i++)
    	temp5.roomList[i].room_num = i;
    for(int i = 0 ; i < temp6.num_rooms; i++)
    	temp6.roomList[i].room_num = i;
    for(int i = 0 ; i < temp7.num_rooms; i++)
    	temp1.roomList[i].room_num = i;

    //store roomtype
    temp.roomTypes.push(temp1);
    temp.roomTypes.push(temp2);
    temp.roomTypes.push(temp3);
    temp.roomTypes.push(temp4);
    temp.roomTypes.push(temp5);
    temp.roomTypes.push(temp6);
    temp.roomTypes.push(temp7);


    //hotels[temp.city].push(temp);
    hotels[temp.city].push_back(temp);

    inHotel.read(reinterpret_cast<char*>(&hotel), sizeof(Hotels));
   // hotels2[temp.city].insert(temp);
  } // finish storing hotel info

//  cout << hotels.size();
//  cout << hotels["San Francisco"].top();
 // hotels["San Francisco"].pop();
 // cout << hotels["San Francisco"].top().name_h;

  list<Hotel>::iterator it;
  for(it = hotels["London"].begin(); it != hotels["London"].end(); it++)
  	cout << it->name_h << endl;


  BinarySearchTree<string, list<Hotel> > copyHotel;
  copyHotel = hotels;


  for(it = copyHotel["London"].begin(); it != copyHotel["London"].end(); it++)
  	cout << it->name_h << endl;


  string city, buf;
  int num_p;

  cout << "City? ";
  getline(cin, city);
  while(hotels[city].size() == 0)
  {
  	cout << "No hotel found in the city" << endl;
    cout << "City? ";
    getline(cin, city);
  }


  while(true)
  {
		cout << "How many people? " << endl;
		cin >> buf;
		num_p = atoi(buf.c_str());
		while(num_p == 0)
		{
			cout << "need to be more than 0" << endl;
			cout << "How many people? " << endl;
			cin >> buf;
			num_p = atoi(buf.c_str());
		}
		set<pair<double,string> > sortprice;
		//look for the cheapest price in the user condition
		for(it = copyHotel[city].begin(); it != copyHotel[city].end(); it++)
		{
			while(it->roomTypes.top().baseprice == 0) // remove 0 dollar hotel roomtypes
				it->roomTypes.pop();
			while(it->roomTypes.top().cap >= num_p) // pop roomytypes with a cap less than user input
				it->roomTypes.pop();



			pair<double,string> temp;
			temp.first = it->roomTypes.top().baseprice;
			temp.second = it->name_h;
			sortprice.insert(temp);
		}
		cout << "The cheapest hotel in " << city << "\n\t" << sortprice.begin()->second << " from $"
				 << fixed << setprecision(2) << sortprice.begin()->first << endl << endl;


		cout << "Wanna reserve this hotel? (Y/N) ";
		cin >> buf;
		cout << endl;
		if(buf[0] == 'y' || buf[0] == 'Y') reserve();
		else
		{
			cout << "Wanna see the list of the hotels in " << city << " ? (Y/N) ";
			cin >> buf;
			if(buf[0] == 'y' || buf[0] == 'Y')
			{

			}
			else
			{
				cout << "Serach hotel again? (Y/N) ";
				cin >> buf;
				if(buf[0] == 'y' || buf[0] == 'Y')
					continue;
				else
					break;

			}
		}

  }




  cout << "finish" << endl;
	return 0;
}

void reserve()
{
	string buf;
	int acc_num;
	cout << "Enter your account number: ";
	getline(cin, buf);
	while(buf.c_str() == 0)
	{
		cout << "Invalid account number";
		getline(cin, buf);

	}




}
