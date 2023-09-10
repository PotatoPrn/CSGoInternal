#include "Utils/UiUtils.h"


bool UI::ClearConsole()
{
	COORD CursorPosition;
	CursorPosition.X = 0;
	CursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
	return true;
}

bool UI::SetupConsole()
{
	// Wipe Screen Fully
	std::cout.clear();
	std::cin.clear();

	// Begin Console Setup
	HWND CurrentConsole = GetConsoleWindow();
	HANDLE StdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	RECT ConsoleRect;
	CONSOLE_CURSOR_INFO CursorInfo;
	CONSOLE_FONT_INFOEX ConsoleFontInfo;

	// Setup Console Size
	GetWindowRect(CurrentConsole, &ConsoleRect);
	MoveWindow(CurrentConsole, ConsoleRect.left, ConsoleRect.top, 800, 600, TRUE);

	// Modify Font
	ConsoleFontInfo.cbSize = sizeof(ConsoleFontInfo);
	ConsoleFontInfo.dwFontSize.X = 0;
	ConsoleFontInfo.dwFontSize.Y = 24;
	ConsoleFontInfo.FontWeight = FW_BOLD;
	SetCurrentConsoleFontEx(StdHandle, FALSE, &ConsoleFontInfo);

	// Hide Cursor
	GetConsoleCursorInfo(StdHandle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(StdHandle, &CursorInfo);
	return true;
}