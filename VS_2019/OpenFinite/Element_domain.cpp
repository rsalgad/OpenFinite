#include "Element_domain.h"

Element_domain::Element_domain()
{
}

void Element_domain::Add_element(Element* element)
{
	this->element_list.emplace_back(element);
}

Element* Element_domain::Get_element(int id)
{
	return this->element_list[id - 1];
}

int Element_domain::Total_elements()
{
	return this->element_list.size();
}

std::string Element_domain::List_elements()
{
	std::string str = "";
	for (int i = 0; i < this->element_list.size(); i++) {
		str += std::to_string(i) + ", ";
		str += this->element_list[i]->To_string() + "\n";
	}
	return str;
}
