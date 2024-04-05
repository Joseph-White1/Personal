#include <iostream>
#include "graphType.h"

using namespace std;

int main()
{
    graphType g(50);

    g.createGraph(); 

    g.depthFirstTraversal();
    cout << endl;

    return 0;
}
