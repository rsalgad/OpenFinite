#include "Node.h"

Node::Node()
{
}

Node::Node(double x, double y, double z)
{
	this->coords.emplace_back(x);
	this->coords.emplace_back(y);
	this->coords.emplace_back(z);
}

std::vector<double> Node::Coordinates()
{
	return this->coords;
}

std::string Node::To_string() const
{
	std::string s = "(" + std::to_string(this->coords[0]) + "," + std::to_string(this->coords[1]) + "," + std::to_string(this->coords[2]) +")";

	return s;
}
