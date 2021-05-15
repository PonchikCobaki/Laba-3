#include <conio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <Windows.h>

enum KeyCode 
{
    KEY_ENTER = 13,
    KEY_DELETE = 83,
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 77,
    KEY_RIGHT = 75,
    KEY_ESCAPE = 27,
};
enum MenuCode
{
    MENU_ENTER = 1,
    MENU_DELETE,
    MENU_UP,
    MENU_DOWN,
    MENU_LEFT,
    MENU_RIGHT,
    MENU_ESCAPE,
};


void CreateRandomBinDataset(std::string dir, int size);
void CreateMenu(int code);
int NavigationMenu();


int main(int argc, char* argv[])
{
    using namespace std;
    setlocale(LC_ALL, "ru");

    string path = "random_data.bin";

    //CreateRandomBinDataset(path, 10000);

    //cout << cin.peek() << '\t';

    cout << "size string " <<sizeof(string) << endl;

    while (true) {
        cout << NavigationMenu() << "\n";
    }
     
    return 0;
}

void CreateRandomBinDataset(std::string dir, int size) 
{
    using namespace std;
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
    using std::cout;
    using std::endl;

    switch (_getch())
    {
    case KEY_ESCAPE:
        return MENU_ESCAPE;

    case KEY_ENTER:
        return MENU_ENTER;

    }
    
    // второй вызов _getch() для считывания функциональных клавишь 
    switch (_getch())
    {
    case KEY_UP:
        return MENU_UP;

    case KEY_DOWN:
        return MENU_DOWN;

    case KEY_LEFT:
        return MENU_LEFT;

    case KEY_RIGHT:
        return MENU_RIGHT;

    case KEY_DELETE:
        return MENU_DELETE;
    }

    return 0;
}