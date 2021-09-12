#include "CMenu.h"

// шаблоны пунктов меню
MenuTemplates allMenuTemplates = {
	">>",
	" ",
	"%",

	"навигация по меню:  arrow up/down - перемещение вверх/вниз, Enter - выбор пункта",
	" ПРОСМОТР ФАЙЛА",
	" СТАТИСТИКА",
	" НОВЫЙ ФАЙЛ",
	" ВЫХОД",

	"навигация: arrow Up/Down - перемещение вверх/вниз, arrow Right/Left - перемещение вправо/вле-\n"
	"во, Esc - возврат в меню, Enter - выбор элемента для редактирования нажмите любую клавишу для\n"
	"ввода нового элемента, Delite - удаление элемента",
	" |   №#   |           имя           |         фамилия         | матем | русс | англ | сумма |",
	" +--------+-------------------------+-------------------------+-------+------+------+-------+",
	"|",
	"                                   страница ",
	"/",

	"навигация по меню: arrow Right / Left - перемещение вправо/влево, Esc - возврат\n"
	"в главное меню",
	"\t\t\tСписок абитуриентов имеющих наивысший балл",
	"Процент абитуриентов не выдержавших конкурса: ",


	"  да",
	"  нет",
};

//	функция предотвращающая выход переменной верктикального указателя за пределы [V_B_P,height]
void FindingCursorPosition(u_int& vertPosOut, const u_int& height)
{
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
//	функция предотвращающая выход переменной верктикального и горизонтального указателя за пределы [V_B_P, height], [H_B_P, length]
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

//	заменяет пробел на указатель
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
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_STATISTICS:
			if (mTemps.lineStatistics == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_CREATE:
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
		if (vertPos == 0) {
			if (iterator == (vertPos + 1)) {
				str.replace(0, 1, mTemps.cursor);
			}
		}
		else {
			if (iterator == vertPos) {
				str.replace(0, 1, mTemps.cursor);
			}
		}
	}

	else if (level == LEVEL_SELECTION) {
		switch (vertPos)
		{
		case ITEM_SELECTION_YES:
			if (mTemps.selLineYes == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;

		case ITEM_SELECTION_NO:
			if (mTemps.selLineNo == str) {
				str.replace(0, 1, mTemps.cursor);
			}
			break;
		}
	}

	return str;
}

//	меню выбора да/нет
bool SelectionMenuPrinting(std::string title, insertCursorPositionFnc insCurPosFnc,
		buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc)
{
	using namespace std;

	u_short codeState;
	u_int	horPos(HORIZONTAL_BEGIN_POINT);
	u_int	vertPos(VERTICAL_BEGIN_POINT);

	while (true) {
		system("cls");
		cout << title << "\n";
		cout << insCurPosFnc(allMenuTemplates.selLineYes, vertPos, allMenuTemplates, LEVEL_SELECTION, 0) << "\n";
		cout << insCurPosFnc(allMenuTemplates.selLineNo, vertPos, allMenuTemplates, LEVEL_SELECTION, 0) << endl;

		codeState = buttReadFnc(horPos, vertPos);
		findCurPosFnc(vertPos, HEIGHT_ITEM_SELECTION);

		if (codeState == KEY_ENTER) {
			switch (vertPos)
			{
			case ITEM_SELECTION_YES:
				return true;

			case ITEM_SELECTION_NO:
				return false;
			}
		}
	}

}

//	основное меню
void PrintMainMenu(const u_int& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc)
{
	using namespace std;

	system("cls");

	cout << insCurPosFnc(mTemps.lineView, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineStatistics, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineCreate, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineExit, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
}

// построение таблицы с функциями редактирования
void PrintTable(std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
		insertCursorPositionFnc insCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc,
		buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc1, findingCursorPositionFnc2 findCurPosFnc2,
		readingBinaryFileFnc readBinFileFnc, writeInBinaryFileFnc writeInBinFileFnc,
		deletingFromBinaryFileFnc delFromBinFileFnc, changeDataInBinaryFileFnc changeInBinFileFnc,
		appendInBinaryFileFnc appInBinFileFnc, userInputFnc userInputFnc)
{
	using namespace std;

	u_int	dataCount(0);

	// чтение учетных записей
	readBinFileFnc(dir, usersData, 0, 0, dataCount);	// чтение кол-ва данных

	bool exitFlag = false;
	if (dataCount == 0) {
		cerr << "\n\t ФАЙЛ ПУСТОЙ ИЛИ ЕГО НЕ СУЩЕСТВУЕТ!" << endl;
		system("pause");
		exitFlag = true;
	}

	u_short codeState;								// код клавиши
	u_int	vertPos(VERTICAL_BEGIN_POINT);			// положение указателя

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

	bool changeFlag = false;						// флаг изменения эл.
	stringstream dataBuffer;						// буфер для вывода

	// переменные для изменения данных
	long int changeInd(0);
	bool offset;
	ExamResults changeUser;

	// расчёт кол-ва выводимых данных
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

			findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);

			prevDataPage = dataPage;
		}

		// чтение нового среза данных	//
		if ((sliceIndBeg + sliceIndCount) < (((dataPage - 1) * DATA_FIELD_LENGTH) + dataViewIndCount) ||
			sliceIndBeg > ((dataPage - 1) * DATA_FIELD_LENGTH) || changeFlag)	// проверка выхода выводимых данных из локальных
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
			else if (dataPage == 1 || dataPage == 0)	// условие выхода индекса просмотра из среза в меньшую сторону для первой страницы
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
				cerr << "\n\tФАЙЛ ПУСТОЙ ИЛИ ЕГО НЕ СУЩЕСТВУЕТ!" << endl;
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
		//				вывод данных					//
		//////////////////////////////////////////////////

		// заполнение промежуточного потока для вывода таблицы
		dataBuffer << mTemps.tableSeparatorHorizontal << "\n" << mTemps.tableHeader << "\n" << mTemps.tableSeparatorHorizontal << "\n";
		for (uIndex = dataViewIndBeg; uIndex <= (dataViewIndBeg + dataViewIndCount - IND_CONV_FACTOR); ++uIndex, ++uData) {
			u_int printInd;
			if (dataViewIndBeg != 0 && dataPage != dataPageCount) {
				printInd = (uIndex % dataViewIndCount) + 1;
			}
			else if (dataPage == dataPageCount) {
				printInd = uIndex - (DATA_FIELD_LENGTH * (dataPageCount - 1)) + 1;
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
		}

		dataBuffer << mTemps.tablePage << setw(PAGE_FIELD_WIDTH) << right << dataPage << mTemps.tablePageSeparator <<
						left << dataPageCount << "\n";
		dataBuffer << mTemps.itemViewDescription << endl;

		// перевод данных из буфера в поток вывода 
		system("cls");
		cout << dataBuffer.str();
		dataBuffer.str("");
		dataBuffer.clear();

		//////////////////////////////////////////////////
		//			обработка клавиатуры				//
		//////////////////////////////////////////////////
		 

		// обработка клавиш
		codeState = buttReadFnc(dataPage, vertPos);
		findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);

		switch (codeState)
		{
		case KEY_DELETE: // удаление эл. из базы

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

		case KEY_ENTER: // изменение эл в базе
			system("cls");

			changeInd = dataViewIndCount - vertPos + IND_CONV_FACTOR;
			advance(uData, (-1) * changeInd);
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
			changeInBinFileFnc(dir, ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR,
				dataCount, changeUser, writeInBinFileFnc);

			changeFlag = true;
			break;

		case KEY_OTHER: // добваление данных

			changeInd = dataViewIndCount - vertPos + IND_CONV_FACTOR;
			advance(uData, (-1) * changeInd);

			dataBuffer << mTemps.tableSeparatorHorizontal << " " << mTemps.cursor << mTemps.tableSeparatorVertical
				<< setw(COUNTER_FIELD_WIDTH) << right << dataViewIndBeg + vertPos << mTemps.tableSeparatorVertical
				<< setw(FIRST_NAME_FIELD_WIDTH) << left << uData->firstName << mTemps.tableSeparatorVertical
				<< setw(LAST_NAME_FIELD_WIDTH) << uData->lastName << mTemps.tableSeparatorVertical
				<< setw(MATCH_SCORE_FIELD_WIDTH) << right << uData->mathScore << mTemps.tableSeparatorVertical
				<< setw(RU_SCORE_FIELD_WIDTH) << right << uData->ruLangScore << mTemps.tableSeparatorVertical
				<< setw(EN_SCORE_FIELD_WIDTH) << right << uData->enLangScore << mTemps.tableSeparatorVertical
				<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << uData->totalScore << mTemps.tableSeparatorVertical << "\n"
				<< mTemps.tableSeparatorHorizontal << endl;

			offset = !selMenuPrintingFnc(dataBuffer.str() + "добавлениь на место куказанной учетной записи? иначе на место выше",
						insCurPosFnc, buttReadFnc, findCurPosFnc1); // выбор метса записи

			// очистка буффера
			dataBuffer.str("");
			dataBuffer.clear();

			cout << "\n\t\t введите новые данные: ";

			userInputFnc(changeUser);
			appInBinFileFnc(dir, ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR, offset,
				dataCount, changeUser, writeInBinFileFnc);
			++dataCount;
			changeFlag = true;
			break;

		case KEY_ESCAPE: // выход из ф. просмотра
			exitFlag = true;
			break;
		}
	}

}
// упрощённая версия для построение таблицы 
void PrintTable(const u_int& failCount, std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
		insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc2 findCurPosFnc2)
{
	using namespace std;

	u_int dataCount(usersData.size());

	bool exitFlag(false);						

	if (dataCount == 0) {
		cout << "\t\t\tнет прошедших абитуриентов\n";
		system("pause");
		exitFlag = true;
		return;
	}
	u_short codeState;							// не имеет смысла
	u_int vertPos;
	u_int dataPage(1);							// текущая страница
	u_int prevDataPage(0);						// предыдущая страница
	u_int dataPageCount(2);						// число страниц

	u_int dataViewIndBeg(0);					// начальный индекс просмотра
	u_int dataViewIndCount(DATA_FIELD_LENGTH);	// число эл. просмотра

	auto  uData = usersData.begin();			// эл. из среза
	u_int uIndex;								// пременная для итератора вывода
	u_int sliceIndBeg(0);						// начальный индекс среза
	u_int sliceIndCount(0);						// число элементов среза
	u_int sliceCur(0);							// текущий срез
	u_int sliceCounts(0);						// число срезов

	stringstream dataBuffer;					// буфер для вывода

	// расчёт кол-ва выводимых данных
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
			cout << "\t\t\tнет прошедших абитуриентов\n";
			system("pause");
			exitFlag = true;
			break;
		}


		if (prevDataPage != dataPage) {
			// установка индексов среза вывода
			dataViewIndCount = DATA_FIELD_LENGTH;
			dataViewIndBeg = (dataPage - IND_CONV_FACTOR) * dataViewIndCount;

			// проверка длины среза вывода
			if ((dataViewIndBeg + dataViewIndCount) > dataCount) {
				dataViewIndCount = dataCount - dataViewIndBeg;
			}

			findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);

			prevDataPage = dataPage;
		}

		// чтение нового среза данных	//
		if ((sliceIndBeg + sliceIndCount) < (((dataPage - 1) * DATA_FIELD_LENGTH) + dataViewIndCount) ||
			sliceIndBeg > ((dataPage - 1) * DATA_FIELD_LENGTH))	// проверка выхода выводимых данных из локальных
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
			else if (dataPage == 1 || dataPage == 0)	// условие выхода индекса просмотра из среза в меньшую сторону для первой страницы
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
		//				вывод данных					//
		//////////////////////////////////////////////////

		// заполнение промежуточного потока для вывода таблицы
		dataBuffer << mTemps.itemStatLinePercent << failCount << mTemps.percent << "\n";
		dataBuffer << mTemps.itemStatLineHeader << "\n";
		dataBuffer << mTemps.tableSeparatorHorizontal << "\n" << mTemps.tableHeader << "\n" << mTemps.tableSeparatorHorizontal << "\n";
		for (uIndex = dataViewIndBeg; uIndex <= (dataViewIndBeg + dataViewIndCount - IND_CONV_FACTOR); ++uIndex, ++uData) { 
			dataBuffer << mTemps.space 
				<< mTemps.tableSeparatorVertical << setw(COUNTER_FIELD_WIDTH) << right << uIndex + 1 << mTemps.tableSeparatorVertical
				<< setw(FIRST_NAME_FIELD_WIDTH) << left << uData->firstName << mTemps.tableSeparatorVertical
				<< setw(LAST_NAME_FIELD_WIDTH) << uData->lastName << mTemps.tableSeparatorVertical
				<< setw(MATCH_SCORE_FIELD_WIDTH) << right << uData->mathScore << mTemps.tableSeparatorVertical
				<< setw(RU_SCORE_FIELD_WIDTH) << right << uData->ruLangScore << mTemps.tableSeparatorVertical
				<< setw(EN_SCORE_FIELD_WIDTH) << right << uData->enLangScore << mTemps.tableSeparatorVertical
				<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << uData->totalScore << mTemps.tableSeparatorVertical << "\n"
				<< mTemps.tableSeparatorHorizontal << "\n";
		}

		dataBuffer << mTemps.tablePage << setw(PAGE_FIELD_WIDTH) << right << dataPage << mTemps.tablePageSeparator <<
			left << dataPageCount << "\n";
		dataBuffer << mTemps.itemStatDescription << endl;

		// перевод данных из буфера в поток вывода 
		system("cls");
		cout << dataBuffer.str();
		dataBuffer.str("");
		dataBuffer.clear();

		//////////////////////////////////////////////////
		//			обработка клавиатуры				//
		//////////////////////////////////////////////////


		// обработка клавиш
		codeState = buttReadFnc(dataPage, vertPos);
		findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);
		exitFlag = codeState == KEY_ESCAPE ?  true: false; // выход из ф. просмотра
	}

}

