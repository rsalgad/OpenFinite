#ifndef STRUCTURE_DOMAIN_H
#define STRUCTURE_DOMAIN_H
#include "Node_domain.h"
#include "Element_domain.h"
#include "Material_domain.h"
#include "Section_domain.h"
#include "Boundary_domain.h"

class Structure_domain
{
public:
	Structure_domain();
	Structure_domain(Node_domain nodes, Element_domain elements, Material_domain materials, Section_domain sections, Boundary_domain boundaries);
	Node_domain* Nodes();
	Element_domain* Elements();
	Material_domain* Materials();
	Section_domain* Sections();
	Boundary_domain* Boundaries();

private:
	Node_domain nodes;
	Element_domain elements;
	Material_domain materials;
	Section_domain sections;
	Boundary_domain boundaries;

};
#endif // !STRUCTURE_DOMAIN_H

