﻿#include <conio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <iterator>
#include <random>
#include <Windows.h>


enum AsciiCode
{
	CODE_ENTER = 13,
	CODE_DELETE = 83,
	CODE_UP = 72,
	CODE_DOWN = 80,
	CODE_LEFT = 75,
	CODE_RIGHT = 77,
	CODE_ESCAPE = 27,
};

enum ButtonsCode
{
	KEY_UP = 1,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ENTER,
	KEY_DELETE,
	KEY_ESCAPE,
	KEY_OTHER,
};

enum MenuItems
{
	ITEM_VIEW = 1,
	ITEM_SEARCH,
	ITEM_APPEND,
	ITEM_STATISTICS,
	ITEM_CRATE,
	ITEM_EXIT,
};

enum AppendMenuItems
{
	ITEM_APPEND_YES = 1,
	ITEM_APPEND_NO,
};

enum MenuSizes {
	HEIGHT_ITEM_MAIN = 6,
	LENGTH_ITEM_DEFAULT = 1,
	HEIGHT_ITEM_VIEW = 15,
	HEIGHT_ITEM_APPEND = 2,
};

enum PositionSteps
{
	HORIZONTAL_STEP = 1,
	VERTICAL_STEP = 1,
};

enum PositionBeginPoint
{
	HORIZONTAL_BEGIN_POINT = 1,
	VERTICAL_BEGIN_POINT = 1,
};

enum MenuLevels
{
	LEVEL_MAIN,
	LEVEL_VIEW,
	LEVEL_SEARCH,
	LEVEL_APPEND
};

enum StringFieldLength
{
	LENGTH_FIRST_NAME = 25,
	LENGTH_LAST_NAME = 25,
};

enum WidthOfTableFields
{
	COUNTER_FIELD_WIDTH = 8,
	FIRST_NAME_FIELD_WIDTH = 25,
	LAST_NAME_FIELD_WIDTH = 25,
	MATCH_SCORE_FIELD_WIDTH = 7,
	RU_SCORE_FIELD_WIDTH = 6,
	EN_SCORE_FIELD_WIDTH = 6,
	TOTAL_SCORE_FIELD_WIDTH = 7,
	OUR_FIELD_WIDTH = 93,
	PAGE_FIELD_WIDTH = 7,
};

enum LengthOfTableFields
{
	DATA_FIELD_LENGTH = 14,
	OUR_FIELD_LENGTH = 35,
};

enum IndexConst {
	IND_CONV_FACTOR = 1, // index conversion factor
};

#pragma pack(1)
static struct MenuTemplates
{
	std::string cursor;
	std::string space;

	std::string itemMainDescription;
	std::string lineView;
	std::string lineSearch;
	std::string lineAppend;
	std::string lineStatistics;
	std::string lineCreate;
	std::string lineExit;

	std::string itemViewDescription;
	std::string tableHeader;
	std::string tableSeparatorHorizontal;
	std::string tableSeparatorVertical;
	std::string tablePage;
	std::string tablePageSeparator;

	std::string appLineYes;
	std::string appLineNo;
};
#pragma pack (pop)

#pragma pack(1)
static struct ExamResults {

	std::string firstName;
	std::string lastName;
	u_short mathScore;
	u_short ruLangScore;
	u_short enLangScore;
	u_short totalScore;
};
#pragma pack (pop)

#pragma pack(1)
static struct ExamResultsBinary {
	char *firstName = new char[LENGTH_FIRST_NAME];
	char *lastName = new char[LENGTH_LAST_NAME];
	u_short mathScore;
	u_short ruLangScore;
	u_short enLangScore;
	u_short writeSize = 56;
	u_short stSize = sizeof(ExamResultsBinary);
};
#pragma pack (pop)



using findingCursorPositionFnc1 = void(*)(u_int&, const u_int&);
using findingCursorPositionFnc2 = void(*)(u_int&, u_int&, const u_int&, const u_int&);
using insertCursorPositionFnc  = std::string(*)(std::string, const u_int&, const MenuTemplates&, u_short, const u_int&);
using buttonsReadingFnc		   = u_short(*)(u_int&, u_int&);
using readingBinaryFileFnc     = void(*)(const std::string, std::list<ExamResults>&, u_int&, u_int&, u_int&);


