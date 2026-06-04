#include <iostream>
#include <vector>
#include "Key.h"

Key::Key(const std::vector<int> aKeys) {
  keys.resize(aKeys.size());
  for (int i = 0; i < aKeys.size(); i++) {
    keys[i] = aKeys[i];
  }

  keys[0] = aKeys[0];
}