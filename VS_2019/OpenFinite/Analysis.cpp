#include "Analysis.h"
#include "Solver.h"

Analysis::Analysis()
{

}

Analysis::Analysis(Structure_domain* structure)
{
	this->structure = structure;
}

void Analysis::Solve_elastic_system()
{
	Matrix global_matrix = Assemble_global_matrix();
	Matrix reduced_global_matrix = Assemble_reduced_global_matrix(&global_matrix);
	Matrix global_force_matrix = Assemble_global_force_matrix();
	Matrix reduced_global_force_matrix = Assemble_reduced_global_force_matrix(&global_force_matrix);
	Matrix reduced_displacement = Solver::Solve_system_cholesky(&reduced_global_matrix, &reduced_global_force_matrix);
	int num = 2;
}

Matrix Analysis::Assemble_global_matrix()
{
	int dofs = 6;
	Matrix global_matrix(this->structure->Nodes()->Total_nodes() * dofs);
	for (int i = 0; i < this->structure->Elements()->Total_elements(); i++) {
		Matrix m = this->structure->Elements()->Get_element(i + 1)->Global_stiffness();
		global_matrix += m;
	}

	return global_matrix;
}

Matrix Analysis::Assemble_reduced_global_matrix(Matrix* global_matrix)
{
	Matrix reduced_matrix = *global_matrix;
	std::vector<int> dofs = this->structure->Boundaries()->Restricted_dofs();
	for (int i = 0; i < dofs.size(); i++) {
		int rest_dof = dofs[i];
		int delete_index;

		reduced_matrix.Remove_Row(rest_dof - i);
		reduced_matrix.Remove_Column(rest_dof - i);
	}
	
	return reduced_matrix;
}

Matrix Analysis::Assemble_global_force_matrix()
{
	int dofs = 6;
	Matrix global_force_matrix(this->structure->Nodes()->Total_nodes() * dofs, 1);
	std::vector<double> force_values;
	std::vector<int> force_dofs = this->structure->Boundaries()->Get_loaded_dofs_by_type("force", &force_values);

	for (int i = 0; i < force_dofs.size(); i++) {
		global_force_matrix.Set_Element(force_dofs[i], 0, force_values[i]);
	}

	return global_force_matrix;
}

Matrix Analysis::Assemble_reduced_global_force_matrix(Matrix* global_force_matrix)
{
	Matrix reduced_matrix = *global_force_matrix;
	std::vector<int> dofs = this->structure->Boundaries()->Restricted_dofs();
	for (int i = 0; i < dofs.size(); i++) {
		int rest_dof = dofs[i];
		int delete_index;

		reduced_matrix.Remove_Row(rest_dof - i);
	}

	return reduced_matrix;
}
