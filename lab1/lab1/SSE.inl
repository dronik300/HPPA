#ifndef SSE_INL
#define SSE_INL

#include "SSE.h"

template<typename T>
Matrix<T>* SSE<T>::multiplyMatrices(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix) {
	Matrix<T>* resultMatrix = new Matrix<T>(firstMatrix.lines, secondMatrix.columns, firstMatrix.includedLines, secondMatrix.includedColumns);
	T** temp = new T * [firstMatrix.includedLines];

	for (auto m = 0; m < firstMatrix.lines; m++) {
		for (auto n = 0; n < secondMatrix.columns; n++) {
			for (auto l = 0; l < firstMatrix.columns; l++) {
				multiplySubmatrices(firstMatrix.matrix[m][l], firstMatrix.includedLines, firstMatrix.includedColumns,
					secondMatrix.matrix[l][n], secondMatrix.includedColumns, resultMatrix->matrix[m][n]);
			}
		}
	}

	return resultMatrix;
}

template<typename T>
void SSE<T>::multiplySubmatrices(T** firstMatrix, int firstMatrixLines, int firstMatrixColumns,
	T** secondMatrix, int secondMatrixColumns, T** resultMatrix) {
	for (auto i = 0; i < firstMatrixLines; i++) {
		for (auto k = 0; k < firstMatrixColumns; k++) {
			for (auto j = 0; j < secondMatrixColumns; j += 4) {
				_mm_store_ps((float*)resultMatrix[i] + j, _mm_add_ps(_mm_loadu_ps((const float*)resultMatrix[i] + j),
					_mm_mul_ps(_mm_set1_ps((const float)firstMatrix[i][k]), _mm_load_ps((const float*)secondMatrix[k] + j))));
			}
		}
	}
}

template<typename T>
void SSE<T>::sumSubmatrices(T** firstMatrix, T** secondMatrix, int lines, int columns, T** resultMatrix) {
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j += 4) {
			_mm_store_ps((float*)resultMatrix[i] + j, _mm_add_ps(_mm_load_ps((float*)firstMatrix[i] + j),
				_mm_load_ps((float*)secondMatrix[i] + j)));
		}
	}
}

#endif