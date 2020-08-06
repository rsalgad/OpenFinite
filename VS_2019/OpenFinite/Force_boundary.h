#ifndef FORCE_BOUNDARY_H
#define FORCE_BOUNDARY_H
#include "Boundary.h"

class Force_boundary :
	public Boundary
{
public:
	Force_boundary();
	std::string Type();
};
#endif // !FORCE_BOUNDARY_H

