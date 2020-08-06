#include "Boundary_domain.h"
#include <algorithm>

Boundary_domain::Boundary_domain()
{
}

void Boundary_domain::Add_boundary(Boundary* boundary)
{
	this->boundary_list.emplace_back(boundary);
}

Boundary* Boundary_domain::Get_boundary(int id)
{
	return this->boundary_list[id - 1];
}

std::string Boundary_domain::List_boundaries()
{
	std::string str = "";

	for (int i = 0; i < this->boundary_list.size(); i++) {
		str += std::to_string(i) + ", ";
		str += this->boundary_list[i]->Type() + ", ";
		str += this->boundary_list[i]->To_string() + "\n";
	}
	return str;
}

std::vector<int> Boundary_domain::Get_loaded_dofs_by_type(std::string type, std::vector<double>* vals)
{
	std::vector<int> dofs;
	int nDof = 6;

	for (int i = 0; i < this->boundary_list.size(); i++) {
		Boundary* b = this->boundary_list[i];
		if (b->Type() == type) {
			
			for (int j = 0; j < b->Get_dofs()->size(); j++) {
				dofs.emplace_back((b->Get_node_id() - 1) * nDof +  b->Get_dofs()->at(j) - 1);
				
				if (vals != nullptr) {
					vals->emplace_back(b->Get_values()->at(j));
				}
			}
		}
	}

	return dofs;
}

std::vector<int> Boundary_domain::Restricted_dofs()
{
	std::vector<int> rest_dofs;
	int nDof = 6;

	for (int i = 0; i < this->boundary_list.size(); i++) {
		
		if (this->boundary_list[i]->Type() == "displacement") {
			Boundary* b = this->boundary_list[i];

			for (int j = 0; j < b->Get_values()->size(); j++) {
				if (b->Get_values()->at(j) == 0) {
					rest_dofs.emplace_back((b->Get_node_id() - 1) * nDof + b->Get_dofs()->at(j) - 1);
				}
			}
		}
	}
	std::sort(rest_dofs.begin(), rest_dofs.end());
	return rest_dofs;
}
