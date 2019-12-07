//#include "AssociativeArray.h"
#include "DynamicArray.h"
#include "SortableArray.h"
#include "BinarySearchTree.h"
#include "StaticPQ.h"
//#include "StaticArray.h"
//#include "PriorityQueue.h"

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
#include <cctype>



struct Rooms
{
  int room_num;
  int reserved_num; // number of reservation for each room, meaning each room can accept a number of reservation unless same time
  									// Rooms are in ascending order in terms of reserved_num so that it is easy to find vacant room
  //int acc_num;
  string note;
  //StaticPQ<RoomInfo,10> eachRoom; // sorted by endDate, pop customers based on endDate / 400 is enough for 365 days?

  Rooms():room_num(0),reserved_num(0),note(""){};//,eachRoom(){};
  Rooms(int a):room_num(a),reserved_num(0),note(""){}; //,eachRoom(){};

  Rooms& operator=(const Rooms& ori)
  {
  	if(this == &ori) return *this;

  	room_num = ori.room_num;
  	note = ori.note;
  	//eachRoom = ori.eachRoom;

  	return *this;
  }
};
bool operator<(const Rooms& a, const Rooms& b) { return (a.reserved_num < b.reserved_num); }


//bool operator<(const Rooms& a, const RoomInfo& b) { return (a.endDate < b.endDate); }

struct RoomTypes
{
  string name_rt;
  double baseprice; // per night
  int cap; // max ppl per room
  int num_rooms;

  double price() { return baseprice * num_rooms / roomList.capacity(); } // need update //per night
  SortableArray<Rooms> roomList; // room 101,102,103... and so on
  //StaticArray<Rooms,1000> roomList;
  //SortableArray<RoomInfo> roomStatus;

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

  int pop_counter;// how many times it pops room types in each hotel. if greater than # of room types, not found
  Hotel():name_h(),city(),star(),rate(), pop_counter(0){};
  Hotel(string a,string b,int c,double d):name_h(a),city(b),star(c),rate(d),roomTypes(),pop_counter(0){};

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



list<Hotel>::iterator searchHotel(list<Hotel>&, string);
void reserve(list<Hotel>&, BinarySearchTree<int,SortableArray<ReserveInfo> >&, string, int);
int outputHotel(list<Hotel>&, string, int);
void outputAllHotel(list<Hotel>&, int);
int newAccnum(); //gives a new account number
int convertRoomNum(list<Hotel>::iterator, int);


int main()
{


	BinarySearchTree<string, list<Hotel> > hotels;	//key: city
	BinarySearchTree<int,SortableArray<ReserveInfo> >ri_Info; // key: roomNum
	//AssociativeArray<string, set<Hotel> > hotels;
//	BinarySearchTree<string, StaticPQ<RoomTypes,10> > hotel_name; // key: hotel name, value:roomtypes
	ifstream inHotel("newHotel.dat", ios::in | ios::binary);
	ifstream inUser("user.dat", ios::in | ios::binary);
	ofstream outUser("user.dat", ios::out | ios::binary);
	ofstream outtxtUser("user.txt");



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

   // cout << hotel.type1 << endl << hotel.type2 << endl << hotel.type3 << endl << hotel.type4 << endl
   // 		 << hotel.type5 << endl << hotel.type6 << endl << hotel.type7 << endl;

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

    hotels[temp.city].push_back(temp);


    inHotel.read(reinterpret_cast<char*>(&hotel), sizeof(Hotels));

  } // finish storing hotel info
  inHotel.close();


  //read user reserve info
	ReserveInfo ri_Read;
  inUser.seekg(0);
  inUser.read(reinterpret_cast <char*>(&ri_Read), sizeof(ReserveInfo));
  int counter = 0;
  while(!inUser.eof() && inUser)
  {


  	ri_Info[ri_Read.getRoomNum()][counter++].setCusNum(ri_Read.getCusNum());
  	ri_Info[ri_Read.getRoomNum()][counter++].setRoomNum(ri_Read.getRoomNum());
		ri_Info[ri_Read.getRoomNum()][counter++].setStartDate(ri_Read.getStartDate());
		ri_Info[ri_Read.getRoomNum()][counter++].setEndDate(ri_Read.getEndDate());

  	inUser.read(reinterpret_cast <char*>(&ri_Read), sizeof(ReserveInfo));
  }











  list<Hotel>::iterator it;

  it = hotels["London"].begin();
  cout << it->name_h << endl;



