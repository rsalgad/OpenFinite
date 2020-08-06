#include "Element.h"

Element::Element()
{
}

void Element::Set_node(int node_id)
{
	this->node_ids.emplace_back(node_id);
}

int Element::Get_node_number(int element_node_index)
{
	return this->node_ids[element_node_index];
}

std::string Element::To_string()
{
	std::string str = "(Type = " + this->Type() + ", Nodes = ";
	for (int i = 0; i < this->node_ids.size(); i++) {
		str += std::to_string(this->node_ids[i]);
		if (i < this->node_ids.size() - 1) {
			str += ",";
		}
		else {
			str += ")";
		}
	}

	return str;
}

