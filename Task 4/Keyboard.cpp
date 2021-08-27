#pragma once
#include "Keyboard.h"

u_short ButtonsReading(u_int& horPosOut, u_int& vertPosOut)
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
		vertPosOut -= VERTICAL_STEP;
		return KEY_UP;

	case CODE_DOWN:
		vertPosOut += VERTICAL_STEP;
		return KEY_DOWN;

	case CODE_LEFT:
		horPosOut -= HORIZONTAL_STEP;
		return KEY_LEFT;

	case CODE_RIGHT:
		horPosOut += HORIZONTAL_STEP;
		return KEY_RIGHT;

	case CODE_DELETE:
		return KEY_DELETE;

	default:
		return KEY_OTHER;
	}
}

void UserInput(ExamResults& userData)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	using namespace std;

	stringstream input;
	string buffer;
	string subBuffer;
	getline(cin, buffer);
	input << buffer;

	// запись строк
	while (buffer.length() == 0) {
		getline(cin, buffer);
		input << buffer;
		cout << "\t";
	}

	input >> userData.firstName;
	input >> userData.lastName;

	// запись чисел с преобразованием из строк
	input >> subBuffer;
	userData.mathScore = atoi(subBuffer.c_str());
	input >> subBuffer;
	userData.ruLangScore = atoi(subBuffer.c_str());
	input >> subBuffer;
	userData.enLangScore = atoi(subBuffer.c_str());
}