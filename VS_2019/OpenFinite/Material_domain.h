#ifndef MATERIAL_DOMAIN_H
#define MATERIAL_DOMAIN_H
#include "Material.h"
#include <string>
#include <vector>

class Material_domain
{
public:
	Material_domain();
	void Add_material(Material* material);
	std::string List_materials();

private:
	std::vector<Material*> material_list;
};

#endif // !MATERIAL_DOMAIN_H

