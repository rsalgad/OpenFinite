#include "Material_domain.h"

Material_domain::Material_domain()
{
}

void Material_domain::Add_material(Material* material)
{
	this->material_list.emplace_back(material);
}

std::string Material_domain::List_materials()
{
	std::string str = "";
	for (int i = 0; i < this->material_list.size(); i++) {
		str += std::to_string(i + 1) + ", ";
		str += this->material_list[i]->To_string() + "\n";
	}
	return str;
}
