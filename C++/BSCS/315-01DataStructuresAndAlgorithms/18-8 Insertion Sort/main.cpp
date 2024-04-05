#include <iostream>
#include "searchSortAlgorithms.h"

using namespace std;

void print(int array[], int length);

int main()
{
    int i, array[10];

    cout << "Enter 10 integers: ";

    for (i = 0; i < 10; ++i) 
    {
        cin >> array[i];
    }

    cout << "Array before sorting: ";
    print(array, 10);

    insertionSort(array, 10);
    cout << "Array after sorting: ";
    print(array, 10);
    return 0;
}

void print(int array[], int length)
{
    int i;
    for (i = 0; i < length; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}
