#include "myStack.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    stackType<int> stack1(12);
    stackType<int> stack2(15);

    cout << "\nPush elements into both stacks.";
    for (int i = 0; i < 20; i += 2)
    {
        stack1.push(i);
        stack2.push(i);
    }

    if (stack1 == stack2)
        cout << "\nBoth the stacks are equal" << endl;
    else
        cout << "\nBoth the stacks are not equal" << endl;

    int insert = 5;
    cout << "\nPush element '" << insert << "' to stack 2.";
    stack2.push(insert);

    if (stack1 == stack2)
        cout << "\nBoth the stacks are equal" << endl;
    else
        cout << "\nBoth the stacks are not equal" << endl;

    cout << "\nRemove top element from stack 2";
    stack2.pop();

    if (stack1 == stack2)
        cout << "\nBoth the stacks are equal" << endl;
    else
        cout << "\nBoth the stacks are not equal" << endl;

    return 0;
}