void    CreateRandomBinDataset(std::string dir);
u_short ButtonsReading(u_int& horPosOut, u_int& vertPosOut);
void    FindingCursorPosition(u_int& vertPosOut, const u_int& heigh);
void    FindingCursorPosition(u_int& horPosOut, u_int& vertPosOut, const u_int& length, const u_int& height);
void    ReadingBinaryFile(const std::string dir, std::list<ExamResults>& usersData, u_int& uDataReadIndBegOut,
			u_int& uDataReadIndCountOut, u_int& uDataCountOut);
void	WritingInBinaryFile(const std::string dir, const std::list<ExamResults>& usersData, const u_int& dataWriteIndBeg,
			const u_int& dataWriteIndCount);

std::string InsertCursorPosition(std::string str, const u_int& vertPos, const MenuTemplates& mTemps,
	u_short level, const u_int& iterator);

void PrintMainMenu(const u_int& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc);
void PrintViewItem(std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
		u_int& dataIndBeg, u_int& dataIndCount, u_int& dataCount,
		insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc,
		findingCursorPositionFnc2 findCurPosFnc, readingBinaryFileFnc readBinFileFnc);
//
//void PrintSearchItem();
//
//void PrintAppendItem();
//
//void PrintStatisticsItem();
//
void PrintCrateItem(std::string& dir, std::list<ExamResults>& userData, const MenuTemplates& mTemps, u_int& horPos,
	u_int& vertPos, insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc);



int main(int argc, char* argv[])
{
	using namespace std;

	setlocale(LC_ALL, "ru");

	string path = "random_data.bin";
	if (argc > 1){
		path = argv[1];
	}
	else {
		cout << "введите путь и название файла: ";
		getline(cin, path);
	}
	//path = "random_data.bin";


	//cout << cin.peek() << '\t';

	MenuTemplates allMenuTemplatse = {
		">",
		" ",

		"навигация по меню:  arrow up/down - перемещение вверх/вниз, Enter - выбор пункта",
		" 1.просмотр файла",
		" 2.поиск по файлу",
		" 3.добавление в файл",
		" 4.вывод статистики",
		" 5.создание нового файла",
		" 6.выход",

		"навигация: arrow Up/Down - перемещение вверх/вниз, arrow Right/Left - перемещение \n"
		"вправо/влево, Enter - выбор элемента, Delite - удаление элеиента, Esc - возврат в меню",
		" |   №#   |           имя           |         фамилия         | матем | русс | англ | сумма |",
		" +--------+-------------------------+-------------------------+-------+------+------+-------+",
		"|",
		"                                   страница ",
		"/",

		" 1.да",
		" 2.нет",
	};

	list<ExamResults> usersData;
	u_int userDataViewIndexBegin(NULL), userDataViewIndexCount(NULL);
	u_int userDataCount(NULL);
	u_int horizontalPos = 1, verticalPos = 1;

	bool exitFlag = true;
	short codeItem(NULL);
	//ReadingBinaryFile(path, usersData, userDataViewIndexBegin, userDataViewIndexCount, userDataCount);
	while (exitFlag)
	{
		PrintMainMenu(verticalPos, allMenuTemplatse, InsertCursorPosition);

		codeItem = ButtonsReading(horizontalPos, verticalPos);
		FindingCursorPosition(verticalPos, static_cast<int>(HEIGHT_ITEM_MAIN));
		if (codeItem == KEY_ENTER)
		{
			switch (verticalPos)
			{
			case ITEM_VIEW:
				PrintViewItem(path, usersData, allMenuTemplatse, userDataViewIndexBegin,
					userDataViewIndexCount, userDataCount,
					InsertCursorPosition, ButtonsReading,
					FindingCursorPosition, ReadingBinaryFile);
				break;

			case ITEM_SEARCH:
				//SearchItemPrinting();
				break;

			case ITEM_APPEND:
				//AppendItemPrinting();
				break;

			case ITEM_STATISTICS:
				//StatisticsItemPrinting();
				break;

			case ITEM_CRATE:
				//CrateItemPrinting(path, userData, menuMain, horizontalPos, verticalPos, InsertCursorPosition,
				//	ButtonsReading, FindingCursorPosition);
				CreateRandomBinDataset(path);
				break;

			case ITEM_EXIT:
				exitFlag = false;

			}
		}
	}


	return 0;
}

