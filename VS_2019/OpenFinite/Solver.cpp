#include "Solver.h"

Solver::Solver()
{
}

Matrix Solver::Solve_system_cholesky(Matrix* m, Matrix* f)
{
	//size of the stiff matrix
	int sizeX = m->Size_x(); 
	int sizeY = m->Size_y();

	// L matrix
	Matrix L(sizeX, sizeY);

	for (int i = 0; i < sizeX; i++)
	{
		double sum = 0;

		//calculates the diagonal term
		for (int k = 0; k < i; k++)
		{
			sum += pow(L.Get_Element(i, k), 2);
		}
		L.Set_Element(i, i, sqrt(abs(m->Get_Element(i, i) - sum)));

		for (int j = i + 1; j < sizeX; j++) {
			double sum = 0;

			for (int k = 0; k < i; k++)
			{
				sum += L.Get_Element(j , k) * L.Get_Element(i , k);
			}
			L.Set_Element(j, i, (1.0 / L.Get_Element(i, i)) * (m->Get_Element(j, i) - sum));
		}
	}

	Matrix LTransp = Matrix::Transpose(&L);

	//Forward Substitution

	int size = f->Size_x();
	Matrix forwardSub(size, 1);

	for (int i = 0; i < size; i++)
	{
		double sum = 0;

		for (int j = 0; j < i; j++)
		{

			sum += L.Get_Element(i , j) * forwardSub.Get_Element(j, 0);
		}
		forwardSub.Set_Element(i, 0, (f->Get_Element(i, 0) - sum) / L.Get_Element(i, i));
	}

	Matrix backSub(size, 1);

	for (int i = size - 1; i >= 0; i--)
	{
		double sum = 0;

		for (int j = size - 1; j > i; j--)
		{
			sum += LTransp.Get_Element(i , j) * backSub.Get_Element(j, 0);
		}
		backSub.Set_Element(i, 0, (forwardSub.Get_Element(i, 0) - sum) / LTransp.Get_Element(i, i));
	}

	return backSub;
}

