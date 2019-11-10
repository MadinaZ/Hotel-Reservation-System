//
//  main.cpp
//  FINAL_PROJECT
//
//  Created by Madina Sadirmekova on 11/8/19.
//  Copyright © 2019 Madina Sadirmekova. All rights reserved.
//
    Plan:
    1)we are going to get user preference
    2)based on that do sorting
    3)display the options
    4)optinons are based on index, we let the user choose the index, thus reserve it
    5)I thought it will be better to let the reservation be only for two weeks with 10 customers
        But entering 10 people's data seems time consuming, so probaly will randomly generate their choices.
        Or I will creat different text file with already exisitng data
    And sorry I did not have time, to focus on project since recently I have registered for another class and had midterm yesterday :(
        
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

    string fname, fstar, flocation, fprice, frate;
    int budget, cust_num, star, sstar, sprice;
    char *location, *slocation, *sname;
    double rate, srate;
    char letter = 'Z';
    cust_num = 5;
    

    for(int i = 0; i < cust_num; i++)
    {
        client.id = getLetter(letter);
        cout<<"Customer: "<<client.id<<endl;
        cout<<"Enter the city: \n";
        cin>>location;
        cout<<"How many stars: \n";
        cin>>star;
        cout<<"Enter the budget: \n";
        cin>>budget;
        cout<<"The rate should be above: \n";
        cin>>rate;
        cout<<"How the arrival time: \n";
        cin>>client.ArrivalTime;
        cout<<"What is your stay length? \n";
        cin>>client.stayLength;
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
        
        sstar= stoi(fstar);
        srate = stof(frate);
        int n1 = (int)fname.length();
        int n2 = (int)flocation.length();
        char Name[n1 + 1];
        strcpy(Name, fname.c_str());
        char Location[n2 + 1];
        strcpy(Location, flocation.c_str());

    }

    
    return 0;
}
