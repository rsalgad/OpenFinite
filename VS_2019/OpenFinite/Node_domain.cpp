#include "Node_domain.h"

Node_domain::Node_domain()
{

}

void Node_domain::Add_node(Node* node)
{
	this->node_list.emplace_back(node);
}

Node* Node_domain::Get_node(int id)
{
	return this->node_list[id - 1];
}

int Node_domain::Total_nodes()
{
	return this->node_list.size();
}

std::string Node_domain::List_nodes()
{
	std::string str = "";
	for (int i = 0; i < this->node_list.size(); i++) {
		str += std::to_string(i) + ", ";
		str += this->node_list[i]->To_string() + "\n";
	}
	return str;
}