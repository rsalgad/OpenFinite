#ifndef ELEMENT_DOMAIN_H
#define ELEMENT_DOMAIN_H
#include <vector>
#include <string>
#include "Element.h"
#include "Beam_column_element.h"

class Element_domain
{
public:
	Element_domain();
	void Add_element(Element* element);
	Element* Get_element(int id);
	int Total_elements();
	std::string List_elements();

private:
	std::vector<Element*> element_list;
};
#endif // !ELEMENT_DOMAIN_H

