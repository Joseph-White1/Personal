#include <iostream>

using namespace std;

int main()
{
    char auth, letter;
    int i = 0, count = 0;
    
    cout << "Enter Y/y to convert a telephone number from letters to digits." << endl
    << "Enter any other letter to terminate the program." << endl;
    cin >> auth;

    while (auth == 'y' || auth == 'Y')
    {

        cout << "Enter a telephone number using letters: ";
        
        while (cin.get(letter) && count < 7 )
        {
            
            if (letter != ' ' && letter >= 'A' && letter <= 'z')
            {
                count++;
                if (letter > 'Z')
                {
                    letter = static_cast<int>(letter)-32;
                }
                
                if (count == 4)
                {
                    cout << "-";
                }
                
                if (i == 0)
                {
                    cout << "\nThe corresponding telephone number is: " << endl;
                    i++;
                }

                switch (letter)
                {
                    case 'A':
                    case 'B':
                    case 'C':
                        cout << "2";
                        break;
                    case 'D':
                    case 'E':
                    case 'F':
                        cout << "3";
                        break;
                    case 'G':
                    case 'H':
                    case 'I':
                        cout << "4";
                        break;
                    case 'J':
                    case 'K':
                    case 'L':
                        cout << "5";
                        break;
                    case 'M':
                    case 'N':
                    case 'O':
                        cout << "6";
                        break;
                    case 'P':
                    case 'Q':
                    case 'R':
                    case 'S':
                        cout << "7";
                        break;
                    case 'T':
                    case 'U':
                    case 'V':
                        cout << "8";
                        break;
                    case 'W':
                    case 'X':
                    case 'Y':
                    case 'Z':
                        cout << "9";
                        break;
                    default:
                        break;
                }
            }   
        }
    
    cin.ignore(1000, '\n');

    cout << "\nTo process another telephone number, enter Y/y" << endl
    << "Enter any other letter to terminate the program." << endl;
    
    i = 0;
    count = 0;
    cin >> auth;  
    
    }
     
    return 0;
}