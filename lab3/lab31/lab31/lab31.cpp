#include <iostream>
#include <windows.h> 
#include <ctime>
#pragma warning(disable:4996)

int main()
{
	char text[] = "Process Running Now";
	wchar_t wtext[20];
	mbstowcs(wtext, text, strlen(text) + 1);
	LPWSTR ptr = wtext;
	SetConsoleTitle(ptr);
	int Run = 0;
	int start = clock();
	std::cout << "Address: " << &Run << '\n';
	while (Run <= 1000)
	{
		if (clock() - start > 1000)
		{
			start = clock();
			std::cout << "memory " << Run << '\n';
			Run++;
		}
	}
	return 0;
}
