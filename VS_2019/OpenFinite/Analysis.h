#ifndef ANALYSIS_H
#define ANALYSIS_H
#include "Structure_domain.h"

class Analysis
{
public:
	Analysis();
	Analysis(Structure_domain* structure);
	void Solve_elastic_system();

private:
	Matrix Assemble_global_matrix();
	Matrix Assemble_reduced_global_matrix(Matrix* global_matrix);
	Matrix Assemble_global_force_matrix();
	Matrix Assemble_reduced_global_force_matrix(Matrix* global_force_matrix);
	Structure_domain* structure;
};
#endif // !ANALYSIS_H

//make a list of dofs with boundaries
//make a list of dofs of the global matrix of each element
//when summing all elements to make the complete reduced matrix, ginore the ones that match the excluded ones.
