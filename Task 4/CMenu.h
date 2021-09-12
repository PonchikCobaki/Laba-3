#pragma once
#include "Config.h"
#include "BinFO.h"
#include "Keyboard.h"



enum MainMenuItems	// перечесление пунтков основного меню
{
	ITEM_VIEW = 1,
	ITEM_STATISTICS,
	ITEM_CREATE,
	ITEM_EXIT,
};


enum MenuSizes	//	перечесление размеров меню
{
	HEIGHT_ITEM_MAIN = 4,
	LENGTH_ITEM_DEFAULT = 1,
	HEIGHT_ITEM_VIEW = 15,
	HEIGHT_ITEM_SELECTION = 2,
};

enum MenuLevels	//	перечесление уровней меню
{
	LEVEL_MAIN,
	LEVEL_VIEW,
	LEVEL_SELECTION
};

enum PositionBeginPoint	//	перечесление нижних положения указателей в меню
{
	HORIZONTAL_BEGIN_POINT = 1,
	VERTICAL_BEGIN_POINT = 1,
};

enum SelectionMenuItems	//	перечесление порядковых номеров меню выбора
{
	ITEM_SELECTION_YES = 1,
	ITEM_SELECTION_NO,
};

enum WidthOfTableFields	//	перечесление размеров таблицы
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

// структура шаблонов меню
#ifndef MENU_TEMP
#define MENU_TEMP

#pragma pack(1)
struct MenuTemplates
{
	std::string cursor;
	std::string space;
	std::string percent;

	std::string itemMainDescription;
	std::string lineView;
	std::string lineStatistics;
	std::string lineCreate;
	std::string lineExit;

	std::string itemViewDescription;
	std::string tableHeader;
	std::string tableSeparatorHorizontal;
	std::string tableSeparatorVertical;
	std::string tablePage;
	std::string tablePageSeparator;

	std::string itemStatDescription;
	std::string itemStatLineHeader;
	std::string itemStatLinePercent;

	std::string selLineYes;
	std::string selLineNo;
};
#pragma pack (pop)

extern MenuTemplates allMenuTemplates;

#endif

// указатели на соответствующие функции
using findingCursorPositionFnc1 = void(*)(u_int& vertPosOut, const u_int& heigh);
using findingCursorPositionFnc2 = void(*)(u_int& horPosOut, u_int& vertPosOut, const u_int& length, const u_int& height);
using insertCursorPositionFnc	= std::string(*)(std::string str, const u_int& vertPos, const MenuTemplates& mTemps,
									u_short level, const u_int& iterator);
using selectionMenuPrintingFnc	= bool(*)(std::string title, insertCursorPositionFnc insCurPosFnc,
									buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc);

using printTableFnc	= void(*)(const u_int& failCount, std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
						insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc2 findCurPosFnc2);

//	функция предотвращающая выход переменной верктикального указателя за пределы [V_B_P,height]
void		FindingCursorPosition(u_int& vertPosOut, const u_int& heigh);

//	функция предотвращающая выход переменной верктикального и горизонтального указателя за пределы [V_B_P, height], [H_B_P, length]
void		FindingCursorPosition(u_int& horPosOut, u_int& vertPosOut, const u_int& length, const u_int& height);

//	заменяет пробел на указатель
std::string InsertCursorPosition(std::string str, const u_int& vertPos, const MenuTemplates& mTemps,
				u_short level, const u_int& iterator);

//	меню выбора да/нет
bool		SelectionMenuPrinting(std::string title, insertCursorPositionFnc insCurPosFnc,
				buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc);

//	основное меню
void		PrintMainMenu(const u_int& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc);

// построение таблицы с функциями редактирования
void		PrintTable(const u_int& failCount, std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
				insertCursorPositionFnc insCurPosFnc, buttonsReadingFnc buttReadFnc, findingCursorPositionFnc2 findCurPosFnc2);
// упрощённая версия для построение таблицы 
void		PrintTable(std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
				insertCursorPositionFnc insCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc,
				buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc1, findingCursorPositionFnc2 findCurPosFnc2,
				readingBinaryFileFnc readBinFileFnc, writeInBinaryFileFnc writeInBinFileFnc,
				deletingFromBinaryFileFnc delFromBinFileFnc, changeDataInBinaryFileFnc changeInBinFileFnc,
				appendInBinaryFileFnc appInBinFileFnc, userInputFnc userInputFnc);

// функция вычисления статискитеских данных
void		ComputeStatistics(const u_short& pasScore, const u_short& minMathScore, const u_short& minRuLangScore,
				const u_short& minEnLangScore, const std::string dir, std::list<ExamResults>& usersData,
				readingBinaryFileFnc readBinFileFnc, printTableFnc printTableFnc, insertCursorPositionFnc insCurPosFnc,
				buttonsReadingFnc buttReadFnc, findingCursorPositionFnc2 findCurPosFnc2);

// функция создания нового файла в ручную
void		PrintCreateItem(std::string& dir, insertCursorPositionFnc insCurPosFnc,	buttonsReadingFnc buttReadFnc,
				findingCursorPositionFnc1 findCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc, userInputFnc userInputFnc);