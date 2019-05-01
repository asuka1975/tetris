#include<cstring>
#include"Matrix4.h"

static char __;

Matrix4::Matrix4() : matrix(new char[16]){  }

Matrix4::Matrix4(const char* line1, const char* line2, const char* line3, const char* line4) : matrix(new char[16]) {
	std::memcpy(&matrix[0],  line1, sizeof(char) * 4);
	std::memcpy(&matrix[4],  line2, sizeof(char) * 4);
	std::memcpy(&matrix[8],  line3, sizeof(char) * 4);
	std::memcpy(&matrix[12], line4, sizeof(char) * 4);
}

Matrix4::Matrix4(const Matrix4& obj) : matrix(new char[16]) {
	std::memcpy(matrix, obj.matrix, sizeof(char) * 16);
}

Matrix4::~Matrix4() {
	if (!matrix) return;
	delete[] matrix;
	matrix = nullptr;
}

char Matrix4::operator()(unsigned int x, unsigned int y) const {
	if (!(0 <= x <= 3) || !(0 <= y <= 3)) return '\0';
	return matrix[x + y * 4];
}

Matrix4& Matrix4::operator=(const Matrix4 & obj)
{
	std::memcpy(matrix, obj.matrix, sizeof(char) * 16);
	return *this;
}

Matrix4 Matrix4::Rot90() {
	Matrix4 obj;
	obj(0, 0) = (*this)(0, 3); obj(1, 0) = (*this)(0, 2); obj(2, 0) = (*this)(0, 1); obj(3, 0) = (*this)(0, 0);
	obj(0, 1) = (*this)(1, 3); obj(1, 1) = (*this)(1, 2); obj(2, 1) = (*this)(1, 1); obj(3, 1) = (*this)(1, 0);
	obj(0, 2) = (*this)(2, 3); obj(1, 2) = (*this)(2, 2); obj(2, 2) = (*this)(2, 1); obj(3, 2) = (*this)(2, 0);
	obj(0, 3) = (*this)(3, 3); obj(1, 3) = (*this)(3, 2); obj(2, 3) = (*this)(3, 1); obj(3, 3) = (*this)(3, 0);
	//rotation
	return obj;
}

char& Matrix4::operator()(unsigned int x, unsigned int y)
{
	if (!(0 <= x <= 3) || !(0 <= y <= 3)) return __;
	return matrix[x + y * 4];
}
