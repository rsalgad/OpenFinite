#include "Structure_domain.h"

Structure_domain::Structure_domain()
{
	this->nodes = Node_domain();
	this->elements = Element_domain();
	this->materials = Material_domain();
	this->sections = Section_domain();
	this->boundaries = Boundary_domain();
}

Structure_domain::Structure_domain(Node_domain nodes, Element_domain elements, Material_domain materials, Section_domain sections, Boundary_domain boundaries)
{
	this->nodes = nodes;
	this->elements = elements;
	this->materials = materials;
	this->sections = sections;
	this->boundaries = boundaries;
}

Node_domain* Structure_domain::Nodes()
{
	return &this->nodes;
}

Element_domain* Structure_domain::Elements()
{
	return &this->elements;
}

Material_domain* Structure_domain::Materials()
{
	return &this->materials;
}

Section_domain* Structure_domain::Sections()
{
	return &this->sections;
}

Boundary_domain* Structure_domain::Boundaries()
{
	return &this->boundaries;
}
