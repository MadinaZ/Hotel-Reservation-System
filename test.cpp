//#include "AssociativeArray.h"
//#include "DynamicArray.h"
#include "SortableArray.h"
#include "BinarySearchTree.h"
#include "StaticPQ.h"
#include "StaticArray.h"
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
 // int reserved_num; // number of reservation for each room, meaning each room can accept a number of reservation unless same time
  									// Rooms are in ascending order in terms of reserved_num so that it is easy to find vacant room
  //int acc_num;
  string note;
  //StaticPQ<RoomInfo,10> eachRoom; // sorted by endDate, pop customers based on endDate / 400 is enough for 365 days?

  Rooms():room_num(0),note(""){};//,eachRoom(){};
  Rooms(int a):room_num(a),note(""){}; //,eachRoom(){};

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
bool operator<(const RoomTypes& a, const RoomTypes& b)
{
	if (a.cap != b.cap)
		return (a.cap > b.cap);
	else
		return (a.baseprice > b.baseprice);

}


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

void cancel(BinarySearchTree<string,SortableArray<ReserveInfo> >&);
list<Hotel>::iterator searchHotel(list<Hotel>&, string);
bool reserve(BinarySearchTree<string, list<Hotel> >&, BinarySearchTree<string,SortableArray<ReserveInfo> >&, list<Hotel>::iterator, int);
int outputHotel(list<Hotel>&, list<Hotel>::iterator);
void outputAllHotel(list<Hotel>&, int);
int newAccnum(); //gives a new account number
string convertRoomNum(list<Hotel>::iterator, int,BinarySearchTree<string,SortableArray<ReserveInfo> >&);
void restoreHotels(BinarySearchTree<string, list<Hotel> >&, string);


int main()
{


	BinarySearchTree<string, list<Hotel> > hotels;	//key: city
	BinarySearchTree<string,SortableArray<ReserveInfo> >ri_room; // key: roomChar
	BinarySearchTree<int,SortableArray<ReserveInfo> >ri_user; // key: account number

	//BinarySearchTree<string, set<Hotel> > hotels;
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
    	temp1.roomList[i].room_num = i + 1;
    for(int i = 0 ; i < temp2.num_rooms; i++)
    	temp2.roomList[i].room_num = i + 1;
    for(int i = 0 ; i < temp3.num_rooms; i++)
    	temp3.roomList[i].room_num = i + 1;
    for(int i = 0 ; i < temp4.num_rooms; i++)
    	temp4.roomList[i].room_num = i + 1;
    for(int i = 0 ; i < temp5.num_rooms; i++)
    	temp5.roomList[i].room_num = i + 1;
    for(int i = 0 ; i < temp6.num_rooms; i++)
    	temp6.roomList[i].room_num = i + 1;
    for(int i = 0 ; i < temp7.num_rooms; i++)
    	temp7.roomList[i].room_num = i + 1;


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
  	ri_room[ri_Read.getRoomChar()][counter].setCusNum(ri_Read.getCusNum());
  	ri_room[ri_Read.getRoomChar()][counter].setRoomChar(ri_Read.getRoomChar());
		ri_room[ri_Read.getRoomChar()][counter].setStartDate(ri_Read.getStartDate());
		ri_room[ri_Read.getRoomChar()][counter].setEndDate(ri_Read.getEndDate());

  	ri_user[ri_Read.getCusNum()][counter++].setCusNum(ri_Read.getCusNum());
  	ri_user[ri_Read.getCusNum()][counter++].setRoomChar(ri_Read.getRoomChar());
		ri_user[ri_Read.getCusNum()][counter++].setStartDate(ri_Read.getStartDate());
		ri_user[ri_Read.getCusNum()][counter++].setEndDate(ri_Read.getEndDate());

  	inUser.read(reinterpret_cast <char*>(&ri_Read), sizeof(ReserveInfo));
  }


  //cout << ri_room["Hotel-KingSuite-1"][0].getCusNum();