// функция вычисления статискитеских данных
void ComputeStatistics(const u_short& pasScore, const u_short& minMathScore, const u_short& minRuLangScore,
		const u_short& minEnLangScore, const std::string dir, std::list<ExamResults>& usersData,
		readingBinaryFileFnc readBinFileFnc, printTableFnc printTableFnc, insertCursorPositionFnc insCurPosFnc,
		buttonsReadingFnc buttReadFnc, findingCursorPositionFnc2 findCurPosFnc2)
{

	using namespace std;


	u_int dataCount(0);		// кол-во данных
	bool exitFlag(false);	// флаг выхода из функции

	// чтение файла с данными
	if (usersData.empty()) {
		exitFlag = readBinFileFnc(dir, usersData, 0, 0, dataCount);			// чтение кол-ва данных
		exitFlag = readBinFileFnc(dir, usersData, 0, dataCount, dataCount);	// чтение данных
	}
	else {
		dataCount = usersData.size();	// присвоение кол-ва данных
	}
	if (exitFlag) {
		return;
	}

	vector<u_int> bestScoreListInd;	// массив с писком индексов имеющих максимальный балл
	u_short maxScore(0);			// максимальное значение баллов
	u_int failCount(0);				// кол-во не проходящих условия
	auto uData = usersData.begin();	// итератор по контейнеру

	for (unsigned int i = 0; i < dataCount; ++i, ++uData) {
		// проверка на прохождение по критериям
		if (uData->totalScore < pasScore || uData->mathScore < minMathScore
			|| uData->ruLangScore < minRuLangScore || uData->enLangScore < minEnLangScore) {
			++failCount;
			continue;
		}
		// проверка на макстимальный балл
		if (uData->totalScore == maxScore) {
			bestScoreListInd.push_back(i);
		}
		else if (uData->totalScore > maxScore) {
			maxScore = uData->totalScore;
			bestScoreListInd.clear();
			bestScoreListInd.push_back(i);
		}
	}

	// создание нового контейнера учетных запесей с лучшими баллами
	uData = usersData.begin();
	list<ExamResults> bestScoreList;
	for (u_int j = 0; j < bestScoreListInd.size(); ++j) {
		uData = usersData.begin();
		advance(uData, bestScoreListInd[j]);
		bestScoreList.push_back(*uData);
	}

	// вывод результатов 
	printTableFnc((float(failCount) / dataCount) * 100, dir, bestScoreList, allMenuTemplates,
		insCurPosFnc, buttReadFnc, findCurPosFnc2);
}

