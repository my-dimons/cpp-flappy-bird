#include <iostream>
#include <windows.h>
#include <vector>
#include "Key.h"
#include "KeyboardInput.h"

using namespace std;

int main()
{
  KeyboardInput keyboardInput;
  KEY_EVENT_RECORD krec;

  do {
    keyboardInput.getconchar(krec);
    //keyboardInput.outputPressedKey(krec);
    if (keyboardInput.keyPressed(keyboardInput.getJumpKeys(), krec)) {
      cout << "JUMPING" << endl;
    }
  } while (!keyboardInput.keyPressed(keyboardInput.getQuitKeys(), krec));

  cout << "Quitting Game";
  return 0;
}