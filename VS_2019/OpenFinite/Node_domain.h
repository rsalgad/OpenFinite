#ifndef NODE_DOMAIN_H
#define NODE_DOMAIN_H
#include "Node.h"
#include <vector>

class Node_domain
{
public:
	Node_domain();
	void Add_node(Node* node);
	Node* Get_node(int id);
	int Total_nodes();
	std::string List_nodes();
	
private:
	std::vector<Node*> node_list;
};
#endif // !NODE_DOMAIN_H

