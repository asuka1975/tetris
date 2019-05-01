#pragma once

class Matrix4 {
public:
	Matrix4();
	Matrix4(const char* line1, const char* line2, const char* line3, const char* line4);
	Matrix4(const Matrix4& obj);
	~Matrix4();
	char operator()(unsigned int x, unsigned int y) const;
	char& operator()(unsigned int x, unsigned int y);
	Matrix4& operator=(const Matrix4& obj);
	Matrix4 Rot90();
private:
	char* matrix;
};