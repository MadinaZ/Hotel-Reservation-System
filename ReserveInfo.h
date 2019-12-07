#ifndef RESERVEINFO_H
#define RESERVEINFO_H

class ReserveInfo
{
  int customerNum;
  int roomNum;
	//char roomChar[45];
  int startDate;
  int endDate;

public:
  ReserveInfo():customerNum(),roomNum(),startDate(22),endDate(){};
  ReserveInfo(int a,int b,int c, int d):customerNum(a),roomNum(b),startDate(c),endDate(d){};

  friend bool operator<(const ReserveInfo& a, const ReserveInfo& b) { return (a.endDate < b.endDate); }
  ReserveInfo& operator=(const ReserveInfo& ori);
 // friend const ReserveInfo& operator[](int) const;
  //friend ReserveInfo& operator[]();

  void setCusNum(int);
  void setRoomNum(int);
  void setStartDate(int);
  void setEndDate(int);

  int getCusNum() const { return customerNum; }
  int getRoomNum() const { return roomNum; }
  int getStartDate() const { return startDate; }
  int getEndDate() const { return endDate; }

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

ReserveInfo& ReserveInfo::operator=(const ReserveInfo& ori)
{
	if(this == &ori) return *this;

	this->customerNum = ori.getCusNum();
	this->roomNum = ori.getRoomNum();
	this->startDate = ori.getStartDate();
	this->endDate = ori.getEndDate();

	return *this;
}

void ReserveInfo::setCusNum(int a)
{
	this->customerNum = a;
}

void ReserveInfo::setRoomNum(int a)
{
	this->roomNum = a;
}

void ReserveInfo::setStartDate(int a)
{
	this->startDate = a;
}

void ReserveInfo::setEndDate(int a)
{
	this->endDate = a;
}



#endif
