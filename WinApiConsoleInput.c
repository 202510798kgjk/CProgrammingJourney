#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	HANDLE hConsoleInput;
	wchar_t* lpBuffer;
	DWORD nNumberOfCharsToRead;
	LPDWORD lpNumberOfCharsRead;
} ConsoleInputStruct;

int main() {
	DWORD bytes; HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_READCONSOLE_CONTROL consoleReadConsoleControl = {
		.nLength = sizeof(CONSOLE_READCONSOLE_CONTROL),
		.nInitialChars = 0,
		.dwControlKeyState = 0,
		.dwCtrlWakeupMask = 1 << '\n'
	};
	DWORD charsRead=0;
	ConsoleInputStruct consoleInputStruct = {
		.lpNumberOfCharsRead = &charsRead,
		.nNumberOfCharsToRead = MAX_PATH,
		.lpBuffer = calloc(MAX_PATH, sizeof(wchar_t)),
		.hConsoleInput = GetStdHandle(STD_INPUT_HANDLE)
	};
	if (!SetConsoleMode(consoleInputStruct.hConsoleInput, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT)) {
		char* errMessage = "Cannot Resolve SetConsoleMode Function. Exiting...";
		WriteFile(hStdOut, errMessage, strlen(errMessage), &bytes, 0);
		free(consoleInputStruct.lpBuffer);
		ExitProcess(1);
	};

	if (!ReadConsoleW(
		consoleInputStruct.hConsoleInput,
		consoleInputStruct.lpBuffer,
		consoleInputStruct.nNumberOfCharsToRead,
		consoleInputStruct.lpNumberOfCharsRead,
		&consoleReadConsoleControl)) {
		char* errMessage = "Cannot Resolve ReadConsole Function. Exiting with error code ";
		
		char errCodeTemp[4]; char* errCode;
		DWORD dwOperand = GetLastError();
		errCode=_ultoa(dwOperand, errCodeTemp, 10);
		
		WriteFile(hStdOut, errMessage, strlen(errMessage), &bytes, 0);
		WriteFile(hStdOut, errCode, strlen(errCode), &bytes, 0);

		free(consoleInputStruct.lpBuffer);

		ExitProcess(1);
	}
	COORD coord;
	coord.X = 0; coord.Y = 1;
	SetConsoleCursorPosition(hStdOut,coord);
	WriteConsoleW(
		hStdOut,
		consoleInputStruct.lpBuffer,
		consoleInputStruct.nNumberOfCharsToRead,
		consoleInputStruct.lpNumberOfCharsRead,
		NULL);
	coord.X = 0; coord.Y = 2;
	SetConsoleCursorPosition(hStdOut, coord);
	free(consoleInputStruct.lpBuffer);
	ExitProcess(0);
}
