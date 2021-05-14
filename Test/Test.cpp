#include <iostream>
#include <cstdlib> // для exit()

using namespace std;

// Вывести меню пользователю и вернуть номер варианта
int prompt_menu_item()
{
    // Выбранный вариант менюж
    int variant;
    cout << "Выберите вариант\n" << endl;
    cout << "1. просмотреть содержимое\n"
        << "2. найти минимальный объект\n"
        << "3. найти максимальный объект\n"
        << "4. отсортировать\n"
        << "5. найти среднее кол-во элементов\n"
        << "6. дополнить таблицу\n"
        << "7. выйти\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}

int main(int argc, char* argv[])
{
    int variant = prompt_menu_item();

    switch (variant) {
    case 1:
        cout << "Проматриваем содержимое..." << endl;
        break;
    case 2:
        cout << "Находим минимальный элемент..." << endl;
        break;
    case 3:
        cout << "Находим максимальный элемент..." << endl;
        break;
    case 4:
        cout << "Сортируем..." << endl;
        break;
    case 5:
        cout << "Находим среднее количество элементов..." << endl;
        break;
    case 6:
        cout << "Дополняем таблицу..." << endl;
        break;
    case 7:
        cout << "Выход из программы..." << endl;
        exit(EXIT_SUCCESS);
        break;
    default:
        cerr << "Вы выбрали неверный вариант" << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
