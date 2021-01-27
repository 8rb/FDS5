#include <iostream>
#include <clocale>
#include "Controladora.h"
using namespace std;
using namespace System;

int main() {
	setlocale(LC_ALL, "spanish");
	system("Color 0A");

	Controladora control = Controladora();
	control.menu();

	return 0;
}