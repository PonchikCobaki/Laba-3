#include <conio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <Windows.h>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75
#define KEY_ESCAPE 27
#define KEY_ENTER 27

using namespace std;

void CreateRandomBinDataset(string dir, int size);
int NavigationMenu();

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    string path = "random_data.bin";

    //CreateRandomBinDataset(path, 10000);

    //cout << cin.peek() << '\t';

    while (true) {
        NavigationMenu();
    }
     
    return 0;
}

void CreateRandomBinDataset(string dir, int size) 
{
    random_device rd;
    mt19937 mersenne(rd());

    string firstNames[] = { "Иван", "Пётр", "Василий", "Марат", "Григорий",
        "Ильназ", "Али", "Максим", "Артём", "Джек" };
    string lastNames[] = { "Иванов", "Пётров", "Васильевич", "Айзатов",
        "Шайхутдинов", "Кларксон", "Ахматович", "Белых", "Понасенков", "Хабибулин" };

    struct ExamResults {
        string fName = "";
        string lName = "";
        int mathSc = 0;
        int ruScore = 0;
        int foreScore = 0;
    };

    ExamResults* Users = new ExamResults[size];

    for (int i = 0; i < size; i++) {
        Users[i].fName = firstNames[mersenne() % 10];
        Users[i].lName = lastNames[mersenne() % 10];
        Users[i].mathSc = mersenne() % 101;
        Users[i].ruScore = mersenne() % 101;
        Users[i].foreScore = mersenne() % 101;

        cout << Users[i].fName << " " << Users[i].lName << "\t" << Users[i].mathSc <<
            "\t" << Users[i].ruScore << "\t" << Users[i].foreScore << endl;
    }

    ofstream outBinFile(dir, ios::trunc | ios::binary);
    outBinFile.write((char*)Users, size * sizeof(Users) );
    outBinFile.close();

    delete[] Users;
}

int NavigationMenu()
{

    cout << _getch();
    switch (_getch()) {
    case KEY_UP:
        cout << endl << "Up" << endl;//key up
        break;
    case KEY_DOWN:
        cout << endl << "Down" << endl;   // key down
        break;
    case KEY_LEFT:
        cout << endl << "Right" << endl;  // key right
        break;
    case KEY_RIGHT:
        cout << endl << "Left" << endl;  // key left
        break;
    case KEY_ESCAPE:
        cout << endl << "Esc" << endl;  // key left
        break;
    default:
        cout << endl << "NULL" << endl;  // any other key
        system("cls");
        break;
    }

    return 0;
}