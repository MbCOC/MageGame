#include "CoreFunctions.h"

namespace cf
{
	void getEnter()
	{
		cin.get();
		cin.get();
		system("cls");
	}
	void setTextColor(int color)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console, color);
	}
	void showMassage(string text, int color)
	{
		cf::setTextColor(color);
		cout << text;
		cf::setTextColor();
	}
	void showError(string text)
	{
		std::transform(text.begin(), text.end(), text.begin(), ::toupper);
		cf::setTextColor(TEXT_D_RED);
		cout << "ERROR: " << text;
		cf::setTextColor();
	}
	int getInputInt()
	{
		try
		{
			string input;
			cin >> input;
			return stoi(input);
		}
		catch (const std::exception& e)
		{
			cf::showError(e.what());
		}
	}
}