#ifndef ELEMENT_H
#define ELEMENT_H
#include <vector>
#include "Node.h"
#include "Matrix.h"

class Element
{
public:
	Element();
	void Set_node(int node_id);
	int Get_node_number(int element_node_index);
	virtual Matrix Global_stiffness() = 0;
	virtual std::vector<int> Global_stiffness_dofs() = 0;
	virtual std::string To_string() = 0;
	virtual std::string Type() = 0;

protected:
	std::vector<int> node_ids;
};
#endif // !ELEMENT_H

