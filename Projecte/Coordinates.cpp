#include "Coordinates.h"

Coordinates::Coordinates()
{
	row = 0;
	col = 0;
	val = 0;
}

Coordinates::Coordinates(const Coordinates &c) {
	row = c.row;
	col = c.col;
	val = c.val;
}

Coordinates::Coordinates(int r, int c, int v)
{
	row = r;
	col = c;
	val = v;
}


Coordinates::~Coordinates()
{
}

bool Coordinates::operator<(const Coordinates & c) const
{
	if (row != c.row) {
		return row < c.row;
	}
	else {
		return col < c.col;
	}
}

ostream & operator<<(ostream & out, const Coordinates & c)
{
	out << "( " << c.row << " :: " << c.col << " :: " << c.val << " ) " << endl;
	return out;
}
