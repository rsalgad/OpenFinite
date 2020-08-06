#include "Section_domain.h"

Section_domain::Section_domain()
{
}

void Section_domain::Add_section(Section* section)
{
	this->section_list.emplace_back(section);
}

std::string Section_domain::List_sections()
{
	std::string str = "";
	for (int i = 0; i < this->section_list.size(); i++) {
		str += std::to_string(i + 1);
		str += this->section_list[i]->To_string() + "\n";
	}
	return str;
}
