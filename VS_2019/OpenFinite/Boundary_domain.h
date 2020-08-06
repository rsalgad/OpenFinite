#ifndef BOUNDARY_DOMAIN_H
#define BOUNDARY_DOMAIN_H
#include <string>
#include "Boundary.h"
#include "Displacement_boundary.h"
#include "Force_boundary.h"

class Boundary_domain
{
public:
	Boundary_domain();
	void Add_boundary(Boundary* boundary);
	Boundary* Get_boundary(int id);
	std::string List_boundaries();
	std::vector<int> Get_loaded_dofs_by_type(std::string type, std::vector<double>* vals = nullptr);
	std::vector<int> Restricted_dofs();

private:
	std::vector<Boundary*> boundary_list;

};
#endif // !BOUNDARY_DOMAIN_H

