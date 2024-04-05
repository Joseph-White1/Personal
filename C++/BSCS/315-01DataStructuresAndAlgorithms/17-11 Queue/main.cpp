#include <iostream>
#include "queueAsArray.h"

using namespace std;

int main()
{
    queueType<int> intQueue;

    intQueue.isEmptyQueue();
    if(intQueue.isEmptyQueue() == 1)
        cout << "Queue is empty" << endl;
    else
        cout << "Queue is not empty" << endl;

    intQueue.addQueue(5);
    intQueue.addQueue(11);
    intQueue.addQueue(34);
    intQueue.addQueue(42);
    intQueue.addQueue(58);    
    
    cout << "\nQueue: ";
    intQueue.print();

    intQueue.isEmptyQueue();
    if(intQueue.isEmptyQueue() == 1)
        cout << "Queue is empty" << endl;
    else
        cout << "Queue is not empty" << endl;
    
    intQueue.isFullQueue();
    if(intQueue.isEmptyQueue() == 1)
        cout << "Queue is full" << endl;
    else
        cout << "Queue is not full" << endl;
    cout << endl;

    cout << "Front element: "  << intQueue.front()  << endl;
    cout << "Back element: "  << intQueue.back()  << endl;
    
    intQueue.deleteQueue();
    cout << "\nQueue after deleting front element: ";
    intQueue.print();

    cout << "Front element: "  << intQueue.front()  << endl;
    cout << "Back element: "  << intQueue.back()  << endl;

    queueType<int> copyQueue(intQueue);

    cout << "\nCopy Queue: ";
    copyQueue.print();
    cout << "Copy front element: "  << intQueue.front()  << endl;
    cout << "Copy back element: "  << intQueue.back()  << endl;

    // testing assignment operator
    queueType<int> assignOp = intQueue;

    cout << "\nAssignment operator queue: ";
    assignOp.print();
    cout << "Assignment operator front element: " << assignOp.front() << endl;
    cout << "Assignment operator back element: " << assignOp.back() << endl;

    cout << "\nAdd '101' to Assignment operator queue\n";
    assignOp.addQueue(101);

    cout << "Assignment operator queue: ";
    assignOp.print();
    cout << "Assignment operator front element: " << assignOp.front() << endl;
    cout << "Assignment operator back element: " << assignOp.back() << endl;

    cout << "\nQueue: ";
    intQueue.print();
    cout << "Front element: " << intQueue.front() << endl;
    cout << "Back element: " << intQueue.back() << endl;

    return 0;
}
