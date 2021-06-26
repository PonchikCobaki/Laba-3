#include <algorithm>
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
#include <filesystem>



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

enum DataBuffersSize {
	SUBFILE_SIZE = 2 * DATA_FIELD_LENGTH, // 98 размер под файлов для удаления/изменения данных 7
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



using buttonsReadingFnc			= u_short(*)(u_int& horPosOut, u_int& vertPosOut);
using findingCursorPositionFnc1 = void(*)(u_int& vertPosOut, const u_int& heigh);
using findingCursorPositionFnc2 = void(*)(u_int& horPosOut, u_int& vertPosOut, const u_int& length, const u_int& height);
using userInputFnc				= void(*)(ExamResults& userData);


using readingBinaryFileFnc      = void(*)(const std::string dir, std::list<ExamResults>& usersData, const u_int& uDataReadIndBegOut,
									const u_int& uDataReadIndCountOut, u_int& uDataCountOut);
using writeInBinaryFileFnc		= void(*)(const std::string& dir);
using findElementFnc			= bool(*)(const std::vector<u_int>& arr, const u_int& el);
using deletingFromBinaryFileFnc = void(*)(const std::string& dir, const u_int& droppedInd,
									const u_int& dataCount, writeInBinaryFileFnc writeInBinFileFnc);
using changeDataInBinaryFileFnc = void(*)(const std::string& dir, const u_int& changeInd, const u_int& dataCount,
									const ExamResults& userData, writeInBinaryFileFnc writeInBinFile);


using insertCursorPositionFnc	= std::string(*)(std::string str, const u_int& vertPos, const MenuTemplates& mTemps,
									u_short level, const u_int& iterator);



void    CreateRandomBinDataset(std::string dir);
u_short ButtonsReading(u_int& horPosOut, u_int& vertPosOut);
void    FindingCursorPosition(u_int& vertPosOut, const u_int& heigh);
void    FindingCursorPosition(u_int& horPosOut, u_int& vertPosOut, const u_int& length, const u_int& height);
void	UserInput(ExamResults& userData);

void    ReadingBinaryFile(const std::string dir, std::list<ExamResults>& usersData, const u_int& uDataReadIndBegOut,
			const u_int& uDataReadIndCountOut, u_int& uDataCountOut);
void	WriteInBinaryFile(const std::string& dir);
bool	FindElement(const std::vector<u_int>& arr, const u_int& el);
void	DeletingFromBinaryFile(const std::string& dir, const u_int& droppedInd,
			const u_int& dataCount, writeInBinaryFileFnc writeInBinFileFnc);
void	ChangeDataInBinaryFile(const std::string& dir, const u_int& changeInd, const u_int& dataCount,
			const ExamResults& userData, writeInBinaryFileFnc writeInBinFile);


std::string InsertCursorPosition(std::string str, const u_int& vertPos, const MenuTemplates& mTemps,
	u_short level, const u_int& iterator);
void		PrintMainMenu(const u_int& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc);
void		PrintViewItem(std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
				insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc2 findCurPosFnc,
				readingBinaryFileFnc readBinFileFnc, writeInBinaryFileFnc writeInBinFileFnc,
				deletingFromBinaryFileFnc delFromBinFileFnc, changeDataInBinaryFileFnc changeInBinFileFnc, userInputFnc userInputFnc);
//
//void PrintSearchItem();
//
//void PrintAppendItem();
//
//void PrintStatisticsItem();
//
void		PrintCrateItem(std::string& dir, std::list<ExamResults>& userData, const MenuTemplates& mTemps,
				u_int& horPos, u_int& vertPos, insertCursorPositionFnc insCurPosFnc,
				buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc);



int main(int argc, char* argv[])
{
	using namespace std;

	setlocale(LC_ALL, "ru");

	string path = "random_data.bin";
	/*if (argc > 1){
		path = argv[1];
	}
	else {
		cout << "введите путь и название файла: ";
		getline(cin, path);
	}*/
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
	u_int horizontalPos = 1, verticalPos = 1;

	bool exitFlag = true;
	short codeItem(0);
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
				PrintViewItem(path, usersData, allMenuTemplatse,
					InsertCursorPosition, ButtonsReading,
					FindingCursorPosition, ReadingBinaryFile, 
					WriteInBinaryFile, DeletingFromBinaryFile,
					ChangeDataInBinaryFile, UserInput);
				break;

			case ITEM_SEARCH:
				//SearchItemPrinting();
				cout << "введите путь и название файла: ";
				getline(cin, path);
				break;

			case ITEM_APPEND:
				
				break;

			case ITEM_STATISTICS:
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

		cout << i + 1 << " " << setw(FIRST_NAME_FIELD_WIDTH) << users.firstName << " " << setw(LAST_NAME_FIELD_WIDTH) 
			<< users.lastName << " " << setw(MATCH_SCORE_FIELD_WIDTH) << users.mathScore <<
			" " << setw(RU_SCORE_FIELD_WIDTH) << users.ruLangScore << " " << setw(EN_SCORE_FIELD_WIDTH) << users.enLangScore << endl;
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
	else if (horPosOut > length && length == 1) {
		horPosOut = length;
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
		vertPosOut = vertPosOut % height;
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

void ReadingBinaryFile(const std::string dir, std::list<ExamResults>& usersData, const u_int& dataReadIndBeg,
	const u_int& dataReadIndCount, u_int& dataCountOut)
{
	using namespace std;

	// открытие файла
	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening" << endl;
	}

	ExamResultsBinary dataBuffer = {};


	// создание нового среза
	usersData.clear();
	usersData.resize(dataReadIndCount);
	inBinFile.seekg(dataReadIndBeg * dataBuffer.writeSize, ios::beg);

	auto userData = usersData.begin();
	for (u_int i = 0; i < dataReadIndCount; ++i, ++userData) {
	/*	cout << "outBinFile.fail() " << inBinFile.fail() << endl;
		cout << "outBinFile.rdstate() " << inBinFile.rdstate() << endl;
		if (inBinFile.rdstate() == ios::goodbit) {
			cout << "stream state is goodbit\n";
		}
		else if (inBinFile.rdstate() == ios::badbit) {
			cout << "stream state is badbit\n";
		}
		else if (inBinFile.rdstate() == ios::failbit) {
			cout << "stream state is failbit\n";
		}
		else if (inBinFile.rdstate() == ios::eofbit) {
			cout << "stream state is eofbit\n";
		}*/
		// чтение в структуру-буффер для бинарного файла
		inBinFile.read(dataBuffer.firstName, sizeof(*dataBuffer.firstName) * LENGTH_FIRST_NAME);
		inBinFile.read(dataBuffer.lastName, sizeof(*dataBuffer.lastName) * LENGTH_LAST_NAME);
		inBinFile.read(reinterpret_cast<char*>(&dataBuffer.mathScore), sizeof(dataBuffer.mathScore));
		inBinFile.read(reinterpret_cast<char*>(&dataBuffer.ruLangScore), sizeof(dataBuffer.ruLangScore));
		inBinFile.read(reinterpret_cast<char*>(&dataBuffer.enLangScore), sizeof(dataBuffer.enLangScore));
		
		// запись структуры в срез
		userData->firstName = string(dataBuffer.firstName);
		userData->lastName = string(dataBuffer.lastName);
		userData->mathScore = dataBuffer.mathScore;
		userData->ruLangScore = dataBuffer.ruLangScore;
		userData->enLangScore = dataBuffer.enLangScore;
		userData->totalScore = userData->mathScore + userData->ruLangScore + userData->enLangScore;
	}

	// чтение кол-ва данных
	dataCountOut = inBinFile.seekg(0, ios::end).tellg() / dataBuffer.writeSize;
	inBinFile.seekg(dataReadIndBeg * dataBuffer.writeSize, ios::beg);

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

void WriteInBinaryFile(const std::string& dir)
{
	using namespace std;

	// очистка файла
	ofstream binFile(dir, ios::binary | ios::trunc);
	binFile.close();

	string	dirBuf = dir.substr(0, dir.length() - 4) + "_buffer"s
				+ dir.substr(dir.length() - 4, 4);
	u_int	bufFileSize;
	ExamResultsBinary confVal;
	char* dataBuffer = new char[confVal.writeSize];

	// запись данных в основной файл из буферного файла	//

	// определение размера файла буффера
	ifstream inBufBinFile(dirBuf, ios::binary);
	if (!inBufBinFile.is_open()) {
		cerr << "Error opening input buffer file on time writing" << endl;
		system("pause");
		return;
	}
	bufFileSize = inBufBinFile.seekg(0, ios::end).tellg() / confVal.writeSize;
	inBufBinFile.seekg(0, ios::beg);

	// пропуск итерации в случае открытия пустого файла
	if (bufFileSize == 0) {
		inBufBinFile.close();
	}
	else {
		ofstream outBinFile(dir, ios::binary | ios::app);
		if (!outBinFile.is_open()) {
			cerr << "Error opening output file on time writing" << endl;
			system("pause");
			return;
		}

		// запись
		for (int j = 0; j < bufFileSize; ++j) {
			inBufBinFile.read(dataBuffer, confVal.writeSize);
			outBinFile.write(dataBuffer, confVal.writeSize);
		}
		inBufBinFile.close();
		outBinFile.close();
		//cout << "\n";
	}

	remove(dirBuf.c_str());	// удаление подфайла
}

void DeletingFromBinaryFile(const std::string& dir, const u_int& droppedInd,
		const u_int& dataCount, writeInBinaryFileFnc writeInBinFileFnc)
{
	using namespace std;

	// преременные для работы с подфайлом
	string	dirBuf = dir.substr(0, dir.length() - 4) + "_buffer"s 
				+ dir.substr(dir.length() - 4, 4);

	// преременные для работы с данными
	ExamResultsBinary confVal;
	char *dataBuffer = new char[confVal.writeSize];
	u_int dataInd(0);

	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input file on time deleting" << endl;
		system("pause");
	}

	// запись данных в подфайл //

	// очистка подфайла, если он уже существует
	ofstream outFile(dirBuf, ios::binary | ios::trunc);
	outFile.close();


	// запись
	ofstream outBufBinFile(dirBuf, ios::binary | ios::app);
	if (!outBufBinFile) {
		cerr << "Error opening output buffer file on time deleting" << endl;
		system("pause");
	}
	for (int j = 0; j < dataCount; ++j) {
		// удаление элемента, путем пропуска его записи в подфайл
		if (droppedInd != dataInd) {
			inBinFile.read(dataBuffer, confVal.writeSize);
			outBufBinFile.write(dataBuffer, confVal.writeSize);
		} else {
			//inBinFile.seekg(confVal.writeSize, ios::cur);	// пропуск чтения основного файла
			inBinFile.read(confVal.firstName, sizeof(*confVal.firstName) * LENGTH_FIRST_NAME);
			inBinFile.read(confVal.lastName, sizeof(*confVal.lastName) * LENGTH_LAST_NAME);
			inBinFile.read(reinterpret_cast<char*>(&confVal.mathScore), sizeof(confVal.mathScore));
			inBinFile.read(reinterpret_cast<char*>(&confVal.ruLangScore), sizeof(confVal.ruLangScore));
			inBinFile.read(reinterpret_cast<char*>(&confVal.enLangScore), sizeof(confVal.enLangScore));
			cout << dataInd << "delete structre: " << confVal.firstName << " " << confVal.lastName << " " << confVal.mathScore
				<< " " << confVal.ruLangScore << " " << confVal.enLangScore << endl;
			//inBinFile.read(dataBuffer, confVal.writeSize);
			//cout << "dataInd " << dataInd << " data " << dataBuffer << endl;
		}
		++dataInd;	// увличение абсолютного индекса всех данных
	}
	outBufBinFile.close();

	inBinFile.close();


	// запись в основной файл изменённых данных
	writeInBinFileFnc(dir);
}

void ChangeDataInBinaryFile(const std::string& dir, const u_int& changeInd, const u_int& dataCount, 
		const ExamResults& userData, writeInBinaryFileFnc writeInBinFile)
{
	using namespace std;

	// преременные для работы с подфайлом
	string	dirBuf = dir.substr(0, dir.length() - 4) + "_buffer"s
						+ dir.substr(dir.length() - 4, 4);

	// преременные для работы с данными
	ExamResultsBinary uDataBin;
	char* dataBuffer = new char[uDataBin.writeSize];
	u_int dataInd(0);

	// запись данных в подфайлы	//
	// очистка подфайла, если он уже существует
	ofstream outFile(dirBuf, ios::binary | ios::trunc);
	outFile.close();

	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input file on time change" << endl;
		system("pause");
	}
	// запись в подфайл
	ofstream outBufBinFile(dirBuf, ios::binary | ios::app);
	if (!outBufBinFile) {
		cerr << "Error opening output buffer file on time change" << endl;
		system("pause");
	}
	for (int j = 0; j < dataCount; ++j) {
		// изменение элемента
		if (changeInd != dataInd) {
			inBinFile.read(dataBuffer, uDataBin.writeSize);
			outBufBinFile.write(dataBuffer, uDataBin.writeSize);
		} else {
			inBinFile.seekg(uDataBin.writeSize, ios::cur);

			// копирование данных в структуру для записи
			strcpy_s(uDataBin.firstName, LENGTH_FIRST_NAME, userData.firstName.c_str());
			strcpy_s(uDataBin.lastName, LENGTH_LAST_NAME, userData.lastName.c_str());
			uDataBin.mathScore = userData.mathScore;
			uDataBin.ruLangScore = userData.ruLangScore;
			uDataBin.enLangScore = userData.enLangScore;

			// запись структуры
			outBufBinFile.write(uDataBin.firstName, sizeof(*uDataBin.lastName) * LENGTH_FIRST_NAME);
			outBufBinFile.write(uDataBin.lastName, sizeof(*uDataBin.firstName) * LENGTH_LAST_NAME);
			outBufBinFile.write((char*)&uDataBin.mathScore, sizeof(uDataBin.mathScore));
			outBufBinFile.write((char*)&uDataBin.ruLangScore, sizeof(uDataBin.ruLangScore));
			outBufBinFile.write((char*)&uDataBin.enLangScore, sizeof(uDataBin.enLangScore));
		}
		++dataInd; // увличение абсолютного индекса всех данных
		}
		
	outBufBinFile.close();
	inBinFile.close();

	// запись в основной файл изменённых данных
	writeInBinFile(dir);
}

std::string InsertCursorPosition(std::string str, const u_int& vertPos, const MenuTemplates& mTemps,
	u_short level, const u_int& iterator)
{
	using std::replace;

	if (level == LEVEL_MAIN)
	{
		switch ( vertPos )
		{
		case ITEM_VIEW:
			if ( mTemps.lineView == str ) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_SEARCH:
			if ( mTemps.lineSearch == str ) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_APPEND:
			if ( mTemps.lineAppend == str ) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_STATISTICS:
			if ( mTemps.lineStatistics == str ) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_CRATE:
			if ( mTemps.lineCreate == str ) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;
		case ITEM_EXIT:
			if ( mTemps.lineExit == str ) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;
		}
	}

	else if ( level == LEVEL_VIEW ) {
		if ( vertPos == 0 ) {
			if ( iterator == (vertPos + 1) ) {
				str.replace(0, 1, mTemps.cursor);
			}
		} 
		else {
			if ( iterator == vertPos ) {
				str.replace(0, 1, mTemps.cursor);
			}
		}
	}

	else if ( level == LEVEL_SEARCH ) {

	}

	else if ( level == LEVEL_APPEND ) {
		switch ( vertPos )
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

	cout << insCurPosFnc(mTemps.lineView, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineSearch, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineAppend, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineStatistics, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineCreate, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineExit, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
}

void PrintViewItem(std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
		insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc2 findCurPosFnc,
		readingBinaryFileFnc readBinFileFnc, writeInBinaryFileFnc writeInBinFileFnc,
		deletingFromBinaryFileFnc delFromBinFileFnc, changeDataInBinaryFileFnc changeInBinFileFnc, userInputFnc userInputFnc)
{
	using namespace std;

	u_int	dataCount(0);

	// чтение учетных записей
	readBinFileFnc(dir, usersData, 0, 0, dataCount);	// чтение кол-ва данных

	bool exitFlag = false;
	if (dataCount == 0) {
		cerr << "\tФАЙЛ ПУСТОЙ ИЛИ ЕГО НЕ СУЩЕСТВУЕТ!" << endl;
		system("pause");
		exitFlag = true;
	}

	u_short codeState(9);							// код клавиши
	u_int	vertPos(1);								// положение указателя

	u_int	dataPage(1);							// текущая страница
	u_int   prevDataPage(0);						// предыдущая страница
	u_int   dataPageCount(2);						// число страниц

	u_int	dataViewIndBeg(0);						// начальный индекс просмотра
	u_int	dataViewIndCount(DATA_FIELD_LENGTH);	// число эл. просмотра

	auto	uData = usersData.begin();				// эл. из среза
	u_int	uIndex;									// пременная для итератора вывода
	u_int	sliceIndBeg(0);							// начальный индекс среза
	u_int	sliceIndCount(0);						// число элементов среза
	u_int	sliceCur(0);							// текущий срез
	u_int	sliceCounts(0);							// число срезов

	bool changeFlag = false;						// влаг изменения эл.
	stringstream dataBuffer;						// потое для вывода

	// расчёт кол-ва выводимах данных
	if ((dataViewIndBeg + dataViewIndCount) > dataCount) {
		dataViewIndCount = dataCount - dataViewIndBeg; // изменение размера кол-ва элементов вывода
	}

	// расчёт кол-ва читаемых данных в срез	//
	if ((sliceIndBeg + sliceIndCount) > dataCount) {
		sliceIndCount = dataCount - sliceIndBeg; // изменение размера кол-ва элементов среза
	}

	while (!exitFlag)
	{
		//////////////////////////////////////////////
		// чтение и поиск всех необходимых индексов	//
		//////////////////////////////////////////////

		if (dataCount == 0) {
			exitFlag = true;
			break;
		}

		if (prevDataPage != dataPage || changeFlag) {
			// установка индексов среза вывода
			dataViewIndCount = DATA_FIELD_LENGTH;
			dataViewIndBeg = (dataPage - IND_CONV_FACTOR) * dataViewIndCount;

			// проверка длины среза вывода
			if ((dataViewIndBeg + dataViewIndCount) > dataCount) {
				dataViewIndCount = dataCount - dataViewIndBeg;
			}

			findCurPosFnc(dataPage, vertPos, dataPageCount, dataViewIndCount);

			prevDataPage = dataPage;
		}

		// чтение нового среза данных	//
		if ( (sliceIndBeg + sliceIndCount) < (((dataPage - 1) * DATA_FIELD_LENGTH) + dataViewIndCount) ||
			sliceIndBeg > ((dataPage - 1) * DATA_FIELD_LENGTH) || changeFlag )	// проверка выхода выводимых данных из локальных
		{
	
			// расчёт кол-ва подфайлов
			if (dataCount % SUBFILE_SIZE == 0) {
				sliceCounts = dataCount / SUBFILE_SIZE;
			}
			else if (dataCount > SUBFILE_SIZE) {
				sliceCounts = dataCount / SUBFILE_SIZE;
				++sliceCounts;
			}
			else {
				++sliceCounts;
			}


			// расчёт начального индекса данных подфайла для среза sliceIndBeg
			// расчёт текущего среза sliceCur
			sliceIndCount = SUBFILE_SIZE;
			if (sliceIndBeg > ((dataPage - 1) * DATA_FIELD_LENGTH) &&
				dataPage != 1 && dataPage != dataPageCount) // условие выхода индекса просмотра из среза в меньшую сторону
			{
				--sliceCur;
				sliceIndBeg = sliceCur * SUBFILE_SIZE;
			}
			else if ((sliceIndBeg + sliceIndCount) < (((dataPage - 1) * DATA_FIELD_LENGTH) + dataViewIndCount) &&
				dataPage != 1 && dataPage != dataPageCount)	// условие выхода индекса просмотра из среза в большую сторону
			{
				++sliceCur;
				sliceIndBeg = sliceCur * SUBFILE_SIZE;
			}
			else if ((sliceIndBeg + sliceIndCount) < (((dataPage - 1) * DATA_FIELD_LENGTH) + dataViewIndCount)
				&& dataPage == dataPageCount)	// условие выхода индекса просмотра из среза в большую сторону для последней страницы
			{
				sliceCur = sliceCounts - IND_CONV_FACTOR;
				sliceIndBeg = sliceCur * SUBFILE_SIZE;
			}
			else if ( dataPage == 1 || dataPage == 0 )	// условие выхода индекса просмотра из среза в меньшую сторону для первой страницы
			{
				sliceCur = 0;
				sliceIndBeg = 0;
			}


			// нахождение кол-ва читаемых данных в срез
			if ((sliceIndBeg + sliceIndCount) > dataCount) {
				sliceIndCount = dataCount - sliceIndBeg; // изменение размера кол-ва элементов среза
			}
			else if (sliceIndCount == 0) {
				sliceIndCount = SUBFILE_SIZE;
				--sliceCur;
			}

			// чтение среза данных
			readBinFileFnc(dir, usersData, sliceIndBeg, sliceIndCount, dataCount);

			if (dataCount == 0) {
				cerr << "\tФАЙЛ ПУСТОЙ ИЛИ ЕГО НЕ СУЩЕСТВУЕТ!" << endl;
				system("pause");
				exitFlag = true;
				break;
			}

			// нахождение количества страниц
			if (dataCount % DATA_FIELD_LENGTH == 0) {
				dataPageCount = dataCount / DATA_FIELD_LENGTH;
			}
			else if (dataCount % DATA_FIELD_LENGTH != 0 && dataCount > DATA_FIELD_LENGTH) {
				dataPageCount = dataCount / DATA_FIELD_LENGTH;
				++dataPageCount;
			}
			else {
				dataPageCount = 1;
			}

			changeFlag = false;
		}

		// установка индекса итератора контейнера с срезом данных
		uData = usersData.begin();
		if (sliceCur != sliceCounts - IND_CONV_FACTOR) {
			advance(uData, dataViewIndBeg % sliceIndCount);
		}
		else {
			advance(uData, (dataViewIndBeg - sliceIndBeg));
		}

		//////////////////////////////////////////////////
		//	вывод и обработка пользовательских данных	//
		//////////////////////////////////////////////////

		// заполнение промежуточного потока для вывода таблицы
		dataBuffer << mTemps.tableSeparatorHorizontal << "\n" << mTemps.tableHeader << "\n" << mTemps.tableSeparatorHorizontal << "\n";
		for (uIndex = dataViewIndBeg; uIndex <= (dataViewIndBeg + dataViewIndCount - IND_CONV_FACTOR); ++uIndex, ++uData) {
			u_int printInd;
			if ( dataViewIndBeg != 0 && dataPage != dataPageCount ) {
				printInd = (uIndex % dataViewIndCount) + 1;
			}
			else if ( dataPage == dataPageCount ) {
				printInd = uIndex - ( DATA_FIELD_LENGTH * (dataPageCount - 1) ) + 1;
			}
			else {
				printInd = uIndex + 1;
			} 
			dataBuffer << insCurPosFnc(mTemps.space, vertPos, mTemps, LEVEL_VIEW, printInd)
				<< mTemps.tableSeparatorVertical << setw(COUNTER_FIELD_WIDTH) << right << uIndex + 1 << mTemps.tableSeparatorVertical
				<< setw(FIRST_NAME_FIELD_WIDTH) << left << uData->firstName << mTemps.tableSeparatorVertical
				<< setw(LAST_NAME_FIELD_WIDTH) << uData->lastName << mTemps.tableSeparatorVertical
				<< setw(MATCH_SCORE_FIELD_WIDTH) << right << uData->mathScore << mTemps.tableSeparatorVertical
				<< setw(RU_SCORE_FIELD_WIDTH) << right << uData->ruLangScore << mTemps.tableSeparatorVertical
				<< setw(EN_SCORE_FIELD_WIDTH) << right << uData->enLangScore << mTemps.tableSeparatorVertical
				<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << uData->totalScore << mTemps.tableSeparatorVertical << "\n"
				<< mTemps.tableSeparatorHorizontal << "\n";

			//// защита от выхода за диапазон контейнера
			//if (uIndex != (dataViewIndBeg + dataViewIndCount - IND_CONV_FACTOR)) {
			//	++uData;
			//}
		}

		dataBuffer << mTemps.tablePage << setw(PAGE_FIELD_WIDTH) << right << dataPage << mTemps.tablePageSeparator <<
			left << dataPageCount << "\n";
		dataBuffer << mTemps.itemViewDescription << endl;

		// перевод данных из буфера в поток вывода 
		system("cls");
		cout << dataBuffer.str();
		dataBuffer.str("");
		dataBuffer.clear();

		// обработка клавиш
		codeState = buttReadFnc(dataPage, vertPos);
		findCurPosFnc(dataPage, vertPos, dataPageCount, dataViewIndCount);
		
		// переменные для изменения данных
		long int changeInd(0);
		ExamResults changeUser;

		switch (codeState)
		{
		case KEY_ENTER: // изменение эл в базе
			system("cls");

			changeInd = dataViewIndCount - vertPos + IND_CONV_FACTOR;
			advance(uData, (-1)* changeInd);
			cout << "\t\t\t\t редактируемая учетная запись \n"
				<< mTemps.tableSeparatorHorizontal << " " << mTemps.cursor << mTemps.tableSeparatorVertical
				<< setw(COUNTER_FIELD_WIDTH) << right << dataViewIndBeg + vertPos << mTemps.tableSeparatorVertical
				<< setw(FIRST_NAME_FIELD_WIDTH) << left << uData->firstName << mTemps.tableSeparatorVertical
				<< setw(LAST_NAME_FIELD_WIDTH) << uData->lastName << mTemps.tableSeparatorVertical
				<< setw(MATCH_SCORE_FIELD_WIDTH) << right << uData->mathScore << mTemps.tableSeparatorVertical
				<< setw(RU_SCORE_FIELD_WIDTH) << right << uData->ruLangScore << mTemps.tableSeparatorVertical
				<< setw(EN_SCORE_FIELD_WIDTH) << right << uData->enLangScore << mTemps.tableSeparatorVertical
				<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << uData->totalScore << mTemps.tableSeparatorVertical << "\n"
				<< mTemps.tableSeparatorHorizontal << endl;

			cout << "\n\t\t введите новые данные: ";

			userInputFnc(changeUser);
			changeInBinFileFnc(dir, ((dataPage - 1)* DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR,
				dataCount, changeUser, writeInBinFileFnc);

			changeFlag = true;
			break;

		case KEY_DELETE: // удадение эл. из базы
		
			delFromBinFileFnc(dir, ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR,
				dataCount, writeInBinFileFnc);

			if (vertPos == dataViewIndCount && dataPage == dataPageCount) {
				--vertPos;
			}

			--dataCount;
			--dataViewIndCount;
			if (dataViewIndCount == 0) {
				--dataPageCount;
				--dataPage;
			}

			changeFlag = true;
			break;

		case KEY_ESCAPE: // выход из ф. просмотра
			exitFlag = true;
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
		cout << insCurPosFnc(mTemps.appLineYes, vertPos, mTemps, LEVEL_APPEND, 0) << endl;
		cout << insCurPosFnc(mTemps.appLineNo, vertPos, mTemps, LEVEL_APPEND, 0) << endl;

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