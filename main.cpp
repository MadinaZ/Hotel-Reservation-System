#include <iostream>
#include<string>
#include<fstream>
#include<cstring>
#include "DynamicArray.h"
#include "Queue.h"
using namespace std;


struct Customer
{
    char Id;
    string City;
    string Star;
    int Budget;
    int ArrivalTime;
    int endTime;
};

struct Hotel
{
    string location;
    int price;
    string star;
    string rate;
    string name;
};

char getLetter(char &letter)
{
    letter++;
    if(letter  > 'Z')
        letter = 'A';
    return letter;
}

bool check_prefernces(const string city, const DynamicArray<Customer>& searching, int classIndex)
{
    for(int i = 0; i < classIndex; i++)
    {
        if(city == searching[i].City)
        {
            return true;
            // if(xbudget >= searching[i].Budget)
            // {
            //     return true;
            // }
        }
    }
    return false;
}

int main()
{

    Queue<Customer> waitLine;
    Queue<Hotel> hotel;
    DynamicArray<Customer> searching;
    DynamicArray<bool> serverStatus;
    Queue<Hotel> copy_hotel;
    Queue<Hotel> reserve;
    


    Customer client;
    Hotel h;
    fstream file;
    fstream user;
    int cust_num = 0;


    //    string fname, fstar, flocation, fprice, frate;

    int xbudget, xstay, xarrival;

    char *token;
    char buf[1000];
    int count;
    const char* const tab = "\t";

    char letter = 'Z';
    int classIndex = 0;

    user.open("User.txt");
    if(!user.good())
        cout<<"I/O error \n";
    while(user.good())
    {
        string line;
        getline(user, line);
        strcpy(buf, line.c_str());

        if(buf[0] == 0)//empty string
            continue;

        const string location (token = strtok(buf, tab));
        const string star((token = strtok(0, tab)) ? token : "");
        const string budget((token = strtok(0, tab)) ? token : "");
        const string rate((token = strtok(0, tab)) ? token : "");
        const string arrival((token = strtok(0, tab)) ? token : "");
        const string stayLength((token = strtok(0, tab)) ? token : "");

        client.Id = getLetter(letter);
        cout<<"Customer: "<<client.Id<<endl;
        cout<<"Enter the city: \n";
        cout<<location<<endl;
        client.City = location;
        cout<<"How many stars: \n";
        cout<<star<<endl;
        client.Star = star;
        cout<<"Enter the budget: \n";
        cout<<budget<<endl;
        xbudget = stoi(budget);
        client.Budget = xbudget;
        //        cout<<"The rate should be above: \n";
        //        cout<<rate<<endl;
        cout<<"What is the arrival time: \n";
        cout<<arrival<<" of November"<<endl;

        xarrival = stoi(arrival);
        client.ArrivalTime = xarrival;

        cout<<"Check out date? \n";
        cout<<stayLength<<" of November"<<endl;

        xstay = stoi(stayLength);
        client.endTime = xstay;
        waitLine.push(client);
        cout<<endl;
//        user.close();
        //--------------
        file.open("Hotel.txt");
        if(!file.good())
            cout<<"I/O error \n";

        while(file.good())
        {
            string line;
            getline(file,line);
            count++;
            strcpy(buf, line.c_str());


            if(buf[0] == 0)//empty string
                continue;
            const string fname (token = strtok(buf, tab));
            const string fstar((token = strtok(0, tab)) ? token : "");
            const string flocation((token = strtok(0, tab)) ? token : "");
            const string fprice((token = strtok(0, tab)) ? token : "");
            const string frate((token = strtok(0, tab)) ? token : "");
            int con_fprice = stoi(fprice);

            h.name = fname;
            h.price = con_fprice;
            h.rate = frate;
            h.star = fstar;
            h.location = flocation;
            hotel.push(h);
                        
            copy_hotel = hotel;
            reserve = hotel;
                if(waitLine.front().City == h.location)
                {
                    
                    if(waitLine.front().Budget >= h.price && waitLine.front().Star == h.star)
                    {
                        cout<<"Available options in "<<waitLine.front().City<<" are: "<<endl;
                        cout<<copy_hotel.front().name<<endl<<endl;
                        
                    }
                }
                else
                    continue;
                copy_hotel.pop();

            
        }//end of the hotel loop
        
        cout<<"Enter your choice \n";
        string input;
        cin>>input;

        if(input == reserve.front().name) //reserve
        {
            for(int i = waitLine.front().ArrivalTime; i != waitLine.front().endTime; i++)
            {
                serverStatus[i] = true;
            }
            cout<<"Succesfully booked \n";
        }
        else
            cout<<"Sorry, your booking is unavailable \n";
            
        reserve.pop();

        file.close();

    }//end of the user loop
    waitLine.pop();

    return 0;
}


