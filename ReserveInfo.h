#ifndef RESERVEINFO_H
#define RESERVEINFO_H

#include <string>
using namespace std;

class ReserveInfo
{
  int customerNum;
 // int roomNum
  int startDate;
  int endDate;
  char roomChar[50];

public:
  ReserveInfo():customerNum(),startDate(22),endDate(),roomChar(){};
  ReserveInfo(int a,int b,int c, const string& room);

  friend bool operator<(const ReserveInfo& a, const ReserveInfo& b) { return (a.endDate < b.endDate); }
  ReserveInfo& operator=(const ReserveInfo& ori);
 // friend const ReserveInfo& operator[](int) const;
  //friend ReserveInfo& operator[]();

  void setCusNum(int a) { this->customerNum = a; }
  void setStartDate(int a) { this->startDate = a; }
  void setEndDate(int a) { this->endDate = a; }
  void setRoomChar(const string&);

  int getCusNum() const { return customerNum; }
  int getStartDate() const { return startDate; }
  int getEndDate() const { return endDate; }
  string getRoomChar() const { return roomChar; }

};
/*
ReserveInfo::ReserveInfo(const ReserveInfo& ori)
{
	this->customerNum = ori.getCusNum();
	this->roomNum = ori.getRoomNum();
	this->startDate = ori.getStartDate();
	this->endDate = ori.getEndDate();
}
*/

ReserveInfo::ReserveInfo(int a,int b,int c, const string& room)
:customerNum(a)
,startDate(b)
,endDate(c)
{
	setRoomChar(room);
}

ReserveInfo& ReserveInfo::operator=(const ReserveInfo& ori)
{
	if(this == &ori) return *this;

	setCusNum(ori.getCusNum());
	setRoomChar(ori.getRoomChar());
	setStartDate(ori.getStartDate());
	setEndDate(ori.getEndDate());

	return *this;
}

void ReserveInfo::setRoomChar(const string& a)
{
	int length = (int)a.size();
	length = (length < 50 ? length : 49); // not necessary, but just in case
	a.copy(this->roomChar, length);
	this->roomChar[length] = '\0';
}




#endif
