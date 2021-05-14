#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
	string in_str, buffer, dir = "data.txt";						// объявления перемненных
	int start_i_max_str = 0, len_max_str = 0;
	int interm_len = 0;
	int pos = 0, prev_pos = 0;

	setlocale(LC_ALL, "ru");					// установка русской кодировки

	if (argc > 1)
	{
		dir = argv[1];
	}
	else
	{
		cout << "Not arguments, use data.txt" << endl;
	}

	cout << "\n";

	ifstream in_file(dir);		// открывание исходного файла

	if (in_file.is_open()) {					// проверка файла на открывание
		while (in_file) {						// чтение файла
			getline(in_file, buffer);
			in_str += buffer;
		}

		//cout << in_str << endl;

		while (pos != string::npos) {																	// Парсер
			pos = min(min(in_str.find("...", pos + 1), in_str.find(",", pos + 1)),
				min(in_str.find(".", pos + 1), in_str.find("?", pos + 1), in_str.find("!", pos + 1)));	// нахождение разделителя фразы

			if (pos != -1)
				interm_len = pos - prev_pos - 1;															// вычисление промежуточной длины
			else {
				pos = in_str.length() - 1;
				interm_len = in_str.length() - prev_pos - 1;
				if (interm_len > len_max_str) {																// поиск наибольшей фразы
					len_max_str = interm_len;
					start_i_max_str = prev_pos;
				}
				break;
			}
			if (interm_len > len_max_str) {																// поиск наибольшей фразы
				len_max_str = interm_len;
				start_i_max_str = prev_pos;
			}

			prev_pos = pos;

		}
	}
	else {
		cout << "Error opening" << endl;
		exit(1);
	}
	in_file.close();															// закрывание файла

	ofstream out_file("output file.txt", ios_base::out);					// открывание файла

	cout << start_i_max_str + 1 << "\t"<< len_max_str << endl;

	out_file << in_str.substr(start_i_max_str + 1, len_max_str) << endl;	// запись в файл
	cout << in_str.substr(start_i_max_str + 1, len_max_str) << endl;		// промежуточный вывод в консоль

	out_file.close();														// закрывание файла


	return 0;
}