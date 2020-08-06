#ifndef RECTANGULAR_SECTION_H
#define RECTANGULAR_SECTION_H
#include "Section.h"

class Rectangular_section : public Section
{
public:
	Rectangular_section();
	Rectangular_section(double height, double width);
	double Area();
	double InertiaY();
	double InertiaZ();
	double J();
	std::string Type();
	std::string To_string();

private:
	double height, width;
};
#endif // !RECTANGULAR_SECTION_H

