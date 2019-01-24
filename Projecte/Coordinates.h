#pragma once
#include <iostream>

using namespace std;

class Coordinates
{
public:
	Coordinates();
	Coordinates(const Coordinates &c);
	Coordinates(int r, int c, int v);
	~Coordinates();
	int getRow() { return row; };
	int getCol() { return col; };
	int getVal() { return val; };
	void setVal(int v) { val = v; };
	bool operator < (const Coordinates &c) const;
	friend ostream& operator<<(ostream& out, const Coordinates& c);
private:
	int row;
	int col;
	int val;
};

