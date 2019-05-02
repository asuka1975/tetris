#pragma once

#include"Matrix4.h"

#define LEFT -1
#define RIGHT 1

enum minotype { I_MINO, O_MINO, S_MINO, Z_MINO, J_MINO, L_MINO, T_MINO, NONE };

class Tetrimino
{
public:
	Tetrimino();
	Tetrimino(minotype t);
	Tetrimino(const Tetrimino& obj);
	~Tetrimino();
	void Rotate(int direction);
	char operator()(unsigned int x, unsigned int y);
	Tetrimino& operator=(const Tetrimino& obj);
	minotype GetMinotype();
	static void InitMino();
private:
	Matrix4 mino;
	minotype type;
	int rotation;
};

