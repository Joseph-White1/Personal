#include <iostream>
#include "arrayListType.h"
#include "unorderedArrayListType.h"

using namespace std;

int main()
{
    int x = 0;

    unorderedArrayListType<int> list(7);
        cout << "\nList size : " << list.listSize() << endl;
        cout << "Max list size: " << list.maxListSize() << endl;

    list.insertAt(0, 1);
    list.insertAt(1, 3);
    list.insertAt(2, 5);
    list.insertEnd(8);
    list.insertEnd(11);
    list.insertEnd(34);
    list.insertEnd(42);

    cout << "\nList: ";
    list.print();
        cout << endl;

    int searchItem = 5;
    int searchResult = list.seqSearch(searchItem);
    if (searchResult != -1)
        cout << "\nElement '" << searchItem << "' found at location " << searchResult << endl;
    else
        cout << searchItem << " not found in the list." << endl;

    int retLoc = 0;
    list.retrieveAt(retLoc, x);
    cout << "\nElement '" << x << "' retrieved from location " << retLoc << endl;

    int replaceWith = 58;
    int replaceLocation = 6;
    list.replaceAt(replaceLocation, replaceWith);
        cout << "\nList after replacing the element at location " << replaceLocation << " with '" << replaceWith << "': ";
    list.print();
        cout << endl;

    int inserted = 99;
        cout << "\nInsert an eighth element: " << inserted << endl;
    list.insertEnd(inserted);

    int removeItem = 8;
    list.remove(removeItem);
        cout << "\nList after removing the element '" << removeItem << "': ";
    list.print();

    list.clearList();
        cout << "\nList after clearing: ";
    list.print();
        cout << endl;


    return 0;
}
