#pragma once

class MinoGenerator {
public:
	MinoGenerator(int next_num);
	~MinoGenerator();
	Tetrimino Pop();
	Tetrimino GetValue(int idx);
	Tetrimino operator[](int idx);
private:
	Tetrimino* nexts;
	int next_num;
};
