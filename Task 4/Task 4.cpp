#include <conio.h>
#include <sstream>
#include <string>
#include <iostream>
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
	CODE_LEFT = 77,
	CODE_RIGHT = 75,
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

enum IteratorSteps
{
	HORIZONTAL_STEP = 1,
	VERTICAL_STEP = 1,
};

enum MenuLevels
{
	LEVEL_MAIN,
	LEVEL_VIEW,
	LEVEL_SEARCH,
	LEVEL_APPEND
};
#pragma pack(1)
static struct MenuTemplates
{
	std::string title;
	std::string cursor;
	std::string lineView;
	std::string lineSearch;
	std::string lineAppend;
	std::string lineStatistics;
	std::string lineCreate;
	std::string lineExit;
	std::string appLineYes;
	std::string appLineNo;
};
#pragma pack (pop)

#pragma pack(1)
static struct ExamResults {
	std::string firstName;
	std::string lastName;
	int mathScore;
	int ruLangScore;
	int enLangScore;
};
#pragma pack (pop)

using findingCursorPositionFnc = void(*)(short&, short&, int, int);
using insertCursorPositionFnc = std::string(*)(std::string, const short&, const MenuTemplates&, short);
using buttonsReadingFnc = short(*)(short&, short&);

void CreateRandomBinDataset(std::string dir, int size);
short ButtonsReading(short& horPosOut, short& VertPosOut);
void FindingCursorPosition(short& horPosOut, short& vertPosOut, int length, int heigh);

std::string InsertCursorPosition(std::string str, const short& vertPos, const MenuTemplates& mTemps, short level);
void MainMenuPrinting(const short& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc);

void ViewItemPrinting(std::string dir, std::list<ExamResults>& userData);
//
//void SearchItemPrinting();
//
//void AppendItemPrinting();
//
//void StatisticsItemPrinting();
//
void CrateItemPrinting(std::string& dir, std::list<ExamResults>& userData, const MenuTemplates& mTemps, short& horPos,
	short& vertPos, insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc findCurPosFnc);

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
	path = "random_data.bin";
	cout << path << endl;
	system("pause");
	//CreateRandomBinDataset(path, 10);
	//cout << cin.peek() << '\t';

	MenuTemplates menuMain = {
		"навигация по меню: кнопки up/down - перемещение по меню, Enter - выбор пункта",
		">",
		" 1.просмотр файла",
		" 2.поиск по файлу",
		" 3.добавление в файл",
		" 4.вывод статистики",
		" 5.создание нового файла",
		" 6.выход",
		" 1.да",
		" 2.нет"
	};

	list<ExamResults> userData;
	short horizontalPos = 1, verticalPos = 1;
	bool exitFlag = true;
	short codeItem = 0;

	while (exitFlag)
	{
		MainMenuPrinting(verticalPos, menuMain, InsertCursorPosition);
		codeItem = ButtonsReading(horizontalPos, verticalPos);
		FindingCursorPosition(horizontalPos, verticalPos, static_cast<int>(LENGTH_ITEM_DEFAULT), static_cast<int>(HEIGHT_ITEM_MAIN));
		if (codeItem == KEY_ENTER)
		{
			switch (verticalPos)
			{
			case ITEM_VIEW:
				ViewItemPrinting(path, userData);
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
				CrateItemPrinting(path, userData, menuMain, horizontalPos, verticalPos, InsertCursorPosition,
					ButtonsReading, FindingCursorPosition);
				break;

			case ITEM_EXIT:
				exitFlag = false;

			}
		}
	}

	return 0;
}

void CreateRandomBinDataset(std::string dir, int size)
{
	using namespace std;
	random_device rd;
	mt19937 mersenne(rd());

	string firstNames[] = { "Иван", "Пётр", "Василий", "Марат", "Григорий",
		"Ильназ", "Али", "Максим", "Артём", "Джек" };
	string lastNames[] = { "Иванов", "Пётров", "Васильевич", "Айзатов",
		"Шайхутдинов", "Кларксон", "Ахматович", "Белых", "Понасенков", "Хабибулин" };

	cout << sizeof(ExamResults) << endl;
	ExamResults users;
	ofstream outBinFile(dir, ios::binary);
	cout << sizeof(users) << endl;
	for (int i = 0; i < size; i++) {
		users.firstName = firstNames[mersenne() % 10];
		users.lastName = lastNames[mersenne() % 10];
		users.mathScore = mersenne() % 101;
		users.ruLangScore = mersenne() % 101;
		users.enLangScore = mersenne() % 101;

		outBinFile.write((char*)&users, sizeof(ExamResults));

		cout << users.firstName << " " << users.lastName << "\t" << users.mathScore <<
			"\t" << users.ruLangScore << "\t" << users.enLangScore << endl;
	}

	outBinFile.close();

	system("pause");
}

