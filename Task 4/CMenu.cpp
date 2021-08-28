#include "CMenu.h"

MenuTemplates allMenuTemplates = {
	">",
	" ",

	"��������� �� ����:  arrow up/down - ����������� �����/����, Enter - ����� ������",
	"  �������� �����",
	"  ����� �� �����",
	"  ����� ����������",
	"  �������� ������ �����",
	"  �����",

	"���������: arrow Up/Down - ����������� �����/����, arrow Right/Left - ����������� ������/���-\n"
	"��, Esc - ������� � ����, Enter - ����� �������� ��� �������������� ������� ����� ������� ���\n"
	"����� ������ ��������, Delite - �������� ��������",
	" |   �#   |           ���           |         �������         | ����� | ���� | ���� | ����� |",
	" +--------+-------------------------+-------------------------+-------+------+------+-------+",
	"|",
	"                                   �������� ",
	"/",

	"  ��",
	"  ���",
};

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

		case ITEM_SEARCH:
			if (mTemps.lineSearch == str) {
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

	else if (level == LEVEL_SEARCH) {

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

bool SelectionMenuPrinting(std::string title, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc,
	buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc)
{
	using namespace std;

	u_short codeState;
	u_int	horPos(HORIZONTAL_BEGIN_POINT);
	u_int	vertPos(VERTICAL_BEGIN_POINT);

	while (true) {
		system("cls");
		cout << title << "\n";
		cout << insCurPosFnc(mTemps.selLineYes, vertPos, mTemps, LEVEL_SELECTION, 0) << "\n";
		cout << insCurPosFnc(mTemps.selLineNo, vertPos, mTemps, LEVEL_SELECTION, 0) << endl;

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

//void PrintTable() 
//{
//	// ���������� �������������� ������ ��� ������ �������
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
//	// ������� ������ �� ������ � ����� ������ 
//	system("cls");
//	cout << dataBuffer.str();
//	dataBuffer.str("");
//	dataBuffer.clear();
//}

void PrintMainMenu(const u_int& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc)
{
	using namespace std;

	system("cls");

	cout << insCurPosFnc(mTemps.lineView, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineSearch, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineStatistics, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineCreate, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
	cout << insCurPosFnc(mTemps.lineExit, vertPos, mTemps, LEVEL_MAIN, 0) << endl;
}

void PrintViewItem(std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
	insertCursorPositionFnc insCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc,
	buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc1, findingCursorPositionFnc2 findCurPosFnc2,
	readingBinaryFileFnc readBinFileFnc, writeInBinaryFileFnc writeInBinFileFnc,
	deletingFromBinaryFileFnc delFromBinFileFnc, changeDataInBinaryFileFnc changeInBinFileFnc,
	appendInBinaryFileFnc appInBinFileFnc, userInputFnc userInputFnc)
{
	using namespace std;

	u_int	dataCount(0);

	// ������ ������� �������
	readBinFileFnc(dir, usersData, 0, 0, dataCount);	// ������ ���-�� ������

	bool exitFlag = false;
	if (dataCount == 0) {
		cerr << "\n\t ���� ������ ��� ��� �� ����������!" << endl;
		system("pause");
		exitFlag = true;
	}

	u_short codeState;							// ��� �������
	u_int	vertPos(VERTICAL_BEGIN_POINT);			// ��������� ���������

	u_int	dataPage(1);							// ������� ��������
	u_int   prevDataPage(0);						// ���������� ��������
	u_int   dataPageCount(2);						// ����� �������

	u_int	dataViewIndBeg(0);						// ��������� ������ ���������
	u_int	dataViewIndCount(DATA_FIELD_LENGTH);	// ����� ��. ���������

	auto	uData = usersData.begin();				// ��. �� �����
	u_int	uIndex;									// ��������� ��� ��������� ������
	u_int	sliceIndBeg(0);							// ��������� ������ �����
	u_int	sliceIndCount(0);						// ����� ��������� �����
	u_int	sliceCur(0);							// ������� ����
	u_int	sliceCounts(0);							// ����� ������

	bool changeFlag = false;						// ���� ��������� ��.
	stringstream dataBuffer;						// ����� ��� ������

	// ������ ���-�� ��������� ������
	if ((dataViewIndBeg + dataViewIndCount) > dataCount) {
		dataViewIndCount = dataCount - dataViewIndBeg; // ��������� ������� ���-�� ��������� ������
	}

	// ������ ���-�� �������� ������ � ����	//
	if ((sliceIndBeg + sliceIndCount) > dataCount) {
		sliceIndCount = dataCount - sliceIndBeg; // ��������� ������� ���-�� ��������� �����
	}

	while (!exitFlag)
	{
		//////////////////////////////////////////////
		// ������ � ����� ���� ����������� ��������	//
		//////////////////////////////////////////////

		if (dataCount == 0) {
			exitFlag = true;
			break;
		}

		if (prevDataPage != dataPage || changeFlag) {
			// ��������� �������� ����� ������
			dataViewIndCount = DATA_FIELD_LENGTH;
			dataViewIndBeg = (dataPage - IND_CONV_FACTOR) * dataViewIndCount;

			// �������� ����� ����� ������
			if ((dataViewIndBeg + dataViewIndCount) > dataCount) {
				dataViewIndCount = dataCount - dataViewIndBeg;
			}

			findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);

			prevDataPage = dataPage;
		}

		// ������ ������ ����� ������	//
		if ((sliceIndBeg + sliceIndCount) < (((dataPage - 1) * DATA_FIELD_LENGTH) + dataViewIndCount) ||
			sliceIndBeg > ((dataPage - 1) * DATA_FIELD_LENGTH) || changeFlag)	// �������� ������ ��������� ������ �� ���������
		{

			// ������ ���-�� ���������
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


			// ������ ���������� ������� ������ �������� ��� ����� sliceIndBeg
			// ������ �������� ����� sliceCur
			sliceIndCount = SUBFILE_SIZE;
			if (sliceIndBeg > ((dataPage - 1) * DATA_FIELD_LENGTH) &&
				dataPage != 1 && dataPage != dataPageCount) // ������� ������ ������� ��������� �� ����� � ������� �������
			{
				--sliceCur;
				sliceIndBeg = sliceCur * SUBFILE_SIZE;
			}
			else if ((sliceIndBeg + sliceIndCount) < (((dataPage - 1) * DATA_FIELD_LENGTH) + dataViewIndCount) &&
				dataPage != 1 && dataPage != dataPageCount)	// ������� ������ ������� ��������� �� ����� � ������� �������
			{
				++sliceCur;
				sliceIndBeg = sliceCur * SUBFILE_SIZE;
			}
			else if ((sliceIndBeg + sliceIndCount) < (((dataPage - 1) * DATA_FIELD_LENGTH) + dataViewIndCount)
				&& dataPage == dataPageCount)	// ������� ������ ������� ��������� �� ����� � ������� ������� ��� ��������� ��������
			{
				sliceCur = sliceCounts - IND_CONV_FACTOR;
				sliceIndBeg = sliceCur * SUBFILE_SIZE;
			}
			else if (dataPage == 1 || dataPage == 0)	// ������� ������ ������� ��������� �� ����� � ������� ������� ��� ������ ��������
			{
				sliceCur = 0;
				sliceIndBeg = 0;
			}


			// ���������� ���-�� �������� ������ � ����
			if ((sliceIndBeg + sliceIndCount) > dataCount) {
				sliceIndCount = dataCount - sliceIndBeg; // ��������� ������� ���-�� ��������� �����
			}
			else if (sliceIndCount == 0) {
				sliceIndCount = SUBFILE_SIZE;
				--sliceCur;
			}

			// ������ ����� ������
			readBinFileFnc(dir, usersData, sliceIndBeg, sliceIndCount, dataCount);

			if (dataCount == 0) {
				cerr << "\t���� ������ ��� ��� �� ����������!" << endl;
				system("pause");
				exitFlag = true;
				break;
			}

			// ���������� ���������� �������
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

		// ��������� ������� ��������� ���������� � ������ ������
		uData = usersData.begin();
		if (sliceCur != sliceCounts - IND_CONV_FACTOR) {
			advance(uData, dataViewIndBeg % sliceIndCount);
		}
		else {
			advance(uData, (dataViewIndBeg - sliceIndBeg));
		}

		//////////////////////////////////////////////////
		//	����� � ��������� ���������������� ������	//
		//////////////////////////////////////////////////

		// ���������� �������������� ������ ��� ������ �������
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

		// ������� ������ �� ������ � ����� ������ 
		system("cls");
		cout << dataBuffer.str();
		dataBuffer.str("");
		dataBuffer.clear();

		// ��������� ������
		codeState = buttReadFnc(dataPage, vertPos);
		findCurPosFnc2(dataPage, vertPos, dataPageCount, dataViewIndCount);

		// ���������� ��� ��������� ������
		long int changeInd(0);
		bool offset;
		ExamResults changeUser;


		switch (codeState)
		{
		case KEY_DELETE: // �������� ��. �� ����

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

		case KEY_ENTER: // ��������� �� � ����
			system("cls");

			changeInd = dataViewIndCount - vertPos + IND_CONV_FACTOR;
			advance(uData, (-1) * changeInd);
			cout << "\t\t\t\t ������������� ������� ������ \n"
				<< mTemps.tableSeparatorHorizontal << " " << mTemps.cursor << mTemps.tableSeparatorVertical
				<< setw(COUNTER_FIELD_WIDTH) << right << dataViewIndBeg + vertPos << mTemps.tableSeparatorVertical
				<< setw(FIRST_NAME_FIELD_WIDTH) << left << uData->firstName << mTemps.tableSeparatorVertical
				<< setw(LAST_NAME_FIELD_WIDTH) << uData->lastName << mTemps.tableSeparatorVertical
				<< setw(MATCH_SCORE_FIELD_WIDTH) << right << uData->mathScore << mTemps.tableSeparatorVertical
				<< setw(RU_SCORE_FIELD_WIDTH) << right << uData->ruLangScore << mTemps.tableSeparatorVertical
				<< setw(EN_SCORE_FIELD_WIDTH) << right << uData->enLangScore << mTemps.tableSeparatorVertical
				<< setw(TOTAL_SCORE_FIELD_WIDTH) << right << uData->totalScore << mTemps.tableSeparatorVertical << "\n"
				<< mTemps.tableSeparatorHorizontal << endl;

			cout << "\n\t\t ������� ����� ������: ";

			userInputFnc(changeUser);
			changeInBinFileFnc(dir, ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR,
				dataCount, changeUser, writeInBinFileFnc);

			changeFlag = true;
			break;

		case KEY_OTHER: // ���������� ������

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

			offset = !selMenuPrintingFnc(dataBuffer.str() + "���������� �� ����� ���������� ������� ������? ����� �� ����� ����",
				mTemps, insCurPosFnc, buttReadFnc, findCurPosFnc1); // ����� ����� ������

			// ������� �������
			dataBuffer.str("");
			dataBuffer.clear();

			cout << "\n\t\t ������� ����� ������: ";

			userInputFnc(changeUser);
			appInBinFileFnc(dir, ((dataPage - 1) * DATA_FIELD_LENGTH) + vertPos - IND_CONV_FACTOR, offset,
				dataCount, changeUser, writeInBinFileFnc);
			++dataCount;
			changeFlag = true;
			break;

		case KEY_ESCAPE: // ����� �� �. ���������
			exitFlag = true;
			break;
		}
	}

}

void PrintCreateItem(std::string& dir, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc,
	buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc,
	userInputFnc userInputFnc)
{
	using namespace std;

	system("cls");

	if (selMenuPrintingFnc("�������� � ����� �����?", mTemps, insCurPosFnc, buttReadFnc, findCurPosFnc) == true) {
		cout << "\n\t\t ������� ���� � ��� ����� �����: ";
		getline(cin, dir);
		cout << endl; ;
	}
	else {
		cout << "\t\t\t ������ � ������� ����: " << dir << endl;
	}

	bool flagExit = false;
	u_int counter(1);
	ExamResults			userData;
	ExamResultsBinary	bufData;

	ofstream outBinFile(dir, ios::trunc | ios::binary);
	cout << "������� ������ �� �������" << endl;
	while (!flagExit)
	{
		cout << "� " << counter << " : ";
		UserInput(userData);

		// ����������� ������ � ��������� ��� ������
		strcpy_s(bufData.firstName, LENGTH_FIRST_NAME, userData.firstName.c_str());
		strcpy_s(bufData.lastName, LENGTH_LAST_NAME, userData.lastName.c_str());
		bufData.mathScore = userData.mathScore;
		bufData.ruLangScore = userData.ruLangScore;
		bufData.enLangScore = userData.enLangScore;

		// ������ ���������
		outBinFile.write(bufData.firstName, sizeof(*bufData.lastName) * LENGTH_FIRST_NAME);
		outBinFile.write(bufData.lastName, sizeof(*bufData.firstName) * LENGTH_LAST_NAME);
		outBinFile.write((char*)&bufData.mathScore, sizeof(bufData.mathScore));
		outBinFile.write((char*)&bufData.ruLangScore, sizeof(bufData.ruLangScore));
		outBinFile.write((char*)&bufData.enLangScore, sizeof(bufData.enLangScore));

		++counter;

		// �������� ������ �� �����
		cout << "---------------------------------------������� ESC ��� ������---------------------------------" << endl;
		u_int horPos(HORIZONTAL_BEGIN_POINT);
		u_int vertPos(VERTICAL_BEGIN_POINT);
		if (buttReadFnc(horPos, vertPos) == KEY_ESCAPE) {
			outBinFile.close();
			flagExit = true;
		}
	}

}