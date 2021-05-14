#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <list>
#include <iterator>


using namespace std;



int main()
{
	setlocale(LC_ALL, "ru");

	float buffer;
	list<float> data;
	
	// открывание исходного файла
	fstream in_file("In.txt", ios::in | ios::trunc);	

	// проверка файла на открывание
	if (!in_file) {				
		cerr << "Error opening" << endl;
		exit(1);
	}

	// чтение файла
	while (in_file) {
		in_file >> buffer;
		data.push_back(buffer);


		cout << buffer << endl;

	}

	//ofstream out_file("Out.txt", ios_base::out);

	//if (!out_file) {				// проверка файла на открывание
	//	cerr << "Error opening" << endl;
	//	exit(2);
	//}

	//cout << "PO" << in_file.tellg() << "PI" << in_file.tellp() << endl;
	in_file.seekp(0, ios::beg);

	ofstream out_file("file.txt");

	int counter = 1;

	for (auto aIndex = data.begin(); aIndex != data.end(); ++aIndex) {

		if (out_file.good())
			out_file.clear();

		if (counter % 5 != 0)
			out_file << *aIndex << " " << flush;

		++counter;
	}
	int nCounter = 0;
	for (auto& i : data) {
		in_file.seekp(0, ios::beg);
		in_file << i << " ";
		++nCounter;
	}
	cout << '\n';



	//5 46 45 54 44 88 99 344255 - 5252516 0.3452145 32457689.541 515.161 0.51161 16161.000059 - 56161.155005

	return 0;
}