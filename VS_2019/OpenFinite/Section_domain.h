#ifndef SECTION_DOMAIN_H
#define SECTION_DOMAIN_H
#include <vector>
#include <string>
#include "Section.h"
#include "Rectangular_section.h"

class Section_domain
{
public:
	Section_domain();
	void Add_section(Section* section);
	std::string List_sections();

private:
	std::vector<Section*> section_list;
};

#endif // !SECTION_DOMAIN_H

