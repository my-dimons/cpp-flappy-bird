#include <SDL3/SDL.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	SDL_Init(SDL_INIT_VIDEO);

	while (true) {
		cout << "WORKING" << endl;
	}

	return 0;
}