void CreateRandomBinDataset(std::string dir)
{
	using namespace std;
	using std::cout;
	random_device rd;
	mt19937 mersenne(rd());

	u_short size;
	cout << "количество учетных записей: ";
	cin >> size;
	string firstNames[] = { "Иван", "Пётр", "Василий", "Марат", "Григорий",
		"Ильназ", "Али", "Максим", "Артём", "Джек" };
	string lastNames[] = { "Иванов", "Пётров", "Васильевич", "Айзатов",
		"Шайхутдинов", "Кларксон", "Ахматович", "Белых", "Понасенков", "Хабибулин" };
	ExamResultsBinary users;


	cout << sizeof(ExamResultsBinary) << endl;
	ofstream outBinFile(dir, ios::binary);
	for (int i = 0; i < size; i++) {
		strcpy_s(users.firstName, LENGTH_FIRST_NAME, firstNames[mersenne() % 10].c_str());
		strcpy_s(users.lastName, LENGTH_LAST_NAME, lastNames[mersenne() % 10].c_str());
		users.mathScore = mersenne() % 101;
		users.ruLangScore = mersenne() % 101;
		users.enLangScore = mersenne() % 101;

		outBinFile.write(users.firstName, sizeof(*users.lastName) * LENGTH_FIRST_NAME);
		outBinFile.write(users.lastName, sizeof(*users.firstName) * LENGTH_LAST_NAME);
		outBinFile.write((char*)&users.mathScore, sizeof(users.mathScore));
		outBinFile.write((char*)&users.ruLangScore, sizeof(users.ruLangScore));
		outBinFile.write((char*)&users.enLangScore, sizeof(users.enLangScore));

		cout << users.firstName << " " << users.lastName << " " << users.mathScore <<
			"\t" << users.ruLangScore << "\t" << users.enLangScore << endl;
	}
	outBinFile.close();

	system("pause");
}

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

void FindingCursorPosition(u_int& vertPosOut, const u_int& heigh)
{
	if (vertPosOut < VERTICAL_BEGIN_POINT) {
		vertPosOut = (heigh - vertPosOut) % (heigh + 1);
	}
	else if (vertPosOut > heigh) {
		vertPosOut /= heigh;
	}
}
void FindingCursorPosition(u_int& horPosOut, u_int& vertPosOut, const u_int& length, const u_int& height)
{
	if (horPosOut < HORIZONTAL_BEGIN_POINT) {
		horPosOut = (length - horPosOut) % (length + 1);
	}
	else if (horPosOut > length) {
		horPosOut /= length;
	}

	if (vertPosOut < VERTICAL_BEGIN_POINT) {
		vertPosOut = (height - vertPosOut) % (height + 1);
	}
	else if (vertPosOut > height && height == 1) {
		vertPosOut = height;
	}
	else if (vertPosOut > height) {
		vertPosOut /= height;
	}
}

void ReadingBinaryFile(const std::string dir, std::list<ExamResults>& usersData, u_int& uDataReadIndBegOut,
	u_int& uDataReadIndCountOut, u_int& uDataCountOut)
{
	using namespace std;

	ifstream inBinFile(dir, ios_base::binary);
	if (!inBinFile) {
		cerr << "Error opening" << endl;
		exit(1);
	}

	ExamResultsBinary dataBuffer = {};
	uDataCountOut = inBinFile.seekg(NULL, ios::end).tellg() / dataBuffer.writeSize;

	inBinFile.seekg(uDataReadIndBegOut * dataBuffer.writeSize, ios::beg);
	usersData.clear();
	usersData.resize(uDataReadIndCountOut);

	auto iter = usersData.begin();
	for (int i = 0; i < uDataReadIndCountOut; ++i, ++iter) {
		inBinFile.read(dataBuffer.firstName, sizeof(*dataBuffer.firstName) * LENGTH_FIRST_NAME);
		inBinFile.read(dataBuffer.lastName, sizeof(*dataBuffer.lastName) * LENGTH_LAST_NAME);
		inBinFile.read(reinterpret_cast<char*>(&dataBuffer.mathScore), sizeof(dataBuffer.mathScore));
		inBinFile.read(reinterpret_cast<char*>(&dataBuffer.ruLangScore), sizeof(dataBuffer.ruLangScore));
		inBinFile.read(reinterpret_cast<char*>(&dataBuffer.enLangScore), sizeof(dataBuffer.enLangScore));
		
		iter->firstName = string(dataBuffer.firstName);
		iter->lastName = string(dataBuffer.lastName);
		iter->mathScore = dataBuffer.mathScore;
		iter->ruLangScore = dataBuffer.ruLangScore;
		iter->enLangScore = dataBuffer.enLangScore;
		iter->totalScore = iter->mathScore + iter->ruLangScore + iter->enLangScore;
	}
	inBinFile.close();

	//int count = 0;
	//for (const ExamResults& id : usersData) {
	//	cout << count << " " << id.firstName << " " << id.lastName << " " << id.mathScore
	//		<< " " << id.ruLangScore << " " << id.enLangScore << endl;
	//	++count;
	//}
	//cout << "read successful" << endl;
	//system("pause");
}

