#include "Boundary.h"

Boundary::Boundary()
{
}

void Boundary::Set_node(int id)
{
	this->node_id = id;
}

void Boundary::Set_value(int dof, double load_value)
{
	this->dofs.emplace_back(dof);
	this->values.emplace_back(load_value);
}

std::vector<double>* Boundary::Get_values()
{
	return &this->values;
}

std::vector<int>* Boundary::Get_dofs()
{
	return &this->dofs;
}

int Boundary::Get_node_id()
{
	return this->node_id;
}

std::string Boundary::To_string()
{
	std::string str = "(";
	for (int i = 0; i < this->dofs.size(); i++) {
		str += "Dir " + std::to_string(this->dofs[i]) + ": " + std::to_string(this->values[i]);
		if (i < this->dofs.size() - 1) {
			str += ", ";
		}
		else {
			str += ")";
		}
	}

	return str;
}
