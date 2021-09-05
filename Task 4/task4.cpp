﻿/*
	

*/


#include "Config.h"
#include "Keyboard.h"
#include "CMenu.h"
#include "BinFO.h"



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

	u_short passingScore = 100;
	u_short minMathScore = 0, minRuLangScore = 0, minEnLangScore = 0;

	/*cout << "введите сумму проходных баллов: ";
	cin >> passingScore;
	cout << "введите минимальное значение баллов по матаметике: ";
	cin >> minMathScore;
	cout << "введите минимальное значение баллов по русскому языку: ";
	cin >> minRuLangScore;
	cout << "введите минимальное значение баллов по английскому: ";
	cin >> minEnLangScore;*/

	list<ExamResults> usersData;
	u_int horizontalPos = 1, verticalPos = 1;

	bool exitFlag = true;
	short codeItem(0);
	//ReadingBinaryFile(path, usersData, userDataViewIndexBegin, userDataViewIndexCount, userDataCount);
	
	while (exitFlag)
	{
		PrintMainMenu(verticalPos, allMenuTemplates, InsertCursorPosition);

		codeItem = ButtonsReading(horizontalPos, verticalPos);
		FindingCursorPosition(verticalPos, static_cast<int>(HEIGHT_ITEM_MAIN));
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
					ReadingBinaryFile, PrintTable, allMenuTemplates, InsertCursorPosition, ButtonsReading, FindingCursorPosition);
				break;

			case ITEM_CREATE:
				//PrintCreateItem(path, allMenuTemplates, InsertCursorPosition,
				//	ButtonsReading, FindingCursorPosition, SelectionMenuPrinting, UserInput);
				CreateRandomBinDataset(path);
				break;

			case ITEM_EXIT:
				exitFlag = false;

			}
		}
	}


	return 0;
}







