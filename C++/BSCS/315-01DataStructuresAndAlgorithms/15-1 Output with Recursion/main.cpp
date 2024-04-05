#include <iostream>

using namespace std;

void printStars(int lines);

int main()
{
    int lines;

    cout << "Enter the number of lines desired in the pattern: ";
    cin >> lines;
    cout << endl;

    printStars(lines);

    return 0;
}

void printStars(int lines)
{
    if(lines <= 0)
    {
        return ;
    }

    int i;

    for(i = 0; i < lines; i++)
        cout << "*";

    cout << endl;
    printStars(lines-1);
    
    for(i = 0; i < lines; i++)
        cout << "*";

    cout << endl;
}
