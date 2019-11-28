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
    Queue<Customer> copy;
    DynamicArray<Hotel> hotel;
    DynamicArray<Customer> searching;
    DynamicArray<bool> serverStatus;
    
    Customer client;
    Hotel h;
    fstream file;
    fstream user;
    int cust_num = 0;
    int index = 0;
    
    //    string fname, fstar, flocation, fprice, frate;
    
    int xbudget, xstay, xarrival;
    
    char *token;
    char buf[1000];
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
        client.City = location;
        client.Star = star;
        xbudget = stoi(budget);
        client.Budget = xbudget;
        xarrival = stoi(arrival);
        client.ArrivalTime = xarrival;
        xstay = stoi(stayLength);
        client.endTime = xstay;
        waitLine.push(client);
        cout<<endl;
        //        user.close();
    }//end of the user loop
    copy = waitLine;
    //--------------
    file.open("Hotel.txt");
    if(!file.good())
        cout<<"I/O error \n";
    
    
    while(file.good())//hotel
    {
        string line;
        getline(file,line);
        strcpy(buf, line.c_str());
        
        
        if(buf[0] == 0)//empty string
            continue;
        const string fname (token = strtok(buf, tab));
        const string fstar((token = strtok(0, tab)) ? token : "");
        const string flocation((token = strtok(0, tab)) ? token : "");
        const string fprice((token = strtok(0, tab)) ? token : "");
        const string frate((token = strtok(0, tab)) ? token : "");
        int con_fprice = stoi(fprice);
        
        hotel[index].name = fname;
        hotel[index].price = con_fprice;
        hotel[index].rate = frate;
        hotel[index].star = fstar;
        hotel[index].location = flocation;
        index++;
    }
    
    int print = 0;
    while(!waitLine.empty())
    {
        cout<<"Customer: "<<waitLine.front().Id<<endl;
        cout<<"Enter the city: \n";
        cout<<waitLine.front().City<<endl;
        cout<<"How many stars: \n";
        cout<<waitLine.front().Star<<endl;
        cout<<"Enter the budget: \n";
        cout<<waitLine.front().Budget<<endl;
        //        cout<<"The rate should be above: \n";
        //        cout<<rate<<endl;
        
        cout<<"What is the arrival time: \n";
        cout<<waitLine.front().ArrivalTime<<" of November"<<endl;
        cout<<"Check out date? \n";
        cout<<waitLine.front().endTime<<" of November"<<endl;

cout<<"Available options in "<<waitLine.front().City<<" are: "<<endl;
        
        for(int i = 0; i < index; i++)
        {
            if(waitLine.front().City == hotel[i].location)
            {
                if(waitLine.front().Budget >= hotel[i].price && waitLine.front().Star == hotel[i].star)
                {
                    cout<<hotel[i].name<<endl<<endl;
                }
            }
            else
                break;
        }
        
        cout<<"Enter your choice \n";
        string input;
        cin>>input;
        for(int i = 0; i < index; i++)
        {
            if(input == hotel[i].name) //reserve//can I compare two strings like that?
            {
                for(int i = waitLine.front().ArrivalTime; i != waitLine.front().endTime; i++)
                {
                    serverStatus[i] = true;
                }
                cout << "hello";

                print = 1;
            }
            else
            {
                print = 0;
                continue;
            }
            
            if(print == 1)
            cout<<"Succesfully booked \n";
            else if (print == 0)
            cout<<"Sorry, your booking is unavailable \n";
        }
        waitLine.pop();
    }
    
    file.close();
    return 0;
}

