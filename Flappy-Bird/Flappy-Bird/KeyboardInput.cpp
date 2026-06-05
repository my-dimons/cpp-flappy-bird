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
      cout << "char";
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

bool KeyboardInput::keyPressed(Key key, KEY_EVENT_RECORD krec) const {
  bool keyPressed = false;
  int pressedKey = krec.wVirtualKeyCode;

  for (int key : key.getKeys()) {
    if (key == pressedKey)
      keyPressed = true;
  }

  return keyPressed;
}