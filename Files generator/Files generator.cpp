#include <iostream>
#include <fstream>
#include <string>
#include <random> // для std::random_device и std::mt19937

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");

    std::random_device rd;
    std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

    string dir = "task_3_data.bin";

    ifstream in_bin_file(dir, ios::binary);
    ofstream out_bin_file(dir, ios::binary);


    cout << "write" << endl;

    float out_buf[10];

    for (int i = 0; i < 10; ++i)
    {
        out_buf[i] = float(mersenne() / 10e7);
        cout << out_buf[i] << "\t";

        if ((i + 1) % 5 == 0)
            cout << "\n";


    }

    out_bin_file.write(reinterpret_cast<char*>(&out_buf), sizeof out_buf);
    out_bin_file.close();


    cout << "read" << endl;

    float in_buf[10];

    in_bin_file.read(reinterpret_cast<char*>(&in_buf), sizeof in_buf);

    for (int i = 0; i < 10; ++i)
    {

        cout << in_buf[i] << "\t";

        if ((i + 1) % 5 == 0)
            cout << "\n";
    }

    in_bin_file.close();
}