  cout << it->roomTypes.top().name_rt << it->roomTypes.top().cap<< endl;
  it->roomTypes.pop();
  cout << it->roomTypes.top().name_rt<< it->roomTypes.top().cap << endl;
  it->roomTypes.pop();
  cout << it->roomTypes.top().name_rt << it->roomTypes.top().cap<< endl;
  it->roomTypes.pop();
  cout << it->roomTypes.top().name_rt << it->roomTypes.top().cap<< endl;
  it->roomTypes.pop();
  cout << it->roomTypes.top().name_rt<< it->roomTypes.top().cap << endl;
  it->roomTypes.pop();
  cout << it->roomTypes.top().name_rt << it->roomTypes.top().cap << endl;
  it->roomTypes.pop();

  for(it = hotels["Amsterdam"].begin(); it != hotels["Amsterdam"].end(); it++)
  	cout << it->name_h << endl;


  string buf, city;
  int num_p, type;

  while(true)
  {
  	BinarySearchTree<string, list<Hotel> > copyHotel;
  	copyHotel = hotels;

  	cin.ignore(100,'\n');
		cout << "City? ";
		getline(cin, city);
		while(hotels[city].size() == 0)
		{
			cout << "No hotel found in the city" << endl;
			cout << "City? ";
			getline(cin, city);
		}


		set<pair<double,string> > sortprice;
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
	  //	int pop_counter[copyHotel[city].size()]; // how many times it pops room types in each hotel. if greater than # of room types, not found

//	  	for(int i = 0; i < copyHotel[city].size(); i++)
	//  		pop_counter[i] = 0;
			//look for the cheapest price based on # ppl
	  	int i = 0;
			for(it = copyHotel[city].begin(); it != copyHotel[city].end(); i++, it++)
			{
				int ori_size = it->roomTypes.size();

				while(it->roomTypes.top().cap < num_p) // pop room types with a cap less than user input
				{
					it->roomTypes.pop();

					if(++it->pop_counter == ori_size) break; // no more pop than the size of room types
				}
				if(it->roomTypes.size() == 0) continue;
				pair<double,string> temp;
				temp.first = it->roomTypes.top().baseprice;
				temp.second = it->name_h;
				sortprice.insert(temp);
			}

			if(sortprice.size() == 0)
				cout << "No hotel found" << endl;
			else
				break;
    }


		cout << "The cheapest hotel in " << city << "\n\t" << sortprice.begin()->second << " from $"
				 << fixed << setprecision(2) << sortprice.begin()->first << endl << endl;


