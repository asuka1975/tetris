#include <cstdlib>
#include <ctime>
#include "Field.h"
#include "FieldControl.h"



FieldControl::FieldControl() : Field(), handlemino(NONE), holdmino(NONE), predictmino(NONE), nexts(3)
{
	x = 0;
	y = 0;
}

void FieldControl::GenerateMino()
{
	x = GetColumn() / 2 - 3;
	predict_y = y = -1;
	handlemino = nexts.Pop();

	PredictFallAtOnce(true);
}

bool FieldControl::LandingMino()
{
	if (handlemino.GetMinotype() == NONE) return true;
	for (int y = 3; y >= 0; y--) {
		for (int x = 0; x < 4; x++) {
			if (handlemino(x, y) != ' ' && GetValue(this->y + y + 1, this->x + x ) != ' ') {
				FixMino();
				return true;
			}
		}
	}
	return false;
}

void FieldControl::MoveLeft()
{
	x--;
	if (!IsCorrectLocation()) x++;

	PredictFallAtOnce(true);
}

void FieldControl::MoveRight()
{
	x++;
	if (!IsCorrectLocation()) x--;

	PredictFallAtOnce(true);
}

void FieldControl::MoveDown()
{
	y++;
	if (!IsCorrectLocation()) y--;
}

void FieldControl::FallAtOnce()
{
	y++;
	if (!IsCorrectLocation()) y--;
	else FallAtOnce();

	PredictFallAtOnce(true);
}

void FieldControl::RotateMino(int direction)
{
	handlemino.Rotate(direction);
	predictmino.Rotate(direction);
	if (!IsCorrectLocation()) {
		handlemino.Rotate(-direction);
		predictmino.Rotate(-direction);
	}
	PredictFallAtOnce(true);
}

void FieldControl::ExchangeForHold()
{
	if (holdmino.GetMinotype() == NONE) {
		holdmino = handlemino;
		handlemino = nexts.Pop();
		predictmino = handlemino;
	}
	else {
		Tetrimino med = holdmino;
		holdmino = handlemino;
		handlemino = med;
		predictmino = handlemino;
	}
	if (!IsCorrectLocation()) {
		x = (x == 0 ? x + 1 : x - 1);
		predict_x = x;
	}
}

char FieldControl::GetTrueValue(unsigned int y, unsigned int x)
{
	if ((0 <= x - this->x && x - this->x <= 3) && (0 <= y - this->y && y - this->y <= 3) && handlemino(x - this->x, y - this->y) != ' ')
		return handlemino(x - this->x, y - this->y);
	if ((0 <= x - this->predict_x && x - this->predict_x <= 3) && (0 <= y - this->predict_y && y - this->predict_y <= 3) && predictmino(x - this->predict_x, y - this->predict_y) != ' ')
		return predictmino(x - this->predict_x, y - this->predict_y) + 32;

	return GetValue(y, x);
}

Tetrimino FieldControl::GetHold()
{
	return holdmino;
}

Tetrimino FieldControl::CheckNext(int idx)
{
	if (!(0 <= idx && idx <= 3)) return Tetrimino(NONE);
	return nexts[idx];
}

int FieldControl::VanishLine()
{
	int count = 0;
	for (int y = GetLine() - 1; y >= 0; y--) {
		if (CountMinocellOnLine(y) == GetColumn()) {
			for (int j = y - 1; j >= 0; j--) {
				for (int x = 0; x < GetColumn(); x++) {
					SetValue(j + 1, x, GetValue(j, x));
				}
			}
			y++;
			count++;
		}
	}
	return count;
}

bool FieldControl::IsGameOver()
{
	return !IsCorrectLocation();
}

void FieldControl::PredictFallAtOnce(bool isfirst)
{
	if (isfirst) {
		predictmino = handlemino;
		predict_x = x;
		predict_y = y;
	}
	predict_y++;
	if (!PredictIsCorrectLocation()) predict_y--;
	else PredictFallAtOnce(false);
}

void FieldControl::FixMino()
{
	for (int y = 3; y >= 0; y--) {
		for (int x = 0; x < 4; x++) {
			if (GetValue(this->y + y, this->x + x) == ' ') {
				SetValue(this->y + y, this->x + x, handlemino(x, y));
			}
		}
	}
	handlemino = Tetrimino(NONE);
}

bool FieldControl::IsCorrectLocation()
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (handlemino(x, y) != ' ' && (GetValue(this->y + y, this->x + x) != ' ' || GetValue(this->y + y, this->x + x) == '\0')) return false;
		}
	}

	return true;
}

bool FieldControl::PredictIsCorrectLocation()
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (predictmino(x, y) != ' ' && (GetValue(this->predict_y + y, this->predict_x + x) != ' ' || GetValue(this->predict_y + y, this->predict_x + x) == '\0')) return false;
		}
	}

	return true;
}

int FieldControl::CountMinocellOnLine(int line)
{
	int count = 0;
	if (0 <= line && line < GetLine()) {
		for (int x = 0; x < GetColumn(); x++) {
			if (GetValue(line, x) != ' ') count++;
		}
	}

	return count;
}
