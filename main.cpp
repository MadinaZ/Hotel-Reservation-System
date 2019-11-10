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

#include<iostream>
#include<string>
using namespace std;
#include "Queue.h"
#include "DynamicArray.h"
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<cmath>


struct Customer
{
    char id;
    int ArrivalTime;
    int stayLength;
};

int getRandomNumberOfArrivals(double averageArrivalRate)
{
    int arrivals = 0;
    double probOfnArrivals = exp(-averageArrivalRate);
    for(double randomValue = (double)rand( ) / RAND_MAX; (randomValue -= probOfnArrivals) > 0.0; probOfnArrivals *= averageArrivalRate / static_cast<double>(++arrivals));
    return arrivals;
}

char getLetter(char &letter)
{
    letter++;
    if(letter  > 'Z')
        letter = 'A';
    return letter;
}

int main() {

    srand(time(0));
    rand();
    
    Queue<Customer> waitLine;
    DynamicArray<Customer> serving;
    DynamicArray<bool> serverStatus;
    Customer client;

    fstream file;
    fstream user;
    

    string fname, fstar, flocation, fprice, frate;

    int sstar, sprice, xarrival, xstay;
    double srate, xrate;
    
    char *token;
    char buf[1000];
    const char* const tab = "\t";
    
    char letter = 'Z';
    int cust_num = 10;
    
    int size = 10;
    
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
        
        client.id = getLetter(letter);
        cout<<"Customer: "<<client.id<<endl;
        cout<<"Enter the city: \n";
        cout<<location<<endl;
        cout<<"How many stars: \n";
        cout<<star<<endl;
        cout<<"Enter the budget: \n";
        cout<<budget<<endl;
        cout<<"The rate should be above: \n";
        cout<<rate<<endl;
        cout<<"How the arrival time: \n";
        cout<<arrival<<" of November"<<endl;
//        xarrival = stoi(arrival);
//        client.ArrivalTime = xarrival;
        cout<<"What is your stay length? \n";
        cout<<stayLength<<" days"<<endl;
//        xstay = stoi(stayLength);
//        client.stayLength = xstay;
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
    }

    return 0;
}

