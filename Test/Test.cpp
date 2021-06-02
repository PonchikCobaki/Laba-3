#include <iostream>
#include <iomanip> // для setw()
#include <fstream>
#include <string>
#include <string.h>
#include <winsock.h>
#include <filesystem>
using namespace std;

int main()
{
	filesystem::remove();
	ofstream outBinFile("test.bin", ios::binary | ios::ate);
	char* firstName = new char[25];
	char* lastName = new char[25];
	strcpy_s(firstName, 25, "Вася"s.c_str());
	strcpy_s(lastName, 25, "Иванов"s.c_str());
	u_short mathScore = 22;
	u_short ruLangScore = 33;
	u_short enLangScore = 44;
	outBinFile.seekp(1 * 56, ios::beg);
	cout << outBinFile.tellp() << endl;
	outBinFile.write(firstName, 25);
	cout << outBinFile.tellp() << endl;
	outBinFile.write(lastName, 25);
	cout << outBinFile.tellp() << endl;
	outBinFile.write((char*)&mathScore, sizeof(u_short));
	cout << outBinFile.tellp() << endl;
	outBinFile.write((char*)&ruLangScore, sizeof(u_short));
	cout << outBinFile.tellp() << endl;
	outBinFile.write((char*)&enLangScore, sizeof(u_short));
	cout << outBinFile.tellp() << endl;
	outBinFile.seekp(0, ios::end);
	cout << outBinFile.tellp() << endl;
	
	outBinFile.close();
}
// "Task 4.exe" C:\Users\PonchikCobaki\source\repos\Laba 3\Test\test.bin