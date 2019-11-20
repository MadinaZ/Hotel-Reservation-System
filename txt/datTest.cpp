#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <typeinfo>
using namespace std;

#include <cstring>
#include <ctime>



struct Hotels
{
	char name[30];
	char city[20];
	int star;
	double rate;
	char type1[7];
	char type2[7];
	char type3[7];
	char type4[7];
	char type5[7];
	char type6[7];
	char type7[7];
	double baseprice[7];
	int cap[7];
	int num_rooms[7];
};


int main()
{
	srand(time(0));


	ofstream keepHotel("newHotel.dat", ios::out | ios::binary);
	ifstream readHotel("newHotel.dat", ios::in | ios::binary);
	ofstream outHotel("copydatHotel.txt");


	if(!keepHotel)
	{
		cerr << "keepHotel error";
		exit(EXIT_FAILURE);
	}
	if(!readHotel)
	{
		cerr << "keepHotel error";
		exit(EXIT_FAILURE);
	}
	if(!outHotel)
	{
		cerr << "outHotel error";
		exit(EXIT_FAILURE);
	}


	Hotels hotel;
	readHotel.read(reinterpret_cast <char*>(&hotel), sizeof(Hotels));

	while(readHotel && !readHotel.eof())
		cout << hotel.star << endl;

	return 0;
}
