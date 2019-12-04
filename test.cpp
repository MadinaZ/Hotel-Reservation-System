#include "AssociativeArray.h"
#include "DynamicArray.h"
#include "PriorityQueue.h"
#include "BinarySearchTree.h"

#include "Hotels.h"
//#include "RoomManage.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <set>
using namespace std;

#include <cmath>


struct RoomInfo
{
  int startDate;
  int endDate;
  int customerNum;

  RoomInfo():startDate(),endDate(),customerNum(){};
  RoomInfo(int a,int b,int c):startDate(a),endDate(b),customerNum(c){};
};
bool operator<(const RoomInfo& a, const RoomInfo& b) { return (a.endDate < b.endDate); }

struct Rooms
{
  int room_num;
  string note;
  PriorityQueue<RoomInfo> eachRoom; // sorted by endDate, pop customers based on endDate

  Rooms():room_num(),note(),eachRoom(){};
  Rooms(int a):room_num(a),note(),eachRoom(){};
};
bool operator<(const Rooms& a, const Rooms& b) { return (a.room_num < b.room_num); }


//bool operator<(const RoomInfo& a, const RoomInfo& b) { return (a.endDate < b.endDate); }

struct RoomTypes
{
  string name_rt;
  double baseprice; // per night
  int cap; // max ppl per room
  int num_rooms;

  double price() { return baseprice * num_rooms / roomList.size(); } // need update //per night
  DynamicArray<Rooms> roomList; // 101,102,103... and so on
  //PriorityQueue<RoomInfo> roomStatus;

  RoomTypes():name_rt(),baseprice(),cap(),num_rooms(),roomList(){};
  RoomTypes(string a,double b,int c,int d):name_rt(a),baseprice(b),cap(c),num_rooms(d), roomList(){};
};
bool operator<(const RoomTypes& a, const RoomTypes& b) { return (a.cap > b.cap); }


struct Hotel
{
  string name_h;
  string city;
  int star;
  double rate;
  double min_price(int);
  PriorityQueue<RoomTypes> roomTypes;

  Hotel():name_h(),city(),star(),rate(){};
  Hotel(string a,string b,int c,double d):name_h(a),city(b),star(c),rate(d){};
};
bool operator<(const Hotel& a, const Hotel& b) { return (a.city < b.city); }


double Hotel::min_price(int num_ppl)
{
 // while(roomTypes.top().cap < num_ppl)
  //  roomTypes.pop();
 // return roomTypes.top().baseprice;

	return 0.011; // test need uddate@@@@@@@
}



int main()
{


	BinarySearchTree<string, PriorityQueue<Hotel> > hotels; // <string, set<Hotel> doesn't work ....
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


    //store each room type
    for(int i = 0 ; i < temp1.num_rooms; i++)
    {
    	Rooms temp_rm(i);
    	temp1.roomList[i] = temp_rm;
    }
    for(int i = 0 ; i < temp2.num_rooms; i++)
    {
    	Rooms temp_rm(i);
    	temp2.roomList[i] = temp_rm;
    }
    for(int i = 0 ; i < temp3.num_rooms; i++)
    {
    	Rooms temp_rm(i);
    	temp3.roomList[i] = temp_rm;
    }
    for(int i = 0 ; i < temp4.num_rooms; i++)
    {
    	Rooms temp_rm(i);
    	temp4.roomList[i] = temp_rm;
    }
    for(int i = 0 ; i < temp5.num_rooms; i++)
    {
    	Rooms temp_rm(i);
    	temp5.roomList[i] = temp_rm;
    }
    for(int i = 0 ; i < temp6.num_rooms; i++)
    {
    	Rooms temp_rm(i);
    	temp6.roomList[i] = temp_rm;
    }
    for(int i = 0 ; i < temp7.num_rooms; i++)
    {
    	Rooms temp_rm(i);
    	temp7.roomList[i] = temp_rm;
    }



    cout << temp.city << temp.name_h << endl;
    hotels[temp.city].push(temp);

    inHotel.read(reinterpret_cast<char*>(&hotel), sizeof(Hotels));
   // hotels2[temp.city].insert(temp);
  } // finish storing hotel info

//  cout << hotels.size();
  cout << hotels["San Francisco"].top().name_h;
  hotels["San Francisco"].pop();
  cout << hotels["San Francisco"].top().name_h;
/*
  set<Hotel>::iterator it;
  for(it = hotels["San Francisco"].begin(); it != hotels["San Francisco"].end(); it++)
  	cout << it->name_h << endl;*/


  cout << "finish" << endl;
	return 0;
}
