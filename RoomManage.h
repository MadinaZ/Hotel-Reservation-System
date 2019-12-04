#ifndef ROOMMANAGE_H
#define ROOMMANAGE_H

#include "AssociativeArray.h"
#include "DynamicArray.h"
#include "PriorityQueue.h"
#include "BinarySearchTree.h"

#include <string>
using namespace std;


#endif

struct RoomInfo
{
  int startDate;
  int endDate;
  int customerNum;

  RoomInfo():startDate(),endDate(),customerNum(){};
  RoomInfo(int a,int b,int c):startDate(a),endDate(b),customerNum(c){};
};

struct Rooms
{
  int room_num;
  string note;
  PriorityQueue<RoomInfo> eachRoom; // sorted by endDate, pop customers based on endDate

  Rooms():room_num(),note(),eachRoom(){};
  Rooms(int a):room_num(a),note(),eachRoom(){};
};

bool operator<(const RoomInfo& a, const RoomInfo& b) { return (a.endDate < b.endDate); }

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
