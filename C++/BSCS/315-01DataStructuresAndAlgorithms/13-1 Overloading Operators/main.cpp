#include <iostream>
#include "rectangleType.h"

using namespace std;

int main()
{
    rectangleType yard1(5, 3);
    rectangleType yard2(20, 15);
    rectangleType yard3 = yard1 + yard2;
    rectangleType yard4 = yard1 * yard2;

    cout << "Yard #1: " << yard1 << endl;
    cout << "Yard #2: " << yard2 << endl;

    cout << "Yard #1 + #2: " << yard3 << endl;
    cout << "Yard #1 * #2:  " << yard4 << endl;

    if (yard1 == yard2)
      cout << "Area of #1 is equal to the area of #2." << endl;
    else if(yard1 > yard2)
      cout << "Area of #1 is greater than the area of #2." << endl;
    else
      cout << "Area of yard #1 is less than the area of yard #2." << endl;

    yard1++;
    cout << "Yard #1 incremented by one unit is: " << yard1 << endl;

    return 0;
}
