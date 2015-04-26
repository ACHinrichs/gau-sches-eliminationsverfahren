// gauss_lgs.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
using namespace std;



int dimension = 1;

void matrixAusgeben(double** matrix){
	cout << "\n";
	for (int y = 0; y < dimension; y++){
		for (int x = 0; x < dimension + 1; x++){
			if (x == dimension)
				cout << "| ";
			cout << matrix[y][x] << " ";
		}
		cout << "\n";
	}
}



//Rechnet a = a * b
double* mal(double* a, double b){
	double* r = new double[dimension + 1];
	for (int i = 0; i < dimension + 1; i++)
	{
		r[i] = a[i] * b;
	}
	return r;
}

//Rechnet a = a - b
double* matrixMinus(double* a, double* b){
	double* r = new double[dimension + 1];
	for (int i = 0; i < dimension+1; i++)
	{
		r[i] = a[i] - b[i];
	}
	return r;
}

void loese(double** matrix){
	//"linkes unteres dreieck" der Matrix "nullen"
	for (int i = 1; i < dimension; i++)	{
		for (int j = 0; j < i; j++){
			double* a = matrix[i];
			if ((matrix[i][j] != 0)&&(matrix[j][j] != 0)){
				double* b = mal(matrix[j], a[j] / matrix[j][j]);
				matrix[i] = matrixMinus(a, b);
				delete[] b;
			}
			//delete [] a;// a ist nur eine Referenz auf matrix[i]! 
			//cout << "\n";
			matrixAusgeben(matrix);
		}
	}


	//Rueckwaerts einsetzen
	for (int i = dimension - 1; i >= 0; i--){	//dimension -2, weil dimension -1 die unterste Zeile ist, in welcher aber nichts eingesetzt werden muss/darf/kann!
		double x = matrix[i][i];
		double y = matrix[i][dimension];
		for (int j = 0; j < i; j++){
			matrix[j][dimension] = matrix[j][dimension] - y / x * matrix[j][i];
			matrix[j][i] = 0;
		}
	}

	// Werte auf 1 bringen
	for (int i = 0; i < dimension; i++){
		matrix[i] = mal(matrix[i], 1 / matrix[i][i]);
	}

}


int _tmain(int argc, _TCHAR* argv[])
{
	//Dimension der matrix abfragen
	cout << "Groesse der Matrix, welche zu loesen ist: ";
	cin>> dimension;


	//Array anlegen
	double** matrix = new double*[dimension];

	for (int i = 0; i < dimension; i++)
		matrix[i] = new double[dimension + 1];



	//Matrix füllen

	for (int y = 0; y < dimension; y++){
		for (int x = 0; x < dimension + 1; x++){
			cout << "Wert der matrix in " << y+1 << " " << x+1 << ": ";
			cin >> matrix[y][x];
		}
	}

	cout << "Matrix, welche zu loesen ist:\n";
	matrixAusgeben(matrix);

	//loesen der Matrix
	loese(matrix);


	cout << "Ergebniss des Gauss-Verfahrens:\n";
	matrixAusgeben(matrix);

	//Alloziiertes Array wieder freigeben;
	for (int i = 0; i < dimension; i++)
		delete [] matrix[i];
	delete[] matrix;


	cin >> dimension;


	return 0;
}

