#pragma once
#include "Matrix.h"

template<typename T>
class SSE
{
private:
	void sumSubmatrices(T** firstMatrix, T** secondMatrix, int lines, int columns, T** resultMatrix);
	void multiplySubmatrices(T** firstMatrix, int firstMatrixLines, int firstMatrixColumns, T** secondMatrix, int secondMatrixColumns, T** resultMatrix);

public:
	Matrix<T>* multiplyMatrices(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix);
};

#include "SSE.inl"