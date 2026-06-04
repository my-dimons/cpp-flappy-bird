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
  KEY_EVENT_RECORD key;
  for (; ; )
  {
    keyboardInput.getconchar(key);
    keyboardInput.outputPressedKey(key);
  }
}