#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <cstring> 
#include <cctype>

using namespace std;

int smallestIndex(int numberArray[], int arraySize);

int main()
{
  int array[15];

  cout << "Enter 15 integers: " << endl;

  for(int i = 0; i < 15; i++)
    cin>>array[i];

  for(int i = 0; i < 15; i++)
    cout << array[i] << " ";
  
  int index = smallestIndex(array, 15);

  cout << "\nThe position of the first occurrence of the smallest element in list is: " << index << endl;
  cout << "The smallest element in list is: " << array[index] << endl;

  return 0;
}

int smallestIndex(int numberArray[], int arraySize)
{
    int smallest = 0;
    for (int i = 0; i < arraySize - 1; i++)
    {
        if (numberArray[smallest] > numberArray[i])
            smallest = i;
    }
    return smallest;
}


#include "studentType.h"
#include <iostream>

using namespace std;

studentType::studentType()
{
    // Initialize member variables to default values
    firstName = "";
    lastName = "";
    courseGrade = '\0';       // Initialize courseGrade to null character
    testScore = 0;
    programmingScore = 0;
    GPA = 0.0;
}

studentType::studentType(string firstName, string lastName, char courseGrade, int testScore, int programmingScore, double GPA)
{
    this->firstName = firstName;
    this->lastName = lastName;
    //this->courseGrade = courseGrade;
    this->testScore = testScore;
    this->programmingScore = programmingScore;
    setGrade();
    this->GPA = GPA;
}

// Setters
void studentType::setFirstName(string firstName)
{
    this->firstName = firstName;
}

void studentType::setLastName(string lastName)
{
    this->lastName = lastName;
}

//void studentType::setGrade(char courseGrade)
//{
//    this->courseGrade = courseGrade;
//}

void studentType::setGrade()
{
  int score = (testScore + programmingScore)/2;
  if(score >= 90)
    courseGrade = 'A';
  else if(score >= 80)
    courseGrade = 'B';
  else if(score >= 70)
    courseGrade = 'C';
  else if(score >=60)
    courseGrade = 'D';
  else
    courseGrade = 'F';
}

void studentType::setTestScore(int testScore)
{
    this->testScore = testScore;
}

void studentType::setProgScore(int programmingScore)
{
    this->programmingScore = programmingScore;
}

void studentType::setGPA(double GPA)
{
    this->GPA = GPA;
}

// Getters
string studentType::getFirstName()
{
    return firstName;
}

string studentType::getLastName()
{
    return lastName;
}

char studentType::getGrade()
{
    return courseGrade;
}

int studentType::getTestScore()
{
    return testScore;
}

int studentType::getProgScore()
{
    return programmingScore;
}

double studentType::getGPA()
{
    return GPA;
}

void studentType::print()
{
    cout << "Name: " << firstName << " " << lastName << endl;
    cout << "Grade: " << courseGrade << endl;
    cout << "Test Score: " << testScore << endl;
    cout << "Programming Score: " << programmingScore << endl;
    cout << "GPA: " << GPA << endl;
}