void WritingInBinaryFile(const std::string dir, const std::list<ExamResults>& usersData, const u_int& dataWriteIndBeg,
	const u_int& dataWriteIndCount)
{
	using namespace std;

	ofstream outBinFile(dir, ios_base::binary);
	if (!outBinFile) {
		cerr << "Error opening" << endl;
		exit(1);
	}

	ExamResultsBinary dataBuffer = {};

	outBinFile.seekp(dataWriteIndBeg * dataBuffer.writeSize, ios::beg);

	auto iter = usersData.begin();
	for (int i = 0; i < dataWriteIndCount; ++i, ++iter) {
		strcpy_s(dataBuffer.firstName, LENGTH_FIRST_NAME, iter->firstName.c_str());
		strcpy_s(dataBuffer.lastName, LENGTH_LAST_NAME, iter->lastName.c_str());
		dataBuffer.mathScore = iter->mathScore;
		dataBuffer.ruLangScore = iter->ruLangScore;
		dataBuffer.enLangScore = iter->enLangScore;

		outBinFile.write(dataBuffer.firstName, sizeof(*dataBuffer.firstName) * LENGTH_FIRST_NAME);
		outBinFile.write(dataBuffer.lastName, sizeof(*dataBuffer.lastName) * LENGTH_LAST_NAME);
		outBinFile.write(reinterpret_cast<char*>(&dataBuffer.mathScore), sizeof(dataBuffer.mathScore));
		outBinFile.write(reinterpret_cast<char*>(&dataBuffer.ruLangScore), sizeof(dataBuffer.ruLangScore));
		outBinFile.write(reinterpret_cast<char*>(&dataBuffer.enLangScore), sizeof(dataBuffer.enLangScore));
	}
	outBinFile.close();
}

void DeletingFromBinaryFile(const std::string dir, const u_int& dataDeleteIndBeg,
	const u_int& dataDeleteIndCount)
{
	using namespace std;

	ofstream outBinFile(dir, ios_base::binary);
	if (!outBinFile) {
		cerr << "Error opening" << endl;
		exit(1);
	}

	ExamResultsBinary structConf = {};
	outBinFile.seekp(dataDeleteIndBeg * structConf.writeSize, ios::beg);

	for (int i = 0; i < dataDeleteIndCount; ++i) {

	}
	outBinFile.close();
}

