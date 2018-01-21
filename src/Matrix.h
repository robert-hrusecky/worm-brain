/*
 * Matrix.h
 *
 *  Created on: Jul 28, 2017
 *      Author: robert
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

namespace EvolutionSimulator
{

class Matrix
{
public:
	Matrix(int rows, int cols) :
			ROWS(rows), COLS(cols), m_mat(rows * cols)
	{
	}
	double* operator[](int row)
	{
		return &m_mat[COLS * row];
	}
	const int ROWS;
	const int COLS;
private:
	std::vector<double> m_mat;
};

} /* namespace EvolutionSimulator */

#endif /* MATRIX_H_ */
