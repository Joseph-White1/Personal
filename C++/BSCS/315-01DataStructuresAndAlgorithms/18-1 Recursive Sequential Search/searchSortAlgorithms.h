#include<iostream>

using namespace std;

int recSeqSearch(int a[], int s, int i)
{
    if(i < 0)
        return -1;
    else if (a[i] == s)
        return i;
    else
        return recSeqSearch(a, s, i - 1);
}
