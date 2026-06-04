#pragma once

#include <windows.h>
#include "Key.h"
#include <vector>

using namespace std;

class KeyboardInput {
public:
	KeyboardInput() : jumpKeys(jumpKeyCodes), quitKeys(quitKeyCodes) {};
	/// <summary>
	/// Sets krec to the keyboards pressed key
	/// </summary>
	bool getconchar(KEY_EVENT_RECORD& krec);
	/// <summary>
	/// Outputs the pressed key to the console
	/// </summary>
	void outputPressedKey(KEY_EVENT_RECORD) const;
	Key getJumpKeys() const { return jumpKeys; }
	Key getQuitKeys() const { return quitKeys; }
private:
	// Codes
	const vector<int> jumpKeyCodes = {32, 38, 38};
	const vector<int> quitKeyCodes = { 27, 81 };
	// Keys
	Key jumpKeys;
	Key quitKeys;
};