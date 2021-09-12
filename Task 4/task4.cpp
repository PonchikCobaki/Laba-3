/*
	

*/


#include "Config.h"
#include "Keyboard.h"
#include "CMenu.h"
#include "BinFO.h"



int main(int argc, char* argv[])
{
	using namespace std;

	setlocale(LC_ALL, "ru");

	// выбор пути файла
	string path;
	//string path = "random_data.bin";	//to do dbg
	if (argc > 1){
		path = argv[1];
	}
	else {
		cout << "введите путь и название файла: ";
		getline(cin, path);
	}

	// установка нормативных баллов
	u_short passingScore = 100;
	u_short minMathScore = 0, minRuLangScore = 0, minEnLangScore = 0;

	cout << "введите сумму проходных баллов: ";
	cin >> passingScore;
	cout << "введите минимальное значение баллов по матаметике: ";
	cin >> minMathScore;
	cout << "введите минимальное значение баллов по русскому языку: ";
	cin >> minRuLangScore;
	cout << "введите минимальное значение баллов по английскому: ";
	cin >> minEnLangScore;

	//	основные переменные 
	list<ExamResults> usersData;				//	контейнер для неупорядоченного хранения данных пользователя в памяти
	u_int horizontalPos = 1, verticalPos = 1;	//	пересенные положения меню

	bool	exitFlag = true;	//	флаг выхода из программы 
	short	codeItem(0);		//	состояние клавиатуры
	
	while (exitFlag)
	{
		PrintMainMenu(verticalPos, allMenuTemplates, InsertCursorPosition);	// вывод основного меню

		codeItem = ButtonsReading(horizontalPos, verticalPos);					// чтение клавиатуры
		FindingCursorPosition(verticalPos, static_cast<int>(HEIGHT_ITEM_MAIN));	// установка курсора

		if (codeItem == KEY_ENTER)
		{
			switch (verticalPos)
			{
			case ITEM_VIEW:
				PrintTable(path, usersData, allMenuTemplates,
					InsertCursorPosition, SelectionMenuPrinting, ButtonsReading,
					FindingCursorPosition, FindingCursorPosition,
					ReadingBinaryFile, WriteInBinaryFile, DeletingFromBinaryFile,
					ChangeDataInBinaryFile, AppendInBinaryFile, UserInput);
				break;

			case ITEM_STATISTICS:
				ComputeStatistics(passingScore, minMathScore, minRuLangScore, minEnLangScore, path, usersData,
					ReadingBinaryFile, PrintTable, InsertCursorPosition, ButtonsReading, FindingCursorPosition);
				break;

			case ITEM_CREATE:
				PrintCreateItem(path, InsertCursorPosition,	ButtonsReading, FindingCursorPosition, SelectionMenuPrinting, UserInput);
				//CreateRandomBinDataset(path);
				break;

			case ITEM_EXIT:
				exitFlag = false;

			}
		}
	}


	return 0;
}