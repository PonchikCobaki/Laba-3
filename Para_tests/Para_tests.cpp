#include <stdio.h> // для printf() и scanf()
#include <conio.h> // для _getch()
#include <windows.h>
HANDLE hConsole, hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void add()
{
    return;
}// объявляем нужные
void dif()
{
    return;
}// нам функции

int m_pos = 0;          // позиция меню
int max_pos = 3;        // максимальная позиция меню
char s1[101];

enum ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};

char* ru(char* s) { AnsiToOem(s, s1);   return s1; } // вывод русским языком

void SetColor(int text, int background) // устанавливаем цвет
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void GotoXY(int X, int Y) // позиция курсора
{
    COORD coord = { X, Y };
    SetConsoleCursorPosition(hStdOut, coord);
}

void go(int x) // Если нажали Enter
{
    if (x == 0) add();
    if (x == 1) dif();
    printf_s(ru("\n   Нажмите любую\n      клавишу"));
    SetColor(0, 0);
    GotoXY(35, 24);
    exit(0);
}

void choice();

void menu()
{
    system("cls"); // очистить экран
    if (m_pos == 0)
    {
        SetColor(6, 0); printf_s(ru(" + Прибавить матрицы\n")); SetColor(15, 0);
        printf_s(ru("   Отнять матрицы\n"));
        printf_s(ru("   Выход\n"));
        choice();
    }
    if (m_pos == 1)
    {
        printf_s(ru("   Прибавить матрицы\n"));
        SetColor(6, 0); printf_s(ru(" + Отнять матрицы\n")); SetColor(15, 0);
        printf_s(ru("   Выход\n"));
        choice();
    }
    if (m_pos == 2)
    {
        printf_s(ru("   Прибавить матрицы\n"));
        printf_s(ru("   Отнять матрицы\n"));
        SetColor(6, 0); printf_s(ru(" + Выход\n")); SetColor(15, 0);
        choice();
    }
}

void choice() // функция выбора
{
l:
    int ch = _getch(); // считываем значение нажатой клавиши
    if (ch == 224) // 224 - это стрелочки
    {
        switch (ch)
        {
        case 80: // вниз
            if (m_pos + 1 < max_pos) ++m_pos;
            menu();
            break;
        case 72: // вверх
            if (m_pos - 1 >= 0) --m_pos;
            menu();
            break;
        case 13: // Enter
            go(m_pos);
            break;
        default:
            goto l;
        }
    }
    switch (ch)
    {
    case 80: // вниз
        if (m_pos + 1 < max_pos) ++m_pos;
        menu();
        break;
    case 72: // вверх
        if (m_pos - 1 >= 0) --m_pos;
        menu();
        break;
    case 13: // Enter
        go(m_pos);
        break;
    default:
        goto l;
    }
}

void main()
{
    menu();
}