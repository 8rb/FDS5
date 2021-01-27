#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

class Row {
protected:
	int index;
	string info;

public:
	Row() {
		index = 1;
	}
	void setInfo(string info) {
		this->info = info;
	}
	int GetSize() {
		return info.size();
	}
	string getInfo() { return info; }
};