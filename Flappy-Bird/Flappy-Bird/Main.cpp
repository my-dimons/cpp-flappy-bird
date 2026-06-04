#include <iostream>
#include <windows.h>
#include <vector>
#include "Key.h"
#include "KeyboardInput.h"

using namespace std;

class KeyboardInput;
int main()
{
  KeyboardInput keyboardInput;
  KEY_EVENT_RECORD krec;
  for (; ; )
  {
    keyboardInput.getconchar(krec);
    //keyboardInput.outputPressedKey(krec);
    if (keyboardInput.keyPressed(keyboardInput.getJumpKeys(), krec)) {
      cout << "JUMPING" << endl;
    }
  }
}