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

	u_short passingScore;
	u_short minMathScore;
	u_short minRuLangScore;
	u_short minEnLangScore;

	cout << "введите сумму проходных баллов: ";
	cin >> passingScore;
	cout << "введите минимальное значение баллов по матаметике: ";
	cin >> minMathScore;
	cout << "введите минимальное значение баллов по русскому языку: ";
	cin >> minRuLangScore;
	cout << "введите минимальное значение баллов по английскому: ";
	cin >> minEnLangScore;

	MenuTemplates allMenuTemplates = {
		">",
		" ",

		"навигация по меню:  arrow up/down - перемещение вверх/вниз, Enter - выбор пункта",
		"  просмотр файла",
		"  поиск по файлу",
		"  вывод статистики",
		"  создание нового файла",
		"  выход",

		"навигация: arrow Up/Down - перемещение вверх/вниз, arrow Right/Left - перемещение вправо/вле-\n"
		"во, Esc - возврат в меню, Enter - выбор элемента для редактирования нажмите любую клавишу для\n"
		"ввода нового элемента, Delite - удаление элемента",
		" |   №#   |           имя           |         фамилия         | матем | русс | англ | сумма |",
		" +--------+-------------------------+-------------------------+-------+------+------+-------+",
		"|",
		"                                   страница ",
		"/",

		"  да",
		"  нет",
	};

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
				PrintViewItem(path, usersData, allMenuTemplates,
					InsertCursorPosition, SelectionMenuPrinting, ButtonsReading,
					FindingCursorPosition, FindingCursorPosition,
					ReadingBinaryFile, WriteInBinaryFile, DeletingFromBinaryFile,
					ChangeDataInBinaryFile, AppendInBinaryFile, UserInput);
				break;

			case ITEM_SEARCH:
				//SearchItemPrinting();
				cout << "введите путь и название файла: ";
				getline(cin, path);
				break;

			case ITEM_STATISTICS:
				CreateRandomBinDataset(path);
				break;

			case ITEM_CRATE:
				PrintCreateItem(path, allMenuTemplates, InsertCursorPosition,
					ButtonsReading, FindingCursorPosition, SelectionMenuPrinting, UserInput);
				//CreateRandomBinDataset(path);
				break;

			case ITEM_EXIT:
				exitFlag = false;

			}
		}
	}


	return 0;
}



//void PrintTable() 
//{
//	// заполнение промежуточного потока для вывода таблицы
//	dataBuffer << mTemps.tableSeparatorHorizontal << "\n" << mTemps.tableHeader << "\n" << mTemps.tableSeparatorHorizontal << "\n";
//	for (uIndex = dataViewIndBeg; uIndex <= (dataViewIndBeg + dataViewIndCount - IND_CONV_FACTOR); ++uIndex, ++uData) {
//		u_int printInd;
//		if (dataViewIndBeg != 0 && dataPage != dataPageCount) {
//			printInd = (uIndex % dataViewIndCount) + 1;
//		}
//		else if (dataPage == dataPageCount) {
//			printInd = uIndex - (DATA_FIELD_LENGTH * (dataPageCount - 1)) + 1;
//		}
//		else {
//			printInd = uIndex + 1;
//		}
//		dataBuffer << insCurPosFnc(mTemps.space, vertPos, mTemps, LEVEL_VIEW, printInd)
//			<< mTemps.tableSeparatorVertical << setw(COUNTER_FIELD_WIDTH) << right << uIndex + 1 << mTemps.tableSeparatorVertical
//			<< setw(FIRST_NAME_FIELD_WIDTH) << left << uData->firstName << mTemps.tableSeparatorVertical
//			<< setw(LAST_NAME_FIELD_WIDTH) << uData->lastName << mTemps.tableSeparatorVertical
//			<< setw(MATCH_SCORE_FIELD_WIDTH) << right << uData->mathScore << mTemps.tableSeparatorVertical
//			<< setw(RU_SCORE_FIELD_WIDTH) << right << uData->ruLangScore << mTemps.tableSeparatorVertical
//			<< setw(EN_SCORE_FIELD_WIDTH) << right << uData->enLangScore << mTemps.tableSeparatorVertical
//			<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << uData->totalScore << mTemps.tableSeparatorVertical << "\n"
//			<< mTemps.tableSeparatorHorizontal << "\n";
//	}
//
//	dataBuffer << mTemps.tablePage << setw(PAGE_FIELD_WIDTH) << right << dataPage << mTemps.tablePageSeparator <<
//		left << dataPageCount << "\n";
//	dataBuffer << mTemps.itemViewDescription << endl;
//
//	// перевод данных из буфера в поток вывода 
//	system("cls");
//	cout << dataBuffer.str();
//	dataBuffer.str("");
//	dataBuffer.clear();
//}



