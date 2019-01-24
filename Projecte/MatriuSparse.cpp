#include "MatriuSparse.h"

MatriuSparse::MatriuSparse()
{
	maxRowCol = 0;
}

MatriuSparse::MatriuSparse(const MatriuSparse & ms)
{
	maxRowCol = ms.maxRowCol;
	for (int aux = 0; aux < ms.coordVector.size(); aux++) {
		coordVector.emplace_back((ms.coordVector.at(aux)));
	}
}

MatriuSparse::MatriuSparse(string fitxert)
{
	ifstream myReadFile;
	myReadFile.open(fitxert);
	string line = "";
	int sizeCount = 0, row = 0, col = 0;
	if (myReadFile.is_open())
	{
		if (!myReadFile.eof())
		{
			while (getline(myReadFile, line)) {
				stringstream ss(line);
				bool primerVec = true;
				while (getline(ss, line, '\t')) {
					if (line != "")
					{
						row = stoi(line);
						getline(ss, line, '\t');
						col = stoi(line);
						Coordinates coord(row, col, 1);
						coordVector.emplace_back(coord);
						if (row > (maxRowCol - 1)) {
							maxRowCol = row + 1;
						}
						if (col > (maxRowCol - 1)) {
							maxRowCol = col + 1;
						}
					}
				}

			}
		}
		myReadFile.close();
	}
}

MatriuSparse::~MatriuSparse()
{
	coordVector.clear();
}

void MatriuSparse::setVal(const int & nFiles, const int & nColumnes, const int & valor)
{
	if (valor != 0)
	{
		bool trobat = false;
		for (int i = 0; i < coordVector.size(); i++)
		{
			if (coordVector.at(i).getRow() == nFiles && coordVector.at(i).getCol() == nColumnes)
			{
				coordVector.at(i).setVal(valor);
				trobat = true;
			}
		}
		if (!trobat)
		{
			coordVector.emplace_back(Coordinates(nFiles, nColumnes, valor));

			if (nFiles > (maxRowCol - 1))
			{
				maxRowCol = nFiles + 1;
			}
			else {
				sortVectors();
			}
			if (nColumnes > (maxRowCol - 1))
			{
				maxRowCol = nColumnes + 1;
			}
		}
	}
}

bool MatriuSparse::getVal(int nFiles, int nColumnes, float& valor)
{
	if (nFiles < maxRowCol && nColumnes < maxRowCol) {
		bool found = false;
		for (Coordinates coord : coordVector) {
			if (coord.getRow() == nFiles && coord.getCol() == nColumnes) {
				valor = coord.getVal();
				found = true;
			}
			if (coord.getRow() > nFiles || (coord.getRow() == nFiles && coord.getCol() > nColumnes)) {
				break;
			}
		}
		if (!found) {
			valor = 0;
		}
		return true;
	}
	else {
		return false;
	}
}

void MatriuSparse::sortVectors() {
	sort(coordVector.begin(), coordVector.end(), less<Coordinates>());
}

MatriuSparse MatriuSparse::operator*(int n)
{
	MatriuSparse newMatriu;
	newMatriu.maxRowCol = maxRowCol;
	for (Coordinates coord : coordVector) {
		newMatriu.coordVector.emplace_back(Coordinates(coord.getRow(), coord.getCol(), coord.getVal()*n));
	}
	return newMatriu;
}

vector<float> MatriuSparse::operator*(vector<float> n)
{
	vector<float> newVector;
	float result = 0;
	int position = 0;
	for (int aux = 0; aux < maxRowCol; aux++) {
		for (int aux2 = position; aux2 < coordVector.size(); aux2++) {
			if (coordVector.at(aux2).getRow() == aux) {
				result += n.at(coordVector.at(aux2).getCol()) * coordVector.at(aux2).getVal();
			}
			if (coordVector.at(aux2).getRow() > aux) {
				position = aux2;
				aux2 = coordVector.size();
			}
		}
		newVector.emplace_back(result);
		result = 0;
	}
	return newVector;
}

MatriuSparse MatriuSparse::operator/(int  n)
{
	MatriuSparse newMatriu;
	newMatriu.maxRowCol = maxRowCol;
	for (Coordinates coord : coordVector) {
		newMatriu.coordVector.emplace_back(Coordinates(coord.getRow(), coord.getCol(), coord.getVal() / n));
	}
	return newMatriu;
}

ostream & operator<<(ostream & out, const MatriuSparse & md)
{
	out << "MATRIU DE (FILES: " << md.maxRowCol << "  COLUMNES: " << md.maxRowCol << " )" << endl;
	out << "VALORS (FILA::COL::VALOR)" << endl;
	for (Coordinates coord : md.coordVector) {
		out << coord;
	}
	out << endl;
	return out;
}
