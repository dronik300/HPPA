#ifndef NOT_VECTORIZED_INL
#define NOT_VECTORIZED_INL

#include "NotVectorized.h"

template<typename T>
Matrix<T>* NotVectorized<T>::multiplyMatrices(Matrix<T>& firstMatrix, Matrix<T>& secondMatrix) {
	Matrix<T>* resultMatrix = new Matrix<T>(firstMatrix.lines, secondMatrix.columns, firstMatrix.includedLines, secondMatrix.includedColumns);
	T** temp = new T * [firstMatrix.includedLines];

	for (auto m = 0; m < firstMatrix.lines; m++) {
		for (auto n = 0; n < secondMatrix.columns; n++) {
			for (auto l = 0; l < firstMatrix.columns; l++) {
				multiplySubmatrices(firstMatrix.matrix[m][l], firstMatrix.includedLines, firstMatrix.includedColumns,
					secondMatrix.matrix[l][n], secondMatrix.includedColumns, temp);
				sumSubmatrices(resultMatrix->matrix[m][n], temp, firstMatrix.includedLines, secondMatrix.includedColumns, resultMatrix->matrix[m][n]);
			}
		}
	}

	return resultMatrix;
}

template<typename T>
void NotVectorized<T>::multiplySubmatrices(T** firstMatrix, int firstMatrixLines, int firstMatrixColumns,
	T** secondMatrix, int secondMatrixColumns, T** resultMatrix) {

	for (auto i = 0; i < firstMatrixLines; i++) {
		resultMatrix[i] = new T[secondMatrixColumns]();
	}

	for (auto i = 0; i < firstMatrixLines; i++) {
		T* __restrict resultMatrixRow = resultMatrix[i];

		for (auto k = 0; k < firstMatrixColumns; k++) {
			const T* secondMatrixRow = secondMatrix[k];
			T thisElem = firstMatrix[i][k];

			#pragma loop(no_vector)
			for (auto j = 0; j < secondMatrixColumns; j++) {
				resultMatrixRow[j] += thisElem * secondMatrixRow[j];
			}
		}
	}
}

template<typename T>
void NotVectorized<T>::sumSubmatrices(T** firstMatrix, T** secondMatrix, int lines, int columns, T** resultMatrix) {
	for (int i = 0; i < lines; i++) {
		#pragma loop(no_vector)
		for (int j = 0; j < columns; j++) {
			resultMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
		}
	}
}

#endif