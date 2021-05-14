#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <random>

using namespace std;

void GeneratingBinFile(int n, string d);
void PrintingBinFile(string d);



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	string dir = "data.bin";

	if (argc > 1)
	{
		dir = argv[1];
	}
	else
	{
		cout << "Not arguments, use : \n\t" << dir << endl;
	}

	GeneratingBinFile(10, dir);
	PrintingBinFile(dir);

	// открывание исходного файла
	ifstream ifile(dir, ios::binary);

	// проверка файла на открывание
	if (!ifile) {
		cerr << "Error opening" << endl;
		exit(1);
	}

	int nSize = ifile.seekg(0, ios::end).tellg() / sizeof(float);
	float* fPtrInArr = new float[nSize];

	cout << "size arr " << _msize(fPtrInArr) << endl;
	cout << "quantity character " << nSize << endl;


	// чтение файла
	ifile.seekg(0, ios::beg);
	ifile.read(reinterpret_cast<char*>(fPtrInArr), _msize(fPtrInArr));
	ifile.close();

	float fAverage = 0;

	cout << "\n " << "read" << endl;

	for (int i = 0; i < nSize; ++i) 
		fAverage += fPtrInArr[i];
	
	fAverage /= nSize;

	cout << "\n" << "average value " << fAverage << endl;

	for (int i = 0; i < nSize; ++i) 
		fPtrInArr[i] -= fAverage;
	

	ofstream ofile(dir, ios::binary);
	ofile.write(reinterpret_cast<char*>(fPtrInArr), _msize(fPtrInArr));
	ofile.close();
	
	PrintingBinFile(dir);

	delete[] fPtrInArr;

	return 0;
}

void GeneratingBinFile(int n, string d)
{
	std::random_device rd;
	std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

	string dir = "data.bin";

	ofstream outf(d, ios::binary);

	if (!outf) {
		cerr << "Error opening" << endl;
		exit(2);
	}

	float* fPtrOutBuf = new float[n];

	cout << "\n " << "creating" << endl;
	for (int i = 0; i < n; ++i)
		fPtrOutBuf[i] = float(mersenne() / 10e7);
	

	outf.write(reinterpret_cast<char*>(fPtrOutBuf), _msize(fPtrOutBuf));
	outf.close();

	delete[] fPtrOutBuf;
}

void PrintingBinFile(string d) 
{
	ifstream inf(d, ios::binary);

	if (!inf) {
		cerr << "Error opening" << endl;
		exit(3);
	}

	cout << "\n "<< "Printing" << endl;

	int n = inf.seekg(0, ios::end).tellg() / sizeof(float);
	float* fPtrIn = new float[n];

	inf.seekg(0, ios::beg);
	inf.read(reinterpret_cast<char*>(fPtrIn), _msize(fPtrIn));

	for (int i = 0; i < n; ++i)
	{
		cout << fPtrIn[i] << "\t";
		if ((i + 1) % 5 == 0)
			cout << "\n";
	}

	inf.close();
	
	delete[] fPtrIn;
}