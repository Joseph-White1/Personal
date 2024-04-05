#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const double conversion = 2.54;
const int inchesInFoot = 12;
double getLength();

int main()
{

    double feet;
    double inches;
    double centimeters;

    cout << fixed << showpoint << setprecision(2);
    cout << "Enter a length in feet: ";
    feet = getLength();
    cout << endl;

    cout << "Enter a length in inches: ";
    inches = getLength();
    cout << endl;

    centimeters = (inchesInFoot * feet + inches) * conversion;
    cout << "Centimeter: " << centimeters << endl;

    return 0;

}

double getLength()

{
    string str = "A non positive number is entered";
    double number;
    bool done = false;

    do
    {
        try
        {
            cin >> number;

            if (cin.fail() || number < 0)
              throw str;

            done = true;
        }

        catch (string messageStr)
        {
            cout << messageStr << endl;
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Enter a nonnegative integer: ";
        }

    }
    while (!done);

    return number;
}
