#include "AssociativeArray.h"
#include "DynamicArray.h"
#include "PriorityQueue.h"

#include "RoomManage.h"
#include "Hotels.h"


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

#include <cmath>




int main()
{

	AssociativeArray<string, Hotel> hotels;  //key: city


	ifstream inHotel("newHotel.dat", ios::in | ios::binary);



	Hotels hotel;
  inHotel.seekg(0);
  inHotel.read(reinterpret_cast <char*>(&hotel), sizeof(Hotels));

  cout << hotel.name;
  int counter = 0;
  while(!inHotel.eof() && inHotel)
  {
    cout << hotel.name<< hotel.star << endl;

    inHotel.read(reinterpret_cast<char*>(&hotel), sizeof(Hotels));
    counter++;
  }

	return 0;
}
