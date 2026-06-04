#include <iostream>
#include <windows.h>
#include <array>

using namespace std;

class Key {
public:
  Key(int aKeys[3]) {
    for (int i = 0; i < sizeof(aKeys); i++) {
      keys[i] = aKeys[i];
    }

    keys[0] = aKeys[0];
  }
private:
  int keys[];
};

class KeyboardInput {
public:
  //int const jumpKeys[3] = { 32, 38, 87 };
  int test[3] = { 32, 38, 87 };
  //Key jumpKeys(test);
  //int const quitKey = 
  // 27, 81
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