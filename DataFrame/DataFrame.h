#pragma once
#include "AVLTree.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include "Column.h"
#include "Row.h"
#include "Controladora.h"

using namespace std;

//DATOS CON FORMATO:
//NOMBRE - APELLIDO - EQUIPO - SEXO - EDAD - NUMERO
//STRING - STRING   - STRING - CHAR - INT  - INT

class DataFrame {

	vector <Column*>* columns;
	bool shortened = true; //PUNTOS .... DEL MOSTRAR

	int nc;
	int nf;
	int numCol = 1;
	int numFil = 1;

public:
	DataFrame() {
		columns = new vector<Column*>;
		
		nc = 0;
		nf = 0;
	}
	~DataFrame() {
		delete columns;
	}
	void importData(char sep) {

		ifstream archivo;
		ifstream temporal;
		archivo.open("sample.txt"); //Recordar cambiarlo
		temporal.open("sample.txt"); //recordar cambiarlo
		string linea;
		getline(temporal, linea);
		if (sep == 'C' || sep == 'c') {
			//FOR PARA SABER LA CANTIDAD DE COLUMNAS
			for (int i = 0; i < linea.size(); i++) {
				if (linea[i] == ',') numCol++;
			}
			//FOR PARA TENER CREADAS TODAS LAS COLUMNAS
			for (int i = 0; i < numCol; i++) {
				Column* columna;
				columna = new Column();
				columns->push_back(columna);
			}
			temporal.close();
			temporal.open("sample.txt");
			//asignar nombre
			for (int i = 0; i < numCol; i++) {
				if (i == numCol - 1) {
					getline(temporal, linea, '\n');
					columns->at(i)->setNombre(linea);		
				}
				else {
					getline(temporal, linea, ',');
					columns->at(i)->setNombre(linea);
				}
				
			}
			temporal.close();
			int i = 0;
			numFil = 1;
			linea = " ";
			while (archivo.good()) {
				if (i == numCol) {
					i = 0;
					numFil++;
				}
				if (i == numCol - 1) {
					getline(archivo, linea, '\n');
					Row* row;
					row = new Row();
					row->setInfo(linea);
					columns->at(i)->add(*row);
					if (numFil == 2) {
						columns->at(i)->StaType(*row);
					}
				}
				else {
					getline(archivo, linea, ',');
					Row* row;
					row = new Row();
					row->setInfo(linea);
					columns->at(i)->add(*row);
					if (numFil == 2) {
						columns->at(i)->StaType(*row);
					}
				}
				i++;
			}
		}
		else if (sep == 'T' || sep == 't') {
			//FOR PARA SABER LA CANTIDAD DE COLUMNAS
			for (int i = 0; i < linea.size(); i++) {
				if (linea[i] == '	') numCol++;
			}
			//FOR PARA TENER CREADAS TODAS LAS COLUMNAS
			for (int i = 0; i < numCol; i++) {
				Column* columna;
				columna = new Column();
				columns->push_back(columna);
			}
			int i = 0;
			numFil = 1;
			linea = " ";
			while (archivo.good()) {
				if (i == numCol) {
					i = 0;
					numFil++;
				}

				if (i == numCol - 1) {
					getline(archivo, linea, '\n');
					Row* row;
					row = new Row();
					row->setInfo(linea);
					columns->at(i)->add(*row);
					if (numFil == 2) {
						columns->at(i)->StaType(*row);
					}
				}
				else {
					getline(archivo, linea, '	');
					Row* row;
					row = new Row();
					row->setInfo(linea);
					columns->at(i)->add(*row);
					if (numFil == 2) {
						columns->at(i)->StaType(*row);
					}
				}
				i++;
			}

		}
		cout << columns->at(8)->GetTipo();
		Mostrar();
	}
	void indexData(vector<int> poscol) {
		Arbolito<string>* ColumnTree = new Arbolito<string>();
		for (int i = 0; i < poscol.size(); i++) {
			for (int j = 0; j < numFil; j++) {
				ColumnTree->Add(columns->at(poscol.at(i))->getDataAt_j(j));
			}
		}
		cout << "Indexado realizado satisfactoriamente :)" << endl;
	}
	void Mostrar() {
		
		cout << endl << endl << "SHOWING DATAFRAME:" << endl;
		cout << "////////////////////////////////////////" << endl;

		//MUESTRA EL CONTENIDO CON LOS .. O SIN ELLOS
		if (shortened) {
			for (int j = 0; j < numFil; j++) {
				for (int i = 0; i < numCol; i++) {
					if (columns->at(i)->getDataAt_j(j).size() >= 8) {
						cout << columns->at(i)->getDataAt_j(j)[0] << columns->at(i)->getDataAt_j(j)[1] << columns->at(i)->getDataAt_j(j)[2] << "..." << "		";
					}
					else cout << columns->at(i)->getDataAt_j(j) << "		";
				}
				cout << endl;
			}
		}
		else {
			for (int j = 0; j < numFil; j++) {
				for (int i = 0; i < numCol; i++) {
					cout << columns->at(i)->getDataAt_j(j) << "	";
				}
				cout << endl;
			}
		}
	}
	DataFrame* selectData(vector<int> poscol) {

		DataFrame* dfNuevo = new DataFrame();
		dfNuevo->numCol = poscol.size();
		dfNuevo->numFil = numFil;
		for (int i = 0; i < poscol.size(); i++) {
			dfNuevo->columns->push_back(columns->at(poscol.at(i)));
		}
		return dfNuevo;
	}
	void DobleFiltro(int col1, int col2) {
		char El1, El2;
		DataFrame* p;
		int num;
		string zh;
		cout << "Ingrese los parametro por el cual desea filtrar(escriba los 2 separados por un espacio): " << endl;
		cout << "a. Mayor que x" << endl;
		cout << "b. Menor que x " << endl;
		cout << "c. Igual que x " << endl;
		cout << "d. Inicia con: " << endl;
		cout << "e. Finaliza con: " << endl;
		cout << "f. Est� contenido en: " << endl;
		cout << "g. No est� contenido en: " << endl;
		cin >> El1 >> El2;
		switch (El1)
		{
		case 'a':
			cout << "Ingrese el numero: " << endl;
			cin >> num;
			p = NuevoFilterMayor(col1, num, 0);
			break;
		case 'b':
			cout << "Ingrese el numero: " << endl;
			cin >> num;
			p = NuevoFilterMenor(col1, num, 0);
			break;
		case 'c':
			cout << "Ingrese el numero: " << endl;
			cin >> num;
			p = NuevoFilterIgual(col1, num, 0);
			break;
		case 'd':
			cout << "Ingrese el numero o letra con el cual quieres que empieze: " << endl;
			cin >> zh;
			p = NuevoFilterInicia(col1, zh, 0);
			break;
		case 'e':
			cout << "Ingrese el numero o letra con el cual quieres que termine: " << endl;
			cin >> zh;
			p = NuevoFilterTermina(col1, zh, 0);
			break;
		case 'f':
			cout << "Ingrese el digito o la letra que quieres que este contenida" << endl;
			cin >> zh;
			p = NuevoFilterEsta(col1, zh, 0);
			break;
		case 'g':
			cout << "Ingrese el digito o la letra que NO quieres que este contenida" << endl;
			cin >> zh;
			p = NuevoFilterNoEsta(col1, zh, 0);
			break;
		  
		}
		switch (El2)
		{
		case 'a':
			cout << "Ingrese el numero: " << endl;
			cin >> num;
			p->NuevoFilterMayor(col2, num, 1);
			break;
		case 'b':
			cout << "Ingrese el numero: " << endl;
			cin >> num;
			p->NuevoFilterMenor(col2, num, 1);
			break;
		case 'c':
			cout << "Ingrese el numero: " << endl;
			cin >> num;
			p->NuevoFilterIgual(col2, num, 1);
			break;
		case 'd':
			cout << "Ingrese el numero o letra con el cual quieres que empieze: " << endl;
			cin >> zh;
			p ->NuevoFilterInicia(col2, zh, 1);
			break;
		case 'e':
			cout << "Ingrese el numero o letra con el cual quieres que empieze: " << endl;
			cin >> zh;
			p ->NuevoFilterTermina(col2, zh, 1);
			break;
		case 'f':
			cout << "Ingrese el digito o la letra que quieres que este contenida" << endl;
			cin >> zh;
			p->NuevoFilterEsta(col2, zh, 1);
			break;
		case 'g':
			cout << "Ingrese el digito o la letra que NO quieres que este contenida" << endl;
			cin >> zh;
			p->NuevoFilterNoEsta(col2, zh, 1);
			break;

		}
	}
	void filterDataContenido(int c, int m) {
		DataFrame df_Filtered = DataFrame();
		df_Filtered.columns = this->columns;
		df_Filtered.numCol = this->numCol;
		df_Filtered.numFil = this->numFil;
		for (int j = 0; j < df_Filtered.numFil; j++) {
			if (stoi(df_Filtered.columns->at(c)->getDataAt_j(j)) <= m) {
				for (int i = 0; i < df_Filtered.numCol; i++) {
					df_Filtered.columns->at(i)->setDataAt_j(j, " ");
				}
			}
		}
		cout << endl;
		for (int j = 0; j < numFil; j++) {
			for (int i = 0; i < numCol; i++) {
				if (df_Filtered.columns->at(i)->getDataAt_j(j) != " ") {
					cout << df_Filtered.columns->at(i)->getDataAt_j(j) << "		";
				}
			}
			cout << endl;
		}
	}
	DataFrame* sortData(int col) {
		DataFrame* dfNuevo = new DataFrame();
		dfNuevo->numCol = numCol;
		dfNuevo->numFil = numFil;
		for (int i = 0; i < numCol; i++) {
			dfNuevo->columns->push_back(columns->at(i));
		}

		if (dfNuevo->columns->at(col)->GetTipo() == "string")
		{
			quicksort(dfNuevo->columns, 1, numFil - 1, col); 
		}
		else if (dfNuevo->columns->at(col)->GetTipo() == "Int") {
			quicksortInt(dfNuevo->columns, 1, numFil - 1, col);
		}
		else if (dfNuevo->columns->at(col)->GetTipo() == "Double") {
			quicksortDouble(dfNuevo->columns, 1, numFil - 1, col);
		}
		return dfNuevo;
	}
	void exportData(int formato) {
		ofstream exported;

		switch (formato)
		{
		case 1:
			exported.open("exported.csv"); //FORMATO CSV
			for (int j = 0; j < numFil; j++) {
				for (int i = 0; i < numCol; i++) {
					if (i != numCol - 1) {
						exported << columns->at(i)->getDataAt_j(j) << ",";
					}
					else exported << columns->at(i)->getDataAt_j(j) << "";
				}
				exported << endl;
			}
			break;
		case 2:
			exported.open("exported.tsv");
			for (int j = 0; j < numFil; j++) {
				for (int i = 0; i < numCol; i++) {
					if (i != numCol - 1) {
						exported << columns->at(i)->getDataAt_j(j) << "	";
					}
					else exported << columns->at(i)->getDataAt_j(j) << "";
				}
				exported << endl;
			}
			break;
		default:
			cout << "wrong output";
			break;
		}
		exported.close();
	}
	void crear(int numFil, int numCol) {
		this->numFil = numFil;
		this->numCol = numCol;
		string s = " ";
		for (int i = 0; i < numCol; i++) {

			Column* columna;
			columna = new Column();
			columns->push_back(columna);

			for (int j = 0; j < numFil; j++) {

				Row* row;
				row = new Row();
				cout << "Ingrese elemento en la columna: " << i + 1 << " y fila: " << j + 1 << endl;
				cin >> s;
				row->setInfo(s);
				columns->at(i)->add(*row);
				columns->at(i)->StaType(*row);
			}
		}
		Mostrar();

	}
	int getLength() {
		return columns->size();
	}
	void setVisualization(bool shortened) {
		this->shortened = shortened;
	}
	bool getVisualization() {
		return shortened;
	}

