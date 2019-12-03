#include <iostream>
#include<string>
#include<fstream>
#include<cstring>
#include<algorithm>
using namespace std;

#include "DynamicArray.h"
#include "Queue.h"
#include "AssociativeArray.h"

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
    int num;
    string location;
    int price;
    string star;
    string rate;
    string name;
    //bool status[14];
    DynamicArray<bool> status;
};

char getLetter(char &letter)
{
    letter++;
    if(letter  > 'Z')
        letter = 'A';
    return letter;
}

bool boolreserve1(string input, DynamicArray<Hotel>& hotel, Queue<Customer>& waitLine)
{
    for(int i = 0; i < hotel.capacity(); i++)
    {
        if(strcmp(input.c_str(),hotel[i].name.c_str()) == 0)
            return true;
    }
    return false;
}

int reserve1(string input,DynamicArray<Hotel>& hotel, Queue<Customer>& waitLine)
{
    for(int i = 0; i < hotel.capacity(); i++)
    {
        if(strcmp(input.c_str(),hotel[i].name.c_str()) == 0)
            return i;
    }
    return 0;
}

int reserve2(Queue<Customer>& waitLine, DynamicArray<Hotel>& hotel, int index2)
{
    int calc = 0;
//    cout<<waitLine.front().ArrivalTime<<"---"<<waitLine.front().endTime<<endl;
    for(int i = waitLine.front().ArrivalTime; i <= waitLine.front().endTime; i++)
    {
        if(hotel[index2].status[i])//pomenyala
            calc++;
    }
    int result = waitLine.front().endTime - waitLine.front().ArrivalTime + 1;
//    cout<<"calc is: "<<calc<<"result: "<<result<<endl;
    if(calc == result)
        return 1;
    
    return 0;
}

void reserve3(DynamicArray<Hotel>& hotel, Queue<Customer>& waitLine, int index2)
{
    for(int j = waitLine.front().ArrivalTime; j <= waitLine.front().endTime; j++)
    {
        if(hotel[index2].status[j] == false)//POM
            hotel[index2].status[j] = true;//POM
        else
            break;
    }
}

bool reserve4(DynamicArray<Hotel>& hotel, Queue<Customer>& waitLine, int index)
{
    int calc = 0;
    for(int j = waitLine.front().ArrivalTime; j <= waitLine.front().endTime; j++)
    {
        if(!hotel[index].status[j])//POM
            calc++;
    }
    int result = waitLine.front().endTime - waitLine.front().ArrivalTime + 1;
    if(calc == result)
        return true;

    return false;
}

bool check_city(int index, const DynamicArray<Hotel>& hotel, const Queue<Customer> waitLine)
{
    for(int i = 0; i < index; i++)
    {
        if(waitLine.front().City == hotel[i].location)
            return true;
    }
    return false;
}

//void display(int index, const DynamicArray<Hotel>& hotel, const Queue<Customer> waitLine)
//{
//    for(int i = 0; i < index; i++)
//    {
//        if(waitLine.front().Budget >= hotel[i].price && waitLine.front().Star == hotel[i].star)
//        {
//            if(reserve4(hotel, waitLine, index))
//                cout<<hotel[i].name<<endl<<endl;
//        }
//    }
//}

int main()
{
    Queue<Customer> waitLine;
    DynamicArray<Hotel> hotel;
    DynamicArray<Customer> customer;
    Customer client;
    Hotel h;
    fstream file;
    fstream user;
    int index = 0;
    int j = 0;

    int xbudget, xstay, xarrival;
    
    char *token;
    char buf[1000];
    const char* const tab = "\t";
    
    char letter = 'Z';
    
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
        
        customer[j].City = location;
        customer[j].Star = star;
        customer[j].Budget = xbudget;
        customer[j].ArrivalTime = xarrival;
        customer[j].endTime = xstay;
        
        j++;
        waitLine.push(client);
        cout<<endl;
        //        user.close();
    }//end of the user loop
    //---------------------
    file.open("Hotel.txt");
    if(!file.good())
        cout<<"I/O error \n";
    
    string str;
    cout<<"If you would like to use a search bar press 1 \n";
    cout<<"If you would like us to reserve a hotel based on your preferences press 2 \n";
    cin>>str;
    
    if(str[0] == '2')
    {
        
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
        
        string Ucity,Ustar, Ubudget, UarrTime, UendTime;
        cout<<"Enter the city: \n";
        cin>>Ucity;
        cout<<"How many stars: \n";
        cin>>Ustar;
        cout<<"Enter the budget: \n";
        cin>>Ubudget;
        cout<<"What is the arrival time: \n";
        cin>>UarrTime;
        cout<<"Check out date? \n";
        cin>>UendTime;
        user<<Ucity<<tab<<Ustar<<tab<<Ubudget<<tab<<UarrTime<<tab<<UendTime<<"\n";
        
        while(!waitLine.empty())//user
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
            
            if(check_city(index, hotel, waitLine) == true)
            {
                cout<<"Available options in "<<waitLine.front().City<<" are: "<<endl;
                //                display(index, hotel, waitLine);
                for(int i = 0; i < index; i++)
                {
                    if(waitLine.front().Budget >= hotel[i].price && waitLine.front().Star == hotel[i].star)
                    {
                        if(reserve4(hotel, waitLine, index))
                            cout<<hotel[i].name<<endl<<endl;
                    }
                }
                cout<<"Enter your choice \n";
                string input;
                cin>>input;
                
                if(boolreserve1(input,hotel,waitLine) == true)
                {
                    int index2 = reserve1(input, hotel, waitLine);
                    reserve3(hotel, waitLine, index2);
                    int result = reserve4(hotel, waitLine, index2);
                    
                    
                    if(result == 1)
                        cout<<endl<<"Succesfully booked \n";
                    else if (result == 0)
                        cout<<"\n Sorry, your booking is unavailable \n";
                }
                
            }
            else
                cout<<endl<<"Nothing found"<<endl<<endl;
            
            waitLine.pop();
        }
        
    }
    file.close();
    return 0;
}


