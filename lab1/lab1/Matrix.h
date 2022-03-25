#pragma once
#include "libraries.h"

template<typename T>
class Matrix
{
public:
	T**** matrix;
	int lines;
	int columns;
	int includedLines;
	int includedColumns;

public:
	Matrix(int lines, int columns, int includedLines, int includedColumns);
	~Matrix();
	boolean equals(Matrix<T>* anotherMatrix);

	void printToConsole();
	void fillWithRandomNumbers();
};

#include "Matrix.inl"