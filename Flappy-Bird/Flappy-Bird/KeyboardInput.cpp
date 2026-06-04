#include <iostream>
#include "KeyboardInput.h"
#include "Key.h"

bool KeyboardInput::getconchar(KEY_EVENT_RECORD& krec) {
  DWORD cc;
  INPUT_RECORD irec;
  HANDLE h = GetStdHandle(STD_INPUT_HANDLE);

  if (h == NULL)
  {
    return false; // console not found
  }

  for (; ; )
  {
    ReadConsoleInput(h, &irec, 1, &cc);
    if (irec.EventType == KEY_EVENT
      && ((KEY_EVENT_RECORD&)irec.Event).bKeyDown)
    {
      krec = (KEY_EVENT_RECORD&)irec.Event;
      return true;
    }
  }
  return false;
}

void KeyboardInput::outputPressedKey(KEY_EVENT_RECORD krec) const {
  std::cout << "key: " << krec.uChar.AsciiChar
    << " | code: " << krec.wVirtualKeyCode << std::endl;
}