short ButtonsReading(short& horPosOut, short& vertPosOut)
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

void FindingCursorPosition(short& horPosOut, short& vertPosOut, int length, int heigh)
{
	if (horPosOut < 1) {
		horPosOut = (length - abs(horPosOut)) % (length + 1);
	}
	else if (horPosOut == length + 1) {
		horPosOut /= length;
	}

	if (vertPosOut < 1) {
		vertPosOut = (heigh - abs(vertPosOut)) % (heigh + 1);
	}
	else if (vertPosOut == heigh + 1) {
		vertPosOut /= heigh;
	}
}

std::string InsertCursorPosition(std::string str, const short& vertPos, const MenuTemplates& mTemps, short level)
{
	using std::replace;

	if (level == LEVEL_MAIN) {
		switch (vertPos)
		{
		case ITEM_VIEW:
			if (mTemps.lineView == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_SEARCH:
			if (mTemps.lineSearch == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_APPEND:
			if (mTemps.lineAppend == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_STATISTICS:
			if (mTemps.lineStatistics == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_CRATE:
			if (mTemps.lineCreate == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;
		case ITEM_EXIT:
			if (mTemps.lineExit == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;
		}
	}
	else if (level == LEVEL_VIEW) {

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

void MainMenuPrinting(const short& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc)
{
	using namespace std;

	system("cls");

	cout << insCurPosFnc(mTemps.lineView, vertPos, mTemps, LEVEL_MAIN) << endl;
	cout << insCurPosFnc(mTemps.lineSearch, vertPos, mTemps, LEVEL_MAIN) << endl;
	cout << insCurPosFnc(mTemps.lineAppend, vertPos, mTemps, LEVEL_MAIN) << endl;
	cout << insCurPosFnc(mTemps.lineStatistics, vertPos, mTemps, LEVEL_MAIN) << endl;
	cout << insCurPosFnc(mTemps.lineCreate, vertPos, mTemps, LEVEL_MAIN) << endl;
	cout << insCurPosFnc(mTemps.lineExit, vertPos, mTemps, LEVEL_MAIN) << endl;
}

void ViewItemPrinting(std::string dir, std::list<ExamResults>& userData)
{
	using namespace std;

	system("cls");

	ifstream inf(dir, ios::binary);
	if (!inf) {
		cerr << "Error opening" << endl;
		exit(1);
	}

	int n = inf.seekg(0, ios::end).tellg() / sizeof(ExamResults);
	inf.seekg(0, ios::beg);
	ExamResults bufData;

	for (int i = 0; i < (n * 5); ++i) {
		inf.read((char*)&bufData, sizeof(ExamResults));
		userData.push_back(bufData);
	}
	cout << inf.tellg() << endl;

	int count = 0;
	for (const auto& id : userData) {
		cout << count << " "<< id.firstName << " " << id.lastName << " " << id.mathScore 
			<< " " << id.ruLangScore <<" " << id.enLangScore << endl;
		++count;
	}
	inf.close();

	system("pause");
}

void CrateItemPrinting(std::string& dir, std::list<ExamResults>& userData, const MenuTemplates& mTemps, short & horPos, 
	short& vertPos, insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc findCurPosFnc)
{
	using namespace std;

	bool flagExit = false;
	short codeState;
	vertPos = 1;

	while (!flagExit)
	{
		system("cls");
		cout << "создать новый файл?" << endl;
		cout << insCurPosFnc(mTemps.appLineYes, vertPos, mTemps, LEVEL_APPEND) << endl;
		cout << insCurPosFnc(mTemps.appLineNo, vertPos, mTemps, LEVEL_APPEND) << endl;

		codeState = buttReadFnc(horPos, vertPos);
		findCurPosFnc(horPos, vertPos, LENGTH_ITEM_DEFAULT, HEIGHT_ITEM_APPEND);

		if (codeState == KEY_ENTER) {
			switch (vertPos)
			{
			case (ITEM_APPEND_YES):
				system("cls");
				cout << "введите путь и имя новго файла: ";
				getline(cin, dir); 
				cout << endl;
				flagExit = true;
				break;

			case (ITEM_APPEND_NO):
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