#include <ctime>
#include <cstdlib>
#include "Tetrimino.h"
#include "MinoGenerator.h"

MinoGenerator::MinoGenerator(int next_num) : nexts(new Tetrimino[next_num]), next_num(next_num)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < next_num; i++) {
		nexts[i] = Tetrimino((minotype)(rand() % 7));
	}
}

MinoGenerator::~MinoGenerator()
{
	delete[] nexts;
}

Tetrimino MinoGenerator::Pop()
{
	Tetrimino mino = nexts[next_num - 1];
	for (int i = next_num - 1; i > 0; i--) {
		nexts[i] = nexts[i - 1];
	}
	nexts[0] = Tetrimino((minotype)(rand() % 7));
	return mino;
}

Tetrimino MinoGenerator::GetValue(int idx)
{
	if (0 <= idx && idx < next_num) return Tetrimino(NONE);
	return nexts[idx];
}

Tetrimino MinoGenerator::operator[](int idx)
{
	if (!(0 <= idx && idx < next_num)) return Tetrimino(NONE);
	return nexts[idx];
}


