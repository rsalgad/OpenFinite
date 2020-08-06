#include "Rectangular_section.h"

Rectangular_section::Rectangular_section()
{
}

Rectangular_section::Rectangular_section(double height, double width)
{
	this->height = height;
	this->width = width;
}

double Rectangular_section::Area()
{
	return this->width * this->height;
}

double Rectangular_section::InertiaY()
{
	return this->width* pow(this->height, 3) / 12;
}

double Rectangular_section::InertiaZ()
{
	return this->height * pow(this->width, 3) / 12;
}

double Rectangular_section::J()
{
	return this->width * this->height * (pow(this->width, 2) + pow(this->height, 2)) / 12;
}

std::string Rectangular_section::Type()
{
	return "rectangular";
}

std::string Rectangular_section::To_string()
{
	std::string str = "(";
	str += "Type = " + this->Type() + ", Height = " + std::to_string(this->height) + ", Width = " + std::to_string(this->width) + ")";
	return str;
}
