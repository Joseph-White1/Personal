#include "counterType.h"
#include <iostream>

using namespace std;

counterType::counterType(int counter)
{
    this->counter = counter;
}

void counterType::setCounter(int counter)
{
    if (counter < 0)
      counter = 0;
    this->counter = counter;
}

int counterType::getCounter()
{
    return counter;
}

void counterType::incrementCounter()
{
    counter++;
}

void counterType::decrementCounter()
{
    counter--;
}

void counterType::print()
{
    cout << "Counter = " << counter << endl;
}
