#include <iostream>
#include <windows.h>
#include <vector>
#include "Key.h"

using namespace std;

class KeyboardInput;



class KeyboardInput {
public:
  //vector<string> words = { "Test" };
  //const vector<int> arr = { 32, 38, 87 };
  Key jumpKeys;
  KeyboardInput() : jumpKeys( { 32, 38, 87 } ) {}

  /// <summary>
  /// Sets krec to the keyboards pressed key
  /// </summary>
  /// <param name="krec"></param>
  /// <returns></returns>
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

  /// <summary>
  /// Outputs the pressed key to the console
  /// </summary>
  /// <param name="krec"></param>
  void outputPressedKey(KEY_EVENT_RECORD krec) {
    cout << "key: " << krec.uChar.AsciiChar
      << " | code: " << krec.wVirtualKeyCode << endl;
  }
};

int main()
{
  int arr[] = { 3 };
  KeyboardInput keyboardInput;
  KEY_EVENT_RECORD key;
  for (; ; )
  {
    keyboardInput.getconchar(key);
    keyboardInput.outputPressedKey(key);
  }
}