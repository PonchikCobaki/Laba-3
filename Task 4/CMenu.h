#pragma once
#include "Config.h"
#include "BinFO.h"
#include "Keyboard.h"



enum MenuItems
{
	ITEM_VIEW = 1,
	ITEM_SEARCH,
	ITEM_STATISTICS,
	ITEM_CRATE,
	ITEM_EXIT,
};

enum SelectionMenuItems
{
	ITEM_SELECTION_YES = 1,
	ITEM_SELECTION_NO,
};

enum MenuSizes {
	HEIGHT_ITEM_MAIN = 5,
	LENGTH_ITEM_DEFAULT = 1,
	HEIGHT_ITEM_VIEW = 15,
	HEIGHT_ITEM_SELECTION = 2,
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
	LEVEL_SELECTION
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


#ifndef MENU_TEMP
#define MENU_TEMP

#pragma pack(1)
struct MenuTemplates
{
	std::string cursor;
	std::string space;

	std::string itemMainDescription;
	std::string lineView;
	std::string lineSearch;
	std::string lineStatistics;
	std::string lineCreate;
	std::string lineExit;

	std::string itemViewDescription;
	std::string tableHeader;
	std::string tableSeparatorHorizontal;
	std::string tableSeparatorVertical;
	std::string tablePage;
	std::string tablePageSeparator;

	std::string selLineYes;
	std::string selLineNo;
};
#pragma pack (pop)



extern MenuTemplates allMenuTemplates;

#endif


using findingCursorPositionFnc1 = void(*)(u_int& vertPosOut, const u_int& heigh);
using findingCursorPositionFnc2 = void(*)(u_int& horPosOut, u_int& vertPosOut, const u_int& length, const u_int& height);
using insertCursorPositionFnc =	  std::string(*)(std::string str, const u_int& vertPos, const MenuTemplates& mTemps,
									u_short level, const u_int& iterator);
using selectionMenuPrintingFnc =  bool(*)(std::string title, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc,
									buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc);


void		FindingCursorPosition(u_int& vertPosOut, const u_int& heigh);
void		FindingCursorPosition(u_int& horPosOut, u_int& vertPosOut, const u_int& length, const u_int& height);
std::string InsertCursorPosition(std::string str, const u_int& vertPos, const MenuTemplates& mTemps,
				u_short level, const u_int& iterator);
bool		SelectionMenuPrinting(std::string title, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc,
				buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc);
void		PrintMainMenu(const u_int& vertPos, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc);
void		PrintViewItem(std::string dir, std::list<ExamResults>& usersData, const MenuTemplates& mTemps,
				insertCursorPositionFnc insCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc,
				buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc1, findingCursorPositionFnc2 findCurPosFnc2,
				readingBinaryFileFnc readBinFileFnc, writeInBinaryFileFnc writeInBinFileFnc,
				deletingFromBinaryFileFnc delFromBinFileFnc, changeDataInBinaryFileFnc changeInBinFileFnc,
				appendInBinaryFileFnc appInBinFileFnc, userInputFnc userInputFnc);
void		PrintCreateItem(std::string& dir, const MenuTemplates& mTemps, insertCursorPositionFnc insCurPosFnc,
				buttonsReadingFnc buttReadFnc, findingCursorPositionFnc1 findCurPosFnc, selectionMenuPrintingFnc selMenuPrintingFnc,
				userInputFnc userInputFnc);