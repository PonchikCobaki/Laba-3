#pragma once

#include "Config.h"


u_short ButtonsReading(u_int& horPosOut, u_int& vertPosOut);
void	UserInput(ExamResults& userData);

using buttonsReadingFnc = u_short(*)(u_int& horPosOut, u_int& vertPosOut);
using userInputFnc = void(*)(ExamResults& userData);



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

enum DefalutPositionStepers
{
	HORIZONTAL_STEP = 1,
	VERTICAL_STEP = 1,
};