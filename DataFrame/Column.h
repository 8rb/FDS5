#pragma once
#include <vector>
#include <stdlib.h>
#include <string>
#include "Row.h"

using namespace std;

class Column {

	vector <Row> rows;
	string nombre;
	string tipo;

public:
	Column() {
		tipo = " ";
		string nombre;
	}
	void setNombre(string nombre) { this->nombre = nombre; }
	string getNombre() { return nombre; }
	string getDataAt_j(int j) {
		
		return rows.at(j).getInfo();
	}
	void setDataAt_j(int j, string data) {

		rows.at(j).setInfo(data);
	}
	void add(Row r) {
		rows.push_back(r);
	}
	string GetTipo() { return tipo; }
	int GetSizeIterador(int i) {
		return rows.at(i).GetSize();
	}
	void ErasePosition(int pos) {
		rows.erase(rows.begin() + pos);
	}

private:
	int FindType(string j) {
		if ((j[0] >= 32 && j[0] <= 47) || (j[0] >= 58)) {
			return 0; //retorna 0 si es string
		}
		else {
			double aux = stod(j);
			int aux2 = int(aux);
			if (aux != (double)aux2) {
				return -1; //retorna -1 si es double
			}
			else {
				return 1;//retorna 1 si es int 
			}
		}
	}
	void CambiarPosición(int i, int j ) {
		string temporal = rows.at(i).getInfo();
		rows[i].setInfo(rows[j].getInfo());
		rows[j].setInfo(temporal);
	}
public:
	void StaType(Row r) { // establecer tipo
		if (FindType(r.getInfo()) == 0) {
			tipo = "string";
		}
		else if (FindType(r.getInfo()) == -1) {
			tipo = "Double";
		}
		else if (FindType(r.getInfo()) == 1) {
			tipo = "Int";
		}
	}

};
