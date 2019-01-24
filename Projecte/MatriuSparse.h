#pragma once
#include "Coordinates.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

class MatriuSparse {
public:
	MatriuSparse();
	MatriuSparse(const MatriuSparse &ms);
	MatriuSparse(string fitxert);
	~MatriuSparse();
	void setVal(const int& nFiles, const  int& nColumnes, const int& valor);
	bool getVal(int nFiles, int nColumnes, float &valor);
	void sortVectors();
	int getNFiles() { return maxRowCol; };
	MatriuSparse operator* (int n);
	//MatriuSparse operator* (int& n);
	vector<float> operator* (vector<float> n);
	MatriuSparse operator/ (int n);
	friend ostream& operator<<(ostream& out, const MatriuSparse& md);
private:
	vector<Coordinates> coordVector;
	int maxRowCol;
};