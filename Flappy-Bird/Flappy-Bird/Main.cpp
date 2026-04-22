#include "Main.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

	int code = MessageBoxA(0, "context", "title", MB_OKCANCEL);

	if (code == IDOK) {
		cout << "ok";
	}
	else if (code == IDCANCEL) {
		cout << "cancel";
	}

	cin.get();
	return 0;
}