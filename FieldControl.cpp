#include <cstdlib>
#include <ctime>
#include "Field.h"
#include "FieldControl.h"



FieldControl::FieldControl() : Field(), handlemino(NONE), holdmino(NONE), next_mino(3)
{
	x = 0;
	y = 0;
}

void FieldControl::GenerateMino()
{
	x = GetColumn() / 2 - 3;
	y = -1;
	handlemino = next_mino.Pop();
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
}

void FieldControl::MoveRight()
{
	x++;
	if (!IsCorrectLocation()) x--;
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
}

void FieldControl::RotateMino(int direction)
{
	handlemino.Rotate(direction);
	if (!IsCorrectLocation()) handlemino.Rotate(-direction);
}

void FieldControl::ExchangeForHold()
{
	if (holdmino.GetMinotype() == NONE) {
		holdmino = handlemino;
		handlemino = next_mino.Pop();
	}
	else {
		Tetrimino med = holdmino;
		holdmino = handlemino;
		handlemino = med;
	}
}

char FieldControl::GetTrueValue(unsigned int y, unsigned int x)
{
	if ((0 <= x - this->x && x - this->x <= 3) && (0 <= y - this->y && y - this->y <= 3) && handlemino(x - this->x, y - this->y) != ' ')
		return handlemino(x - this->x, y - this->y);
	return GetValue(y, x);
}

Tetrimino FieldControl::GetHold()
{
	return holdmino;
}

Tetrimino FieldControl::CheckNext(int idx)
{
	if (!(0 <= idx && idx <= 3)) return Tetrimino(NONE);
	return next_mino[idx];
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
