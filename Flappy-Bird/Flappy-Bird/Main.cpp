#include <iostream>
#include <windows.h>

using namespace std;

class KeyboardInput {
public:
  bool getconchar(KEY_EVENT_RECORD& krec)
  {
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
};


int main()
{
  KeyboardInput keyboardInput;
  KEY_EVENT_RECORD key;
  for (; ; )
  {
    keyboardInput.getconchar(key);
    std::cout << "key: " << key.uChar.AsciiChar
      << " code:  " << key.wVirtualKeyCode << std::endl;
  }
}