	DataFrame* GetMayor(int columnas, int dato, int mostrar) {
		return NuevoFilterMayor(columnas, dato, mostrar);
	}
	DataFrame* GetMenor(int columnas, int dato, int mostrar) {
		return NuevoFilterMenor(columnas, dato, mostrar);
	}
	DataFrame* GetIgual(int columnas, int dato, int mostrar) {
		return NuevoFilterIgual(columnas, dato, mostrar);
	}
	DataFrame* GetInicia(int columnas, string dato, int mostrar) {
		return NuevoFilterInicia(columnas, dato, mostrar);
	}
	DataFrame* GetTermina(int columnas, string dato, int mostrar) {
		return NuevoFilterTermina(columnas, dato, mostrar);
	}
	DataFrame* GetContiene(int columnas, string dato, int mostrar) {
		return NuevoFilterEsta(columnas, dato, mostrar);
	}
	DataFrame* GetNoContiene(int columnas, string dato, int mostrar) {
		return NuevoFilterNoEsta(columnas, dato, mostrar);
	}

	void OtroMostrar(DataFrame* df) {
		for (int j = 0; j < df->numFil; j++) {
			for (int i = 0; i < df->numCol; i++) {
				cout << df->columns->at(i)->getDataAt_j(j) << " ";
			}
			cout << endl;
		}
	}
private:
	void Limpiar() {
		string x;
		x = "                                                      ";
		ofstream archivo("peladas.txt");
		if (!archivo.is_open()) {
			cout << "error";
		}
		archivo << x;
		archivo.flush();
		archivo.close();
	}
	bool estaVacio() {
		string x;
		ifstream archivo("peladas.txt");
		archivo >> x;
		archivo.close();
		if (x == " ") return true;

	}
	bool IsInside(string a, string comp) {
		char compara = comp[0];
		return a.find(compara) != std::string::npos;
	}
	//by vilaron

