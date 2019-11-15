//
//  main.cpp
//  FINAL_PROJECT
//
//  Created by Madina Sadirmekova on 11/8/19.
//  Copyright © 2019 Madina Sadirmekova. All rights reserved.
// Plan:
//   1)we are going to get user preference
//   2)based on that do sorting
//   3)display the options
//   4)optinons are based on index, we let the user choose the index, thus reserve it
//   5)I thought it will be better to let the reservation be only for two weeks with 10 customers
//       But entering 10 people's data seems time consuming, so probaly will randomly generate their choices.
//       Or I will creat different text file with already exisitng data

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
    int Budget;
    int ArrivalTime;
    int endTime;
    int StayLength;
};

//struct Time
//{
//
//};

char getLetter(char &letter)
{
    letter++;
    if(letter  > 'Z')
        letter = 'A';
    return letter;
}

bool check_prefernces(const string city, const int xbudget, const DynamicArray<Customer>& searching, int classIndex)
{
    for(int i = 0; i < classIndex; i++)
    {
        if(city == searching[i].City)
        {
            if(xbudget >= searching[i].Budget)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{

    srand(time(0));
    rand();
    
    Queue<Customer> waitLine;
    DynamicArray<Customer> searching;
    DynamicArray<bool> serverStatus;
    Customer client;

    fstream file;
    fstream user;
    int cust_num = 0;
    

    string fname, fstar, flocation, fprice, frate;

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
        cout<<"Customer: "<<client.Id<<endl;
        cout<<"Enter the city: \n";
        cout<<location<<endl;
        cout<<"How many stars: \n";
        cout<<star<<endl;
        cout<<"Enter the budget: \n";
        cout<<budget<<endl;
        xbudget = stoi(budget);
        
//        cout<<"The rate should be above: \n";
//        cout<<rate<<endl;
        cout<<"What is the arrival time: \n";
        cout<<arrival<<" of November"<<endl;
        
        xarrival = stoi(arrival);
//        time.ArrivalTime = xarrival;
        
        cout<<"What is your stay length? \n";
        cout<<stayLength<<" days"<<endl;
        
        xstay = stoi(stayLength);
//        time.stayLength = xstay;
              
    }
    
    file.open("simulation.txt");
    if(!file.good())
        cout<<"I/O error \n";
    while(file.good())
    {
        getline(file,fname, '\n');
        getline(file,fstar, '\n');
        getline(file,flocation, '\n');
        getline(file,fprice, '\n');
        getline(file,frate, '\n');
        cust_num++;
    }

    for(int time = 0; ;time++)
    {
        for(int i = 0; i < cust_num; i++)
        {
            if(!serverStatus[i])
            {
                if(searching[i].endTime == time)
                    serverStatus[i] = true;
                searching[i].Id = ' ';
            }
        }
    }
    return 0;
}