//test
  list<Hotel>::iterator it;
  string buf, city;
  int num_p, type;
  cout << endl << endl;
  cout << "Welcome to our hotel booking system!\n" << endl
  		 << "  1. Search hotels\n"
  		 << "  2. Modify your reservation\n" << endl
			 << "choice(1 or 2): ";
  cin >> buf;

  cout << endl;
  while(atoi(buf.c_str()) < 1 || atoi(buf.c_str()) > 2)
  {
  	cout << "Invalid input\n"
  			 << "Please choose 1 or 2\n"
				 << "  1. Search hotels\n"
				 << "  2. Modify your reservation\n" << endl
				 << "choice(1 or 2): ";
  	cin >> buf;
  	cout << endl;
  }

  switch(stoi(buf))
  {
  case 1: break;
  case 2: cancel(ri_room);
  }

  while(true)
  {

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

			cout << "How many people? ";
			cin >> buf;
			num_p = atoi(buf.c_str());
			while(num_p == 0)
			{
				cout << "need to be more than 0" << endl;
				cout << "How many people? " ;
				cin >> buf;
				num_p = atoi(buf.c_str());
			}
	  //	int pop_counter[hotels[city].size()]; // how many times it pops room types in each hotel. if greater than # of room types, not found

//	  	for(int i = 0; i < hotels[city].size(); i++)
	//  		pop_counter[i] = 0;
			//look for the cheapest price based on # ppl
	  	int i = 0;
			for(it = hotels[city].begin(); it != hotels[city].end(); i++, it++)
			{
				int ori_size = it->roomTypes.size();

				while(it->roomTypes.top().cap < num_p) // pop room types with a cap less than user input
				{
					it->roomTypes.topKeepandPop();

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

    cout << endl;

		cout << "   The cheapest hotel for " << num_p << (num_p == 1 ? " person" : " people") << " in "<< city << " is\n --→  『 " << sortprice.begin()->second << " 』  from   $"
				 << fixed << setprecision(2) << sortprice.begin()->first << endl;
		it = searchHotel(hotels[city],sortprice.begin()->second);
		cout << "        star: " << it->star << "   rate by users: " << it->rate << endl << endl;
		cout << "You have " << hotels[city].size() - 1 << " more options in " << city << endl;

		cout << "  1. Reserve 『 " << sortprice.begin()->second << " 』" << endl
				 << "  2. See other hotels in " << city << endl << endl
				 << "choice(1 or 2): " ;
		cin >> buf;
		while(atoi(buf.c_str()) != 1 && atoi(buf.c_str()) != 2)
		{
			cout << "Invalid input" << endl;
			cout << "  1. Reserve 『 " << sortprice.begin()->second << " 』" << endl
					 << "  2. See other hotels in " << city << endl << endl
					 << "choice(1 or 2): " ;
			cin >> buf;
		}
		if(stoi(buf) == 1)
		{
			type = outputHotel(hotels[city],it); // second is the name of hotel
			if(reserve(hotels, ri_room, it, type))
			{
				cout << "done";
			}
		}
		else // choice 2
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



void cancel(BinarySearchTree<string,SortableArray<ReserveInfo> >& ri)
{
	cout << "test";
}


bool reserve(BinarySearchTree<string, list<Hotel> >& h, BinarySearchTree<string,SortableArray<ReserveInfo> >& ri,list<Hotel>::iterator it, int type)
{
	ofstream outUser("user.dat", ios::out | ios::binary);
	string buf;

	ReserveInfo r_info;
	int acc_num,start_date,end_date;
	string roomChar;
	roomChar = convertRoomNum(it, type, ri);
	if(roomChar[0] == '0') return false; // all rooms are booked


	cout << "   Booking 『 " << roomChar << " 』 ...\n\n"
			 << "Enter your account number (If you don't have one, enter 'x'):  ";
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
				acc_num = newAccnum();
				cout << "Your account number is " << newAccnum() << endl;
				r_info.setCusNum(newAccnum());
				break;
			}
			cout << "Invalid account number";
			getline(cin, buf);
		}
		cout << "num " << stoi(buf) << endl;
		acc_num = stoi(buf);
		r_info.setCusNum(stoi(buf));
	}

	// if the user info exit?? ?@@@@@@@

// need validation!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	cout << "From what day (YYYY.MM.DD) ?? ";
	getline(cin,buf);

	while(buf[0] != '2' || buf[4] != '.' || buf[7] != '.') // 2000 or later need restrict validation
	{
		cout << "Invalid input\n"
				 << "From what day?? (YYYY.MM.DD) ?? ";
		getline(cin,buf);
	}
	buf.erase(4,1);
	buf.erase(6,1);
	start_date = stoi(buf);


	cout << "To what day (YYYY.MM.DD) ?? ";
	getline(cin,buf);
	end_date = 0;
	while(end_date <= start_date)
	{
		while(buf[0] != '2' || buf[4] != '.' || buf[7] != '.') // 2000 or later
		{
			cout << "Invalid input\n"
					 << "To what day?? (YYYY.MM.DD) ?? ";
			getline(cin,buf);
		}
		buf.erase(4,1);
		buf.erase(6,1);
		end_date = stoi(buf);

		if(end_date <= start_date)
		{
			cout << "End date should be after start date\n"
					 << "To what day (YYYY.MM.DD) ?? ";
			getline(cin,buf);
		}
	}


	int aaa;

		bool capa = false; // caoacity of sortable array
		for(int i = 0; i < ri[roomChar].capacity(); i++)
		{
			if(ri[roomChar][i].getCusNum() == 0) //no customer
			{
				ri[roomChar][i].setCusNum(acc_num);
				ri[roomChar][i].setRoomChar(roomChar);
				ri[roomChar][i].setStartDate(start_date);
				ri[roomChar][i].setEndDate(end_date);
			//cout << it->roomTypes.top().roomList[0].reserved_num++; // increment reserved num
				aaa = i;
				capa = true;
				cout << " aaaa "  << aaa;
				break;
			}
		}
		if(!capa)
		{
			cout << ri[roomChar].capacity();
			ri[roomChar][ri[roomChar].capacity()].setCusNum(acc_num);
			ri[roomChar][ri[roomChar].capacity()].setRoomChar(roomChar);
			ri[roomChar][ri[roomChar].capacity()].setStartDate(start_date);
			ri[roomChar][ri[roomChar].capacity()].setEndDate(end_date);
			// cout << 	it->roomTypes.top().roomList[0].reserved_num++;
			cout << "ajhha";
		}

		r_info.setStartDate(start_date);
		r_info.setEndDate(end_date);
		r_info.setRoomChar(roomChar);

		outUser.seekp(0, ios::end);
		outUser.write(reinterpret_cast <const char*>(&r_info), sizeof(ReserveInfo));
		ofstream outtxtUser("user.txt");
		outtxtUser  << acc_num << '\t' << roomChar << '\t' << start_date << '\t' << end_date << endl;
		cout << "for binary" << r_info.getRoomChar();
		cout << "Booking is done!" << endl;
		cout << acc_num << '\t' << roomChar << '\t' << start_date << '\t' << end_date << endl;
		cout << " aa" <<ri[roomChar][0].getCusNum()	 << endl;

		ReserveInfo ri_Read;
		ifstream inUser("user.dat", ios::in | ios::binary);
	  inUser.seekg(0);
	  inUser.read(reinterpret_cast <char*>(&ri_Read), sizeof(ReserveInfo));
	  cout << ri_Read.getRoomChar();
		cout << endl<< endl;

	//	cout << it->roomTypes.top().roomList[0].reserved_num;
	//	cout <<ri[roomChar][ri[roomChar].capacity()].getRoomChar();
		restoreHotels(h, it->city);

		return true;

}

