#ifndef HOTELS_H
#define HOTELS_H

struct Hotels
{
  char name[30];
  char city[20];
  int star;
  double rate;
  char type1[10];
  char type2[10];
  char type3[10];
  char type4[10];
  char type5[10];
  char type6[10];
  char type7[10];
  double baseprice[7];
  int cap[7];
  int num_rooms[7];

  Hotels();
};

Hotels::Hotels()
:name("")
,city("")
,star(0)
,rate(0)
,type1("")
,type2("")
,type3("")
,type4("")
,type5("")
,type6("")
,type7("")
{}

#endif
