#pragma once

#include <conio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <vector>
#include <iterator>
#include <random>
#include <Windows.h>



enum StringFieldLength	//	перечесление размеров поля имен в структуре
{
	LENGTH_FIRST_NAME = 25,
	LENGTH_LAST_NAME = 25,
};

#pragma pack(1)
struct ExamResults	//	структура учетной записи
{	
	std::string firstName;
	std::string lastName;
	u_short mathScore;
	u_short ruLangScore;
	u_short enLangScore;
	u_short totalScore;
};
#pragma pack (pop)

#pragma pack(1)
struct ExamResultsBinary	// структура для записи в бинарный файл
{
	char* firstName = new char[LENGTH_FIRST_NAME];
	char* lastName = new char[LENGTH_LAST_NAME];
	u_short mathScore;
	u_short ruLangScore;
	u_short enLangScore;
	u_short writeSize = 56;
	u_short stSize = sizeof(ExamResultsBinary);
};
#pragma pack (pop)