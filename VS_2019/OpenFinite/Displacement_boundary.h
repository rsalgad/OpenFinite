#ifndef DISPLACEMENT_BOUNDARY_H
#define DISPLACEMENT_BOUNDARY_H
#include "Boundary.h"

class Displacement_boundary :
	public Boundary
{
public:
	Displacement_boundary();
	std::string Type();
};
#endif // !DISPLACEMENT_BOUNDARY_H