		cout << "Wanna reserve this hotel? (Y/N) ";
		cin >> buf;
		cout << endl;
		if(buf[0] == 'y' || buf[0] == 'Y')
		{
			it = copyHotel[city].begin();
			it++;
			cout << it->roomTypes.size();


			type = outputHotel(copyHotel[city],sortprice.begin()->second, num_p);
			cout << type;

			reserve(hotels[city], ri_Info, sortprice.begin()->second, type);
		}
		else
		{
			cout << "Wanna see the list of the hotels in " << city << " ? (Y/N) ";
			cin >> buf;
			cout << endl;
			if(buf[0] == 'y' || buf[0] == 'Y')
				outputAllHotel(hotels[city],num_p);
			else
			{
				cout << "Search hotel again? (Y/N) ";
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


void reserve(list<Hotel>& h, BinarySearchTree<int,SortableArray<ReserveInfo> >& ri,string name_h, int type)
{
	ofstream outUser("user.dat", ios::out | ios::binary);
	string buf, buf2;
	list<Hotel>::iterator it = searchHotel(h, name_h);
	ReserveInfo r_info;
	int acc_num,room_num,start_date,end_date;



	cout << "Enter your account number (If you don't have one, enter 'x'):  ";
	cin.ignore(1000,'\n');
	getline(cin, buf);
	if(buf[0] == 'x' || buf[0] == 'X')
	{
		acc_num = newAccnum();
		cout << "Your account number is " << acc_num << endl;
		r_info.setCusNum(acc_num);
	}
	else
	{
		while(atoi(buf.c_str()) == 0)
		{
			if(buf[0] == 'x' || buf[0] == 'X')
			{
				cout << "Your account number is " << newAccnum() << endl;
				r_info.setCusNum(newAccnum());
				break;
			}
			cout << "Invalid account number";
			getline(cin, buf);
			r_info.setCusNum(stoi(buf));
		}
	}

	// if the user info exit?? ?@@@@@@@

// need validation!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	cout << "from What day?? (20190801)";
	getline(cin,buf);
	start_date = stoi(buf);
	cout << "to What day?? (20190801)";
	getline(cin,buf);
	end_date = stoi(buf);


	for(int i = 0; i < type; i++) // go to the room type of the hotel
		it->roomTypes.pop();

	room_num = convertRoomNum(it, type);


		bool book = false;
		for(int i = 0; i < ri[room_num].capacity(); i++)
		{
			if(ri[room_num][i].getStartDate() == 0 && ri[room_num][i].getEndDate() == 0) //find both start and end date 0
			{
				ri[room_num][i].setCusNum(acc_num);
				ri[room_num][i].setRoomNum(room_num);
				ri[room_num][i].setStartDate(start_date);
				ri[room_num][i].setEndDate(end_date);
				it->roomTypes.top().roomList[0].reserved_num++; // increment reserved num;

				book = true;
				break;
			}
		}

		if(!book) // no o star and end date, then add it to the new index
		{
			ri[room_num][ri[room_num].capacity()].setCusNum(acc_num);
			ri[room_num][ri[room_num].capacity()].setRoomNum(room_num);
			ri[room_num][ri[room_num].capacity()].setStartDate(start_date);
			ri[room_num][ri[room_num].capacity()].setEndDate(end_date);
			it->roomTypes.top().roomList[0].reserved_num++;
		}

		outUser.seekp(0, ios::end);
		outUser.write(reinterpret_cast <char*>(&ri_Read), sizeof(ReserveInfo))


}

list<Hotel>::iterator searchHotel(list<Hotel>& h, string name)
{
	list<Hotel>::iterator it;
	for(it = h.begin(); it != h.end(); it++)
		if(it->name_h == name) break;

	return it;
}


int outputHotel(list<Hotel>& h, string name_h, int num_p)
{
	string buf;
	list<Hotel>::iterator it = searchHotel(h, name_h);
	int size = it->roomTypes.size();
	int pop_counter[size];

	cout.setf(ios::left);
	cout << name_h << endl;
	cout << " " << setw(8) << "Choice" << setw(15) << "Room Type" << setw(9) << "Price($)" << setw(25) << "Capacity(ppl)" << endl
			 << "---------------------------------------------" << endl;


	cout << size;
	for(int i = 0; i < size; i++)
	{
		cout << "    " << setw(5) << i + 1 << setw(15) << it->roomTypes.top().name_rt << setw(9) << it->roomTypes.top().baseprice << "     " << it->roomTypes.top().cap << endl;
		pop_counter[i] = it->pop_counter;
		it->roomTypes.pop();
	}

	cout << "Enter your choice in a number: " ;
	cin >> buf;

	while(atoi(buf.c_str()) < 1 || atoi(buf.c_str()) > size)
	{
		cout << "Invalid input. Enter again: ";
		cin >> buf;
	}
	cout <<stoi(buf) + pop_counter[stoi(buf)];

	return stoi(buf) + pop_counter[stoi(buf)]; // number from the top of copyHotel + pop_counter = # from the top of hotels

//	return 0;
}

void outputAllHotel(list<Hotel>& h, int num_p)
{
	list<Hotel>::iterator it;
	for(it = h.begin(); it != h.end(); it++)
	{
		cout.setf(ios::left);
		cout << it->name_h << endl;
		cout << " " << setw(8) << "Choice" << setw(15) << "Room Type" << setw(9) << "Price($)" << setw(25) << "Capacity(ppl)" << endl
				 << "---------------------------------------------" << endl;

		int size = it->roomTypes.size();
		cout << size;
		for(int i = 0; i < size; i++)
			cout << "    " << setw(5) << i + 1 << setw(15) << it->roomTypes.top().name_rt << setw(9) << it->roomTypes.top().baseprice << "     " << it->roomTypes.top().cap << endl;
		cout << endl;
	}
}

int newAccnum()
{
	return 0;
}


int convertRoomNum(list<Hotel>::iterator it, int type) // convert hotel name(string) to integer, then add room number
{
	int room_num;
	int value = 0,counter = 0;
	string name_h = it->name_h;
	const string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for(int i = 0; i < type; i++)
		it->roomTypes.pop();

	room_num = it->roomTypes.top().roomList[0].room_num;

	for(int i = 0; i < 10; i+=3)
	{
		int temp;

		if(isalpha(name_h[i]))
			name_h[i] = toupper(name_h[i]);
		const auto pos = alpha.find(name_h);
		if(pos != string::npos)
			temp = pos + 1; // let 'A' to be 1
		else
			temp = 0;

		value += temp * pow(10,6 - counter++);	// last three digits are room number like 101
	}

	return value += room_num;
}