std::string InsertCursorPosition(std::string str, const u_int& vertPos, const MenuTemplates& mTemps,
	u_short level, const u_int& iterator)
{
	using std::replace;

	if (level == LEVEL_MAIN)
	{
		switch (vertPos)
		{
		case ITEM_VIEW:
			if (mTemps.lineView == str) {
				str.replace(NULL, 1, mTemps.cursor);
			}
			break;

		case ITEM_SEARCH:
			if (mTemps.lineSearch == str) {
				str.replace(NULL, 1, mTemps.cursor);
			}
			break;

		case ITEM_APPEND:
			if (mTemps.lineAppend == str) {
				str.replace(NULL, 1, mTemps.cursor);
			}
			break;

		case ITEM_STATISTICS:
			if (mTemps.lineStatistics == str) {
				str.replace(NULL, 1, mTemps.cursor);
			}
			break;

		case ITEM_CRATE:
			if (mTemps.lineCreate == str) {
				str.replace(NULL, 1, mTemps.cursor);
			}
			break;
		case ITEM_EXIT:
			if (mTemps.lineExit == str) {
				str.replace(NULL, 1, mTemps.cursor);
			}
			break;
		}
	}

	else if (level == LEVEL_VIEW) {
		if (iterator == 0) {
			if ((iterator + 1) == vertPos) {
				str.replace(NULL, 1, mTemps.cursor);
			}
		}
		else {
			if (iterator == vertPos) {
				str.replace(NULL, 1, mTemps.cursor);
			}
		}
	}

	else if (level == LEVEL_SEARCH) {

	}

	else if (level == LEVEL_APPEND) {
		switch (vertPos)
		{
		case ITEM_APPEND_YES:
			if (mTemps.appLineYes == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_APPEND_NO:
			if (mTemps.appLineNo == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;
		}
	}

	return str;
}

void PrintMainMenu(const u_int& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc)
{
	using namespace std;

	system("cls");

	cout << insCurPosFnc(mTemps.lineView, vertPos, mTemps, LEVEL_MAIN, NULL) << endl;
	cout << insCurPosFnc(mTemps.lineSearch, vertPos, mTemps, LEVEL_MAIN, NULL) << endl;
	cout << insCurPosFnc(mTemps.lineAppend, vertPos, mTemps, LEVEL_MAIN, NULL) << endl;
	cout << insCurPosFnc(mTemps.lineStatistics, vertPos, mTemps, LEVEL_MAIN, NULL) << endl;
	cout << insCurPosFnc(mTemps.lineCreate, vertPos, mTemps, LEVEL_MAIN, NULL) << endl;
	cout << insCurPosFnc(mTemps.lineExit, vertPos, mTemps, LEVEL_MAIN, NULL) << endl;
}

void PrintViewItem(std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
		u_int& dataIndBeg, u_int& dataIndCount, u_int& dataCount,
		insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc,
		findingCursorPositionFnc2 findCurPosFnc, readingBinaryFileFnc readBinFileFnc)
{
	using namespace std;

	system("cls");


	// чтение учетных записей
	readBinFileFnc(dir, usersData, dataIndBeg, dataIndCount, dataCount);

	bool flagExit = false;
	if (dataCount == NULL) {
		cout << "файл пустой" << endl;
		system("pause");
		flagExit = true;
	}

	u_int horPos = 1;
	u_int vertPos = 1;

	u_short codeState;
	u_int   prevHorPos(NULL);
	u_int   dataPageCount(NULL);

	auto uData = usersData.begin();
	
	// проверка длины среза данных
	if ((dataIndBeg + dataIndCount - IND_CONV_FACTOR) > (dataCount - IND_CONV_FACTOR)) {
		dataIndCount = dataCount - dataIndBeg;
	}

	stringstream dataBuffer;

	while (!flagExit)
	{
		system("cls");



		// чтение нового среза данных
		if (prevHorPos != horPos) {
			// установка индексов среза данных
			dataIndCount = DATA_FIELD_LENGTH;
			dataIndBeg = (horPos - IND_CONV_FACTOR) * dataIndCount;
			
			// проверка длины среза данных
			if ((dataIndBeg + dataIndCount - IND_CONV_FACTOR) > (dataCount - IND_CONV_FACTOR)) {
				dataIndCount = dataCount - dataIndBeg;
			}

			// чтение среза данных
			readBinFileFnc(dir, usersData, dataIndBeg, dataIndCount, dataCount);

			if (dataCount == NULL) {
				cout << "файл пустой" << endl;
				system("pause");
				flagExit = true;
			}

			// нахождение количества страниц
			if (dataCount % DATA_FIELD_LENGTH == NULL) {
				dataPageCount = dataCount / DATA_FIELD_LENGTH;
			}
			else if (dataCount > DATA_FIELD_LENGTH) {
				dataPageCount = dataCount / DATA_FIELD_LENGTH;
				++dataPageCount;
			}
			else {
				++dataPageCount;
			}

			findCurPosFnc(horPos, vertPos, dataPageCount, dataIndCount);
		}
		prevHorPos = horPos;

		// установка индекса итератора локального контейнера с срезом данных
		uData = usersData.begin();

		// заполнение промежуточного потока для вывода таблицы
		dataBuffer << mTemps.tableSeparatorHorizontal << "\n" << mTemps.tableHeader << "\n" << mTemps.tableSeparatorHorizontal << "\n";
		for (u_short uIndex = dataIndBeg; uIndex <= (dataIndBeg + dataIndCount - IND_CONV_FACTOR); ++uIndex) {
			dataBuffer << insCurPosFnc(mTemps.space, vertPos, mTemps, LEVEL_VIEW, (uIndex + 1) % (dataIndCount) + 1)
				<< mTemps.tableSeparatorVertical << setw(COUNTER_FIELD_WIDTH) << right << uIndex + 1 << mTemps.tableSeparatorVertical
				<< setw(FIRST_NAME_FIELD_WIDTH) << left << uData->firstName << mTemps.tableSeparatorVertical
				<< setw(LAST_NAME_FIELD_WIDTH) << uData->lastName << mTemps.tableSeparatorVertical
				<< setw(MATCH_SCORE_FIELD_WIDTH) << right << uData->mathScore << mTemps.tableSeparatorVertical
				<< setw(RU_SCORE_FIELD_WIDTH) << right << uData->ruLangScore << mTemps.tableSeparatorVertical
				<< setw(EN_SCORE_FIELD_WIDTH) << right << uData->enLangScore << mTemps.tableSeparatorVertical
				<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << uData->totalScore << mTemps.tableSeparatorVertical << "\n"
				<< mTemps.tableSeparatorHorizontal << "\n";

			// защита от выхода за диапазон контейнера
			if (uIndex != (dataIndBeg + dataIndCount - IND_CONV_FACTOR)) {
				++uData;
			}
		}
		dataBuffer << mTemps.tablePage << setw(PAGE_FIELD_WIDTH) << right << horPos << mTemps.tablePageSeparator <<
			left << dataPageCount << "\n";
		dataBuffer << mTemps.itemViewDescription << endl;

		// перевод данных из буфера в поток вывода 
		cout << dataBuffer.str();
		dataBuffer.str("");
		dataBuffer.clear();

		// обработка клавиш
		codeState = buttReadFnc(horPos, vertPos);
		findCurPosFnc(horPos, vertPos, dataPageCount, dataIndCount);

		switch (codeState)
		{
		case KEY_ENTER:
				
			break;

		case KEY_DELETE:

			break;

		case KEY_ESCAPE:
			flagExit = true;
			break;
		}

	}

}

void PrintCrateItem(std::string& dir, std::list<ExamResults>& userData, const MenuTemplates& mTemps, u_int& horPos,
	u_int& vertPos, insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc)
{
	using namespace std;

	bool flagExit = false;
	u_short codeState;
	vertPos = 1;

	while (!flagExit)
	{
		system("cls");
		cout << "создать новый файл?" << endl;
		cout << insCurPosFnc(mTemps.appLineYes, vertPos, mTemps, LEVEL_APPEND, NULL) << endl;
		cout << insCurPosFnc(mTemps.appLineNo, vertPos, mTemps, LEVEL_APPEND, NULL) << endl;

		codeState = buttReadFnc(horPos, vertPos);
		findCurPosFnc(vertPos, HEIGHT_ITEM_APPEND);

		if (codeState == KEY_ENTER) {
			switch (vertPos)
			{
			case ITEM_APPEND_YES:
				system("cls");
				cout << "введите путь и имя новго файла: ";
				getline(cin, dir); 
				cout << endl;
				flagExit = true;
				break;

			case ITEM_APPEND_NO:
				cout << "запись в файл: " << dir << endl;
				flagExit = true;
				break;
			}
		}
	}

	userData.clear();
	flagExit = false;
	ExamResults bufData;
	int counter = 0;
	while (!flagExit)
	{
		system("cls");
		cout << "Введите данные:" << endl;
		getline(cin, bufData.firstName);
		getline(cin, bufData.lastName);
		cin >> bufData.mathScore;
		cin >> bufData.ruLangScore;
		cin >> bufData.enLangScore;
		userData.push_back(bufData);
		++counter;
		cout << "_________________";
		if (buttReadFnc(horPos, vertPos) == KEY_ESCAPE) {
			flagExit = true;
		}
	}

	ofstream fout(dir, ios::trunc | ios::binary);
	fout.write((char*)&userData, counter * sizeof(ExamResults));
	fout.close();
}