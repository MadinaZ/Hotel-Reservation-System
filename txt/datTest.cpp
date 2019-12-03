#include "Hotels.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <typeinfo>
using namespace std;

#include <cstring>
#include <ctime>




int main()
{
	srand(time(0));


	//ofstream keepHotel("newHotel.dat", ios::out | ios::binary);
	ifstream readHotel("newHotel.dat", ios::in | ios::binary);
	ofstream outHotel("copydatHotel.txt");



	/*if(!keepHotel)
	{
		cerr << "keepHotel error";
		exit(EXIT_FAILURE);
	}*/
	if(!readHotel)
	{
		cerr << "readHotel error";
		exit(EXIT_FAILURE);
	}
	if(!outHotel)
	{
		cerr << "outHotel error";
		exit(EXIT_FAILURE);
	}


	int counter =0;
	Hotels hotel;
  readHotel.seekg(0);
  readHotel.read(reinterpret_cast <char*>(&hotel), sizeof(Hotels));

  cout << hotel.name;

  while(!readHotel.eof() && readHotel)
  {
    cout << hotel.name<< hotel.star << endl;

    readHotel.read(reinterpret_cast<char*>(&hotel), sizeof(Hotels));
    counter++;
  }

	cout<< counter;

	return 0;
}
