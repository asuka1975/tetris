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
	void PredictFallAtOnce(bool isfirst);
	void FixMino();
	bool IsCorrectLocation();
	bool PredictIsCorrectLocation();
	int CountMinocellOnLine(int line);
	MinoGenerator nexts;
	Tetrimino handlemino;
	Tetrimino holdmino;
	Tetrimino predictmino;
	int x;
	int y;
	int predict_x;
	int predict_y;
};

