
#include <iostream>
#include "searchSortAlgorithms.h"     

using namespace std;

int main()
{ 
    int search, result, list[10] = {0,2,4,6,8,1,3,5,7,9};
    const int length = 10;

    cout << "Enter an element to search for: ";
    cin >> search;
                   
    result = recSeqSearch(list, search, length);
    if (result == -1)
        cout << "Element '" << search << "' not found in list" << endl;
    else
        cout << "Element '" << search << "' found at location " << result << endl;
    
    return 0;
}
