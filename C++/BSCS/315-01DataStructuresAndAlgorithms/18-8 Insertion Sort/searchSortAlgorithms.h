#include <iostream>

using namespace std;

template <class elemType>
void insertionSort(elemType list[], int length)
{
    for (int preSort = 1; preSort < length; preSort++)
    if (list[preSort] < list[preSort - 1])
    {
        elemType temp = list[preSort];
        int location = preSort;

        do
        {
            list[location] = list[location - 1];
            location--;
        }
        while(location > 0 && list[location - 1] > temp);

        list[location] = temp;
    }
}