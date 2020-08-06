#ifndef BOUNDARY_H
#define BOUNDARY_H
#include <vector>
#include <string>

class Boundary
{
public:
	Boundary();
	virtual void Set_node(int id);
	virtual void Set_value(int dof, double load_value);
	virtual std::vector<double>* Get_values();
	virtual std::vector<int>* Get_dofs();
	virtual int Get_node_id();
	virtual std::string To_string();
	virtual std::string Type() = 0;

private:
	int node_id;
	std::vector<int> dofs;
	std::vector<double> values;

};
#endif // !BOUNDARY_H

