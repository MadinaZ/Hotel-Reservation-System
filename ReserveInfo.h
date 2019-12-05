#ifndef RESERVEINFO_H
#define RESERVEINFO_H

class ReserveInfo
{
  int customerNum;
	int roomNum;
  int startDate;
  int endDate;

public:
  ReserveInfo():customerNum(),roomNum(),startDate(22),endDate(){};
  ReserveInfo(int a,int b,int c):customerNum(a),roomNum(b),startDate(c),endDate(){};

  ReserveInfo& operator=(const ReserveInfo&);
  friend bool operator<(const ReserveInfo& a, const ReserveInfo& b) { return (a.endDate < b.endDate); }

  void setCusNum(int);
  void setRoomNum(int);
  void setStartDate(int);
  void setEndDate(int);

  int getCusNum() { return customerNum; }
  int getRoomNum() { return roomNum; }
  int getStartDate() { return startDate; }
  int getEndDate() { return endDate; }

};

ReserveInfo& ReserveInfo::operator=(const ReserveInfo& ori)
{
	if(this == &ori) return *this;

	startDate = ori.startDate;
	endDate = ori.endDate;
	customerNum = ori.customerNum;

	return *this;
}

void ReserveInfo::setCusNum(int a)
{
	this->customerNum = a;
}

#endif