	DataFrame* NuevoFilterMayor(int columnas, long  dato, int mostrar) {
		DataFrame* df_filtrado = new DataFrame();
		df_filtrado->numCol = this->numCol;
		df_filtrado->numFil = 0;
		//df_filtrado.GenerarColumnas(df_filtrado.numCol);
		for (int o = 0; o < df_filtrado->numCol; o++) {
			Column* columnna = new Column();
			df_filtrado->columns->push_back(columnna);
		}
		//inicializar Rows
		for (int j = 0; j < numFil; j++) {
			if (atoi(columns->at(columnas)->getDataAt_j(j).c_str()) > dato) {
				for (int i = 0; i < df_filtrado->numCol; i++) {
					Row* row = new Row();
					row->setInfo(columns->at(i)->getDataAt_j(j));
					df_filtrado->columns->at(i)->add(*row);
				}
				df_filtrado->numFil++;
			}
		}
		if (mostrar == 1) {
			OtroMostrar(df_filtrado);
		}
		return df_filtrado;
	}
	DataFrame* NuevoFilterMenor(int columnas, int dato, int mostrar) {
		DataFrame* df_filtrado = new DataFrame();
		df_filtrado->numCol = this->numCol;
		df_filtrado->numFil = 0;
		//df_filtrado.GenerarColumnas(df_filtrado.numCol);
		for (int o = 0; o < df_filtrado->numCol; o++) {
			Column* columnna = new Column();
			df_filtrado->columns->push_back(columnna);
		}
		//inicializar Rows
		for (int j = 0; j < numFil; j++) {
			if (atoi(columns->at(columnas)->getDataAt_j(j).c_str()) < dato) {
				for (int i = 0; i < df_filtrado->numCol; i++) {
					Row* row = new Row();
					row->setInfo(columns->at(i)->getDataAt_j(j));
					df_filtrado->columns->at(i)->add(*row);
				}
				df_filtrado->numFil++;
			}
		}
		cout << endl;
		if (mostrar == 1) {
			OtroMostrar(df_filtrado);
		}
		return df_filtrado;
	}
	DataFrame* NuevoFilterIgual(int columnas, int dato, int mostrar) {
		DataFrame* df_filtrado = new DataFrame();
		df_filtrado->numCol = this->numCol;
		df_filtrado->numFil = 0;
		for (int o = 0; o < df_filtrado->numCol; o++) {
			Column* columnna = new Column();
			df_filtrado->columns->push_back(columnna);
		}
		for (int j = 0; j < numFil; j++) {
			if (atoi(columns->at(columnas)->getDataAt_j(j).c_str()) == dato) {
				for (int i = 0; i < df_filtrado->numCol; i++) {
					Row* row = new Row();
					row->setInfo(columns->at(i)->getDataAt_j(j));
					df_filtrado->columns->at(i)->add(*row);
				}
				df_filtrado->numFil++;
			}
		}
		cout << endl;
		if (mostrar == 1) {
			OtroMostrar(df_filtrado);
		}
		return df_filtrado;
	}
	DataFrame* NuevoFilterInicia(int columnas, string dato, int mostrar) {
		DataFrame* df_filtrado = new DataFrame();
		df_filtrado->numCol = this->numCol;
		df_filtrado->numFil = 0;
		for (int o = 0; o < df_filtrado->numCol; o++) {
			Column* columnna = new Column();
			df_filtrado->columns->push_back(columnna);
		}
		for (int j = 0; j < numFil; j++) {
			if (columns->at(columnas)->getDataAt_j(j)[0] == dato[0]) {
				for (int i = 0; i < df_filtrado->numCol; i++) {
					Row* row = new Row();
					row->setInfo(columns->at(i)->getDataAt_j(j));
					df_filtrado->columns->at(i)->add(*row);
				}
				df_filtrado->numFil++;
			}
		}
		cout << endl;
		if (mostrar == 1) {
			OtroMostrar(df_filtrado);
		}
		return df_filtrado;
	}
	DataFrame* NuevoFilterTermina(int columnas, string dato, int mostrar) {
		DataFrame* df_filtrado = new DataFrame();
		df_filtrado->numCol = this->numCol;
		df_filtrado->numFil = 0;
		for (int o = 0; o < df_filtrado->numCol; o++) {
			Column* columnna = new Column();
			df_filtrado->columns->push_back(columnna);
		}
		for (int j = 0; j < numFil; j++) {
			if (columns->at(columnas)->getDataAt_j(j)[columns->at(columnas)->GetSizeIterador(j) - 1] == dato[0]) {
				for (int i = 0; i < df_filtrado->numCol; i++) {
					Row* row = new Row();
					row->setInfo(columns->at(i)->getDataAt_j(j));
					df_filtrado->columns->at(i)->add(*row);
				}
				df_filtrado->numFil++;
			}
		}
		cout << endl;
		if (mostrar == 1) {
			OtroMostrar(df_filtrado);
		}
		return df_filtrado;
	}
	DataFrame* NuevoFilterEsta(int columnas, string dato, int mostrar) {
		DataFrame* df_filtrado = new DataFrame();
		df_filtrado->numCol = this->numCol;
		df_filtrado->numFil = 0;
		for (int o = 0; o < df_filtrado->numCol; o++) {
			Column* columnna = new Column();
			df_filtrado->columns->push_back(columnna);
		}
		for (int j = 0; j < numFil; j++) {
			if (IsInside(columns->at(columnas)->getDataAt_j(j), dato)) {
				for (int i = 0; i < df_filtrado->numCol; i++) {
					Row* row = new Row();
					row->setInfo(columns->at(i)->getDataAt_j(j));
					df_filtrado->columns->at(i)->add(*row);
				}
				df_filtrado->numFil++;
			}
		}
		cout << endl;
		if (mostrar == 1) {
			OtroMostrar(df_filtrado);
		}
		return df_filtrado;
	}
	DataFrame* NuevoFilterNoEsta(int columnas, string dato, int mostrar) {
		DataFrame* df_filtrado = new DataFrame();
		df_filtrado->numCol = this->numCol;
		df_filtrado->numFil = 0;
		for (int o = 0; o < df_filtrado->numCol; o++) {
			Column* columnna = new Column();
			df_filtrado->columns->push_back(columnna);
		}
		for (int j = 0; j < numFil; j++) {
			if (!IsInside(columns->at(columnas)->getDataAt_j(j), dato)) {
				for (int i = 0; i < df_filtrado->numCol; i++) {
					Row* row = new Row();
					row->setInfo(columns->at(i)->getDataAt_j(j));
					df_filtrado->columns->at(i)->add(*row);
				}
				df_filtrado->numFil++;
			}
		}
		cout << endl;
		if (mostrar == 1) {
			for (int j = 0; j < df_filtrado->numFil; j++) {
				for (int i = 0; i < df_filtrado->numCol; i++) {
					cout << df_filtrado->columns->at(i)->getDataAt_j(j) << " ";
				}
				cout << endl;
			}
		}
		return df_filtrado;
	}
	void swapy(vector<Column*>*& v, int x, int y) {
		for (int k = 0; k < v->size(); k++) {
			string temporal = columns->at(k)->getDataAt_j(x);
			columns->at(k)->setDataAt_j(x, columns->at(k)->getDataAt_j(y));
			columns->at(k)->setDataAt_j(y, temporal);
		}
	}
	void quicksort(vector<Column*>* &cols, int L, int R, int col) {
		string piv;
		int i, j, mid;
		i = L;
		j = R;
		mid = L + (R - L) / 2;
		piv = cols->at(col)->getDataAt_j(mid);

		while (i<R || j>L) {
			while (cols->at(col)->getDataAt_j(i) < piv)
				i++;
			while (cols->at(col)->getDataAt_j(j) > piv)
				j--;

			if (i <= j) {
				swapy(cols, i, j);
				i++;
				j--;
			}
			else {
				if (i < R)
					quicksort(cols, i, R, col);
				if (j > L)
					quicksort(cols, L, j, col);
				return;
			}
		}
	}
	void quicksortInt(vector<Column*>* &cols, int L, int R, int col) {
		int piv;
		int i, j, mid;
		i = L;
		j = R;
		mid = L + (R - L) / 2;
		piv = stoi(cols->at(col)->getDataAt_j(mid));

		while (i<R || j>L) {
			while (stoi(cols->at(col)->getDataAt_j(i)) < piv)
				i++;
			while (stoi(cols->at(col)->getDataAt_j(j)) > piv)
				j--;

			if (i <= j) {
				swapy(cols, i, j);
				i++;
				j--;
			}
			else {
				if (i < R)
					quicksortInt(cols, i, R, col);
				if (j > L)
					quicksortInt(cols, L, j, col);
				return;
			}
		}
	}
	void quicksortDouble(vector<Column*>* &cols, int L, int R, int col) {
		int piv;
		int i, j, mid;
		i = L;
		j = R;
		mid = L + (R - L) / 2;
		piv = stod(cols->at(col)->getDataAt_j(mid));

		while (i<R || j>L) {
			while (stod(cols->at(col)->getDataAt_j(i)) < piv)
				i++;
			while (stod(cols->at(col)->getDataAt_j(j)) > piv)
				j--;

			if (i <= j) {
				swapy(cols, i, j);
				i++;
				j--;
			}
			else {
				if (i < R)
					quicksortInt(cols, i, R, col);
				if (j > L)
					quicksortInt(cols, L, j, col);
				return;
			}
		}
	}

};