// функция создания нового файла в ручную
void PrintCreateItem(std::string& dir, insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc,
		findingCursorPositionFnc1 findCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc, userInputFnc userInputFnc)
{
	using namespace std;

	system("cls");

	// меню выбора
	if (selMenuPrintingFnc("записать в новый файл?", insCurPosFnc, buttReadFnc, findCurPosFnc) == true) {
		cout << "\n\t\t введите путь и имя новго файла: ";
		getline(cin, dir);
		cout << endl; ;
	}
	else {
		cout << "\t\t\t запись в текущий файл: " << dir << endl;
	}

	bool flagExit(false);
	u_int counter(1);				// абсолютный счётчик
	ExamResults			userData;	// промежуточная структура для записи
	ExamResultsBinary	bufData;	// структура для записи в бинарный файл

	//	открытие файла
	ofstream outBinFile(dir, ios::trunc | ios::binary);
	// чтение данных
	cout << "Введите данные по порядку" << endl;
	while (!flagExit)
	{
		cout << "№ " << counter << " : ";
		UserInput(userData);

		// копирование данных в структуру для записи
		strcpy_s(bufData.firstName, LENGTH_FIRST_NAME, userData.firstName.c_str());
		strcpy_s(bufData.lastName, LENGTH_LAST_NAME, userData.lastName.c_str());
		bufData.mathScore = userData.mathScore;
		bufData.ruLangScore = userData.ruLangScore;
		bufData.enLangScore = userData.enLangScore;

		// запись структуры
		outBinFile.write(bufData.firstName, sizeof(*bufData.lastName) * LENGTH_FIRST_NAME);
		outBinFile.write(bufData.lastName, sizeof(*bufData.firstName) * LENGTH_LAST_NAME);
		outBinFile.write((char*)&bufData.mathScore, sizeof(bufData.mathScore));
		outBinFile.write((char*)&bufData.ruLangScore, sizeof(bufData.ruLangScore));
		outBinFile.write((char*)&bufData.enLangScore, sizeof(bufData.enLangScore));

		++counter;	// абсолютный счётчик

		// проверка на выхода из цикла
		cout << "---------------------------------------нажмите ESC для выхода---------------------------------" << endl;
		u_int horPos(HORIZONTAL_BEGIN_POINT);
		u_int vertPos(VERTICAL_BEGIN_POINT);
		if (buttReadFnc(horPos, vertPos) == KEY_ESCAPE) {
			outBinFile.close();
			flagExit = true;
		}
	}

}
