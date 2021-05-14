#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <random>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75

//void CreateRandomBinDataset(string dir, int size);

using namespace std;

int main()
{
    string aboab;
    cout << cin.peek() << '\t';
    while (1)
    {
        
        _getch();
        char c = _getch();
        cout << "Hello";
        switch (c) {
        case KEY_UP:
            system("cls");
            cout << endl << "Up" << endl;//key up
            break;
        case KEY_DOWN:
            system("cls");
            cout << endl << "Down" << endl;   // key down
            break;
        case KEY_LEFT:
            system("cls");
            cout << endl << "Right" << endl;  // key right
            break;
        case KEY_RIGHT:
            system("cls");
            cout << endl << "Left" << endl;  // key left
            break;
        default:
            system("cls");
            cout << endl << "NULL" << endl;  // any other key
            break;
        }
    }

    return 0;
}

void CreateRandomBinDataset(string dir, int size) 
{
    ofstream outbinfile(dir, ios::binary);
    for (int i = 0; i < size; i++) {
        outbinfile << 'a';
    }

    
}