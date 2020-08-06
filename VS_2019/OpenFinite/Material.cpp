#include "Material.h"

Material::Material()
{
}

void Material::Set_elastic_properties(double stiff, double shear_stiff, double poisson)
{
	this->elastic_stiffness = stiff;
	this->shear_stiff = shear_stiff;
	this->poisson = poisson;
	this->hasElastic = true;
}

std::string Material::To_string()
{
	std::string str = "(";
	if (hasElastic) {
		str += "Elastic Properties: Stiffness = " + std::to_string(this->elastic_stiffness) + ", Poisson = " + std::to_string(this->poisson);
	}
	str += ")";
	return str;
}

double Material::Elastic_stiffness()
{
	return this->elastic_stiffness;
}

double Material::Poisson()
{
	return this->poisson;
}

double Material::Shear_stiffness()
{
	return this->shear_stiff;
}
