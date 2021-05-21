#include <conio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <Windows.h>

enum AsciiCode 
{
    CODE_ENTER = 13,
    CODE_DELETE = 83,
    CODE_UP = 72,
    CODE_DOWN = 80,
    CODE_LEFT = 77,
    CODE_RIGHT = 75,
    CODE_ESCAPE = 27,
};

enum ButtonCode
{
    KEY_UP = 1,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ENTER,
    KEY_DELETE,
    KEY_ESCAPE,
};

enum MenuItem
{
    ITEM_VIEW = 1,
    ITEM_SEARCH,
    ITEM_APPEND,
    ITEM_CHANGE,
    ITEM_CRATE,
    ITEM_EXIT
};

enum StepsIterators
{
    HORIZONTAL_STEP = 1,
    VERTICAL_STEP = 1,
};


void CreateRandomBinDataset(std::string dir, int size);

bool NavigationMenu(int vertPos, int codeItem);
int ButtonsReading(int* horPos, int* VertPos);

void MainMenuPrinting(int code);
void ViewItemPrinting();
void SearchItemPrinting();
void AppendItemPrinting();
void ChangeItemPrinting();
void CrateItemPrinting();

int main(int argc, char* argv[])
{
    using namespace std;
    setlocale(LC_ALL, "ru");

    string path = "random_data.bin";
    //CreateRandomBinDataset(path, 10000);
    //cout << cin.peek() << '\t';


    int horizontalPos = 0, verticalPos = 0;
    bool exitFlag = true;


    while (exitFlag) {
        //cout << ButtonsReading() << "\n";
        system("cls");
        ButtonsReading(&horizontalPos, &verticalPos);
        exitFlag = NavigationMenu(verticalPos, ButtonsReading(&horizontalPos, &verticalPos));
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

int ButtonsReading(int* horPos, int* VertPos)
{
    using std::cout;
    using std::endl;

    switch (_getch())
    {
    case CODE_ESCAPE:
        return KEY_ESCAPE;

    case CODE_ENTER:
        return KEY_ENTER;

    }
    
    // второй вызов _getch() для считывания функциональных клавишь 
    switch (_getch())
    {
    case CODE_UP:
        *horPos += VERTICAL_STEP;
        return KEY_UP;

    case CODE_DOWN:
        *horPos -= VERTICAL_STEP;
        return KEY_DOWN;

    case CODE_LEFT:
        *VertPos -= HORIZONTAL_STEP;
        return KEY_LEFT;

    case CODE_RIGHT:
        *VertPos += HORIZONTAL_STEP;
        return KEY_RIGHT;

    case CODE_DELETE:
        return KEY_DELETE;
    }
}

bool NavigationMenu(int vertPos, int codeItem)
{
    if (codeItem == KEY_ENTER)
    {
        switch (vertPos)
        {
        case ITEM_VIEW:
            ViewItemPrinting();
            break;

        case ITEM_SEARCH:
            SearchItemPrinting();
            break;

        case ITEM_APPEND:
            AppendItemPrinting();
            break;

        case ITEM_CHANGE:
            ChangeItemPrinting();
            break;

        case ITEM_CRATE:
            CrateItemPrinting();
            break;

        case ITEM_EXIT:
            return false;      
        }
    }
}