list<Hotel>::iterator searchHotel(list<Hotel>& h, string name)
{
	list<Hotel>::iterator it;
	for(it = h.begin(); it != h.end(); it++)
		if(it->name_h == name) break;

	return it;
}


int outputHotel(list<Hotel>& h, list<Hotel>::iterator it)
{
	string buf;

	int size = it->roomTypes.size();

	cout.setf(ios::left);
	cout << endl << endl;
	cout << "   『 " << it->name_h << " 』\n" << endl;
	cout << left << " " << setw(8) << "Choice" << setw(15) << "Room Type" << right << setw(8) << "Price($)" << setw(15) << "Capacity(ppl)" << endl
			 << "-------------------------------------------------" << endl;

	for(int i = 0; i < size; i++)
	{
		cout << left << "    " << setw(5) << i + 1 << setw(15) << it->roomTypes.top().name_rt << right << setw(8) << it->roomTypes.top().baseprice << "     " << it->roomTypes.top().cap << endl;
		it->roomTypes.topKeepandPop();
	}
	cout << endl;
	cout << "Choose a room type (1 - " << size  << "):";
	cin >> buf;

	while(atoi(buf.c_str()) < 1 || atoi(buf.c_str()) > size)
	{
		cout << "Invalid input\n"
		     << "Choose a room type (1 - " << size  << "): ";
		cin >> buf;
	}

	cout << endl << endl << endl;
	return stoi(buf) + it->pop_counter; // number from the top of hotels + pop_counter = # from the top of hotels
}

void outputAllHotel(list<Hotel>& h, int num_p)
{
	list<Hotel>::iterator it;
	int size = it->roomTypes.size();
	int pop_counter[size];

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


string convertRoomNum(list<Hotel>::iterator it, int type, BinarySearchTree<string, SortableArray<ReserveInfo> >& ri_room)
{
	string roomChar;
	int counter = 0;
	int date = 20191209; // start date wanna stay

	cout << "test" << endl;
	it->roomTypes.keepPushBack();

	for(int i = 0; i < type - 1; i++)
		it->roomTypes.topKeepandPop();

	bool available = false;
	if(ri_room[roomChar][0].getCusNum() == 0)
	{
		available = true;
		roomChar = it->name_h;
		roomChar += "-";
		roomChar += it->roomTypes.top().name_rt;
		roomChar += "-";
		roomChar += to_string(it->roomTypes.top().roomList[0].room_num);
	}
	else
	{
		while(counter < it->roomTypes.top().num_rooms) // check all rooms' availability
		{
			roomChar = it->name_h;
			roomChar += "-";
			roomChar += it->roomTypes.top().name_rt;
			roomChar += "-";
			roomChar += to_string(it->roomTypes.top().roomList[counter++].room_num);


			for(int i = 0 ; i < ri_room[roomChar].capacity(); i++) // track all customers book this room
			{
				if(ri_room[roomChar][i].getEndDate() >= date)
					if(ri_room[roomChar][i].getStartDate() <= date)
							break; // this room is occupied

				available = true;
			}
			if(available) break;
		}
	}


	if(!available) roomChar = "0"; //all booked


	return roomChar;
}

void restoreHotels(BinarySearchTree<string, list<Hotel> >& h, string city) //push back all hotels poped and stored in static array
{
	for(list<Hotel>::iterator it = h[city].begin(); it != h[city].end(); ++it)
		it->roomTypes.keepPushBack();
}
