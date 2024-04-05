#include "dateType.h"
#include <iostream>
#include <iomanip>
 
using namespace std;

int maxDays;

void dateType::setDate(int month, int day, int year)
{
    this->month = month;
    this->day = day;
    this->year = year;
}


int dateType::getDay() const
{
	  return day;
}
 
int dateType::getMonth() const
{
	  return month;
}
 
int dateType::getYear() const
{
	  return year;
}
 
void dateType::printDate() const
{
	  cout << month << "-" << day << "-" << year;
}
 
bool dateType::isLeapYear()
{
	if(year % 4 == 0 && (year % 100 || year % 400 == 0))
	{
      return true;
	}
	
	return false;
}

dateType::dateType(int month, int day, int year)
{
    if(year < 0 || year > 9999)
    {
        cout << "Invalid date" << endl;
        this->year = 0;
        this->month = 0;
        this->day = 0;
    }
    else if (month < 1 || month > 12)
    {
        this->month = 1;
        this->day = day;
        this->year = year;
    }
    else
    {
        this->year = year;
        this->month = month;
        this->day = day;

        switch(month)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12: 
              maxDays = 31;
              break;
            case 4:
            case 6:
            case 9:
            case 11: 
              maxDays = 30;
              break;
            case 2:
              if(isLeapYear())
                maxDays = 29;
              else
                maxDays = 28;
              break;
        }
        if(day < 1 || day > maxDays)
        {
            this->day = 1;
        }
    }
}
