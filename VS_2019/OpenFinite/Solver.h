#ifndef SOLVER_H
#define SOLVER_H
#include "Structure_domain.h"

class Solver
{
public:
	Solver();
	
	static Matrix Solve_system_cholesky(Matrix* m, Matrix* f);

private:
	Structure_domain* structure;
};
#endif // !SOLVER_H


