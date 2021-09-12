#pragma once

#include "Config.h"



// указатели на соответствующие функции
u_short ButtonsReading(u_int& horPosOut, u_int& vertPosOut);
void	UserInput(ExamResults& userData);

// функция чтения клавиш клавиатуры
using buttonsReadingFnc = u_short(*)(u_int& horPosOut, u_int& vertPosOut);
// функция ввода с клавиатуры
using userInputFnc = void(*)(ExamResults& userData);



enum AsciiCode	// перечисление значения клавиш клавиатуры
{
	CODE_ENTER = 13,
	CODE_DELETE = 83,
	CODE_UP = 72,
	CODE_DOWN = 80,
	CODE_LEFT = 75,
	CODE_RIGHT = 77,
	CODE_ESCAPE = 27,
};

enum ButtonsCode	// перечисление сценариев работы клавиатуры
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

enum DefalutPositionStepers	//	перечисление шага инкремента/декремента указателя
{
	HORIZONTAL_STEP = 1,
	VERTICAL_STEP = 1,
};