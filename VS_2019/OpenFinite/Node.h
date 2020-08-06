#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

class Node
{
public:
	Node();
	Node(double x, double y, double z);
	std::vector<double> Coordinates();
	std::string To_string() const;

private:
	std::vector<double> coords;
};
#endif // !NODE_H

