#pragma once


#include "MinoGenerator.h"

class FieldControl :
	public Field
{
public:
	FieldControl();
	void GenerateMino();
	bool LandingMino();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void FallAtOnce();
	void RotateMino(int direction);
	void ExchangeForHold();
	char GetTrueValue(unsigned int y, unsigned int x);
	Tetrimino GetHold();
	Tetrimino CheckNext(int idx);
	int VanishLine();
	bool IsGameOver();
private:
	void FixMino();
	bool IsCorrectLocation();
	int CountMinocellOnLine(int line);
	MinoGenerator next_mino;
	Tetrimino handlemino;
	Tetrimino holdmino;
	int x;
	int y;
};

