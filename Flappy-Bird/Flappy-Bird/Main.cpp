#include "Main.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

	int code;

	do {
		code = MessageBoxA(0, "uh oh, ran into an error", "VIRUS.exe", MB_CANCELTRYCONTINUE);

		switch (code) {
		case IDTRYAGAIN:
			cout << "retrying!";
			break;
		case IDCANCEL:
			cout << "YOU CANNOT CANCELL!!!";
			break;
		case IDCONTINUE:
			cout << "ok :3";
			break;
		}

		cout << endl;
	} while (code != IDCONTINUE);

	cin.get();
	return 0;
}