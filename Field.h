#pragma once

#include"Tetrimino.h"

typedef char minocell;

class Field
{
public:
	Field();
	~Field();
	void ChangeSize(unsigned int line, unsigned int column);
	unsigned int GetColumn();
	unsigned int GetLine();
	minocell GetValue(unsigned int y, unsigned int x);
	void SetValue(unsigned int y, unsigned int x, minocell value);
private:
	unsigned int column;
	unsigned int line;
	minocell* field;
	void Release();
};
