#pragma once

#include <vector>

class Key {
public:
	Key(const std::vector<int> aKeys);
	std::vector<int> getKeys() const { return keys; };
private:
	std::vector<int> keys;
};