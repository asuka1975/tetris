#include "Field.h"



Field::Field()
{
	field = nullptr;
	line = 0;
	column = 0;
}

Field::~Field()
{
	if (!field) return;
	delete[] field;
	field = nullptr;
}

void Field::ChangeSize(unsigned int line, unsigned int column)
{
	Release();
	this->line = line;
	this->column = column;
	field = new minocell[line * column];
	for (int i = 0; i < line * column; i++) field[i] = ' ';
}

unsigned int Field::GetColumn()
{
	return column;
}

unsigned int Field::GetLine()
{
	return line;
}

minocell Field::GetValue(unsigned int y, unsigned int x)
{
	if (y >= GetLine() || x >= GetColumn()) return '\0';
	return field[x + y * GetColumn()];
}

void Field::SetValue(unsigned int y, unsigned int x, minocell value)
{
	if (y >= GetLine() || x >= GetColumn()) return;
	field[x + y * GetColumn()] = value;
}

void Field::Release()
{
	if (!field) return;
	delete[] field;
	field = nullptr;
}
