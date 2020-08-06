#ifndef BEAM_COLUMN_ELEMENT_H
#define BEAM_COLUMN_ELEMENT_H

#include "Element.h"
#include "Material.h"
#include "Section.h"
#include "Node_domain.h"
class Beam_column_element : public Element
{
public:
	Beam_column_element();
	Beam_column_element(Material* material, Section* section, Node_domain* node_domain);
	Matrix Global_stiffness();
	std::string Type();
	double Element_length();
	std::string To_string();
	std::vector<int> Global_stiffness_dofs();

private:
	Matrix Local_stiffness();
	double Get_cosine_term(int axis_index);
	Matrix Transformation();
	Material* material;
	Section* section;
	Node_domain* node_domain;
};

#endif // !BEAM_COLUMN_ELEMENT_H

