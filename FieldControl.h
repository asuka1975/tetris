#pragma once

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
	char GetTrueValue(unsigned int y, unsigned int x);
	int VanishLine();
	bool IsGameOver();
private:
	void FixMino();
	bool IsCorrectLocation();
	int CountMinocellOnLine(int line);
	Tetrimino handlemino;
	int x;
	int y;
};

