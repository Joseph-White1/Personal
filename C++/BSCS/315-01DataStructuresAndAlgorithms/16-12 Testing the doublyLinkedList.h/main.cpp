#include <iostream>
#include "doublyLinkedList.h"

using namespace std;

void testCopyConstructor(doublyLinkedList<int> list);

int main()
{
	doublyLinkedList<int> intList, temp;
	int num;
	
	cout << "Enter a list of positive integers ending with -999: " << endl;
	cin >> num;
	
	while (num != -999)
	{
		intList.insert(num);
		cin >> num;
	}
	cout << endl;
	
	cout << "List in ascending order: ";
	intList.print();
	cout << endl;
	
	cout << "List in descending order: ";
	intList.reversePrint();
	cout << endl;
	
	cout << "Enter element to be deleted: ";
	cin >> num;
	cout << endl;
	
	intList.deleteNode(num);
	cout << "List after deleting '" << num << "': ";
	intList.print();
	cout << endl;
	
	cout << "Enter element to be searched: ";
	cin >> num;
	cout << endl;
    if (intList.search(num))
        cout << "'" << num << "' found in the list." << endl;
    else
        cout << "'" << num << "' is not found in the list." << endl;
	
	cout << "***********Testing copy constructor***********" << endl;
	testCopyConstructor(intList);
	cout << "intList: ";
	intList.print();
	cout << endl;
	temp.destroy();
	
	cout << "\n**********Testing assignment operator*********" << endl;
	temp = intList;
	cout << "temp: ";
	intList.print();
	cout << endl;
	return 0;
}

void testCopyConstructor(doublyLinkedList<int> list) {}
