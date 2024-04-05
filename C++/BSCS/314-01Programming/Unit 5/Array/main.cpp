//Data: 21 10 56 43 78 11 20 18

#include <iostream>
#include "unorderedArrayListType.h"

using namespace std;

int main()
{
  unorderedArrayListType myArray;
  int n,i=0;

  while (i != 8)
    {
      cout<<"Number:";
      cin >> n;
      myAry.insertEnd(n);
      i++;
    }
  cout << "location:";
  cin >> n;
  cout << myAry.retrieveAt(n) << endl;

  return 0;
}