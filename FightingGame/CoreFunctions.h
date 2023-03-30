#ifndef __CORE_FUNCTIONS_H_INCLUDED__
#define __CORE_FUNCTIONS_H_INCLUDED__

#define TEXT_BLACK 0
#define TEXT_D_BLUE 1
#define TEXT_D_GREEN 2
#define TEXT_D_CYAN 3
#define TEXT_D_RED 4
#define TEXT_D_MAGENTA 5
#define TEXT_D_YELLOW 6
#define TEXT_GRAY 7
#define TEXT_L_GRAY 8
#define TEXT_L_BLUE 9
#define TEXT_L_GREEN 10
#define TEXT_L_CYAN 11
#define TEXT_L_RED 12
#define TEXT_L_MAGENTA 13
#define TEXT_YELLOW 14
#define TEXT_WHITE 15

#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

using namespace std;

namespace cf
{
	void getEnter();
	void setTextColor(int color = TEXT_WHITE);
	void showMassage(string text = "%TEXT%", int color = TEXT_WHITE);
	void showError(string text = "%ERROR%");
	int getInputInt();
}

#endif // !__CORE_FUNCTIONS_H_INCLUDED__