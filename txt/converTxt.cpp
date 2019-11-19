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
	string name;
	string city;
	int star;
	double rate;
	string roomytype[7];
	double baseprice[7];
	int cap[7];
	int num_rooms[7];
};


void write(ostream&, const Hotels);




int main()
{
	srand(time(0));
	ifstream fin;
	fin.open("Hotel.txt");

	ofstream keepHotel("newHotel.dat", ios::out | ios::binary);
	ifstream readHotel("newHotel.dat", ios::in | ios::binary);
	ofstream outHotel("newHotel.txt");

	if(!fin)
	{
		cerr << "fin error";
		exit(EXIT_FAILURE);
	}
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


  char *token;
  char buf[1000];
  const char* const tab = "\t";
  int line_counter = 0;

  while(fin.good())
  {
  	string line;
  	getline(fin, line);
    strcpy(buf, line.c_str());

    if(buf[0] == 0)	continue;

    const string name (token = strtok(buf, tab));
    const string star((token = strtok(0, tab)) ? token : "");
    const string location((token = strtok(0, tab)) ? token : "");
    const string price((token = strtok(0, tab)) ? token : "");
    const string rate((token = strtok(0, tab)) ? token : "");



    int n = rand()%2 + 1;
    string type[7];
    double baseprices[7];
    int cap[7], num_rooms[7];

    // hotel price = baseprice * RevPAR

    switch(n)
    {
    	case 1:  type[0] = "typeA"; type[1] = "typeB"; type[2] = "typeC"; type[3] = "typeD";
    					 type[4] = "typeE"; type[5] = "typeF"; type[6] = "typeG";
    					for(int i = 0; i < 7; i++)
    					{
    						baseprices[i] = rand()%200000 / 100.00 + 20;
    						cap[i] = rand()%5 + 1;
    						num_rooms[i] = rand()%200;
    					}
    					break;
    	case 2: type[0] = "King Suite"; type[1] = "King Room"; type[2] = "Queen Suite"; type[3] = "Queen Room";
    					type[4] = "Luxury"; type[5] = "Premium";
    					double k = rand()%1000/100.00 + 1;
    					baseprices[0] = 200*k; baseprices[1] = 150*k; baseprices[2] = 100*k; baseprices[3] = 50*k;
    					baseprices[4] = 30*k; baseprices[5] = 20*k;
    					cap[0] = 6; cap[1] = 4; cap[2] = 4; cap[3] = 2; cap[4] = 2; cap[5] = 2;
    					for(int i = 0; i < 6; i++)
    						num_rooms[i] = rand()%100;
    					break;
    }


    outHotel.setf(ios::left);
    outHotel << fixed;
    cout << name << endl;
    int n_max = (n == 1 ? 7:6);
    outHotel << setw(30) << name << setw(20) << location << setw(5) << star << setw(5) << rate;

    if(line_counter == 0)
    	outHotel << setw(13) << "Roomtype" << setw(9) << "baseprice" << setw(4) << "cap" << setw(5) << "num_rooms" << endl;
    else
    {
    	for(int i = 0; i < n_max; i++)
    	{
    		outHotel << setw(13) << type[i] << setw(9) << setprecision(2) << baseprices[i] << setw(4) << cap[i] << setw(5) << num_rooms[i];
    	}
    }
    outHotel << endl;

    ++line_counter;



    // for binary

    Hotels hotel;
    hotel.name = name;
    hotel.city = location;
    hotel.star = atoi(star.c_str());
    hotel.rate = atof(rate.c_str());
    for(int i = 0; i < 7; i++)
    {
    	if(n == 2 && i == 6)
    	{
      	hotel.roomytype[i] = "";
      	hotel.baseprice[i] = 0;
      	hotel.cap[i] = 0;
      	hotel.num_rooms[i] = 0;
      	break;
    	}
    	hotel.roomytype[i] = type[i];
    	hotel.baseprice[i] = baseprices[i];
    	hotel.cap[i] = cap[i];
    	hotel.num_rooms[i] = num_rooms[i];
    }

    keepHotel.write(reinterpret_cast<char *> (&hotel), sizeof(Hotels));

  }

  return 0;
}


void write(ostream& out, const Hotels& hotel)
{
	out << setw(30) << hotel.name << setw(20) << hotel.city << setw(5) << hotel.star << setw(5) << hotel.rate;
	for(int i = 0; i < 7; i++)
		out << setw(13) << hotel.roomytype[i] << setw(9) << setprecision(2) << hotel.baseprice[i] << setw(4) << hotel.cap[i] << setw(5) << hotel.num_rooms[i];

	out << endl;
}
