#include "dateType.h"
#include <iostream>

using namespace std;

int main()
{
    int month, day, year;

    cout << "Date #: ";
    cin >> month >> day >> year;

    dateType date(month, day, year);
    
    cout << "Date 1: ";
    date.printDate();
    cout << endl;
    
    if(date.isLeapYear())
    {
        cout<<"This is a leap year\n";
    }
    else
    {
        cout<<"This is not a leap year\n";
    }
    
    return 0;
}
