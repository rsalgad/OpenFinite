#ifndef MATERIAL_H
#define MATERIAL_H
#include <string>

class Material
{
public:
	Material();
	void Set_elastic_properties(double stiff, double shear_stiff, double poisson);
	std::string To_string();
	double Elastic_stiffness();
	double Poisson();
	double Shear_stiffness();

private:
	double elastic_stiffness, poisson, shear_stiff;
	bool hasElastic = false;
};
#endif // !MATERIAL_H

