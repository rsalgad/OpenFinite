#include "Beam_column_element.h"
#include "Element.h"
#include "Rectangular_section.h"
#include "Node_domain.h"
#include <math.h>

Beam_column_element::Beam_column_element()
{
}

Beam_column_element::Beam_column_element(Material* material, Section* section, Node_domain* node_domain)
{
	this->material = material;
	this->section = section;
	this->node_domain = node_domain;
}

Matrix Beam_column_element::Global_stiffness()
{
	Matrix transf = this->Transformation();
	Matrix local_stiff = this->Local_stiffness();

	return Matrix::Transpose(&transf) * local_stiff * transf;
}

std::string Beam_column_element::Type()
{
	return "beam_column";
}

double Beam_column_element::Element_length()
{
	std::vector<double> coords_1 = this->node_domain->Get_node(Get_node_number(0))->Coordinates();
	std::vector<double> coords_2 = this->node_domain->Get_node(Get_node_number(1))->Coordinates();

	int x_comp = coords_2[0] - coords_1[0];
	int y_comp = coords_2[1] - coords_1[1];
	int z_comp = coords_2[2] - coords_1[2];

	return sqrt(pow(x_comp, 2) + pow(y_comp, 2) + pow(z_comp, 2));
}

std::string Beam_column_element::To_string()
{
	return std::string();
}

std::vector<int> Beam_column_element::Global_stiffness_dofs()
{
	int dofs = 6;
	std::vector<int> stiff_dofs;
	for (int i = 0; i < this->node_ids.size(); i++) {
		for (int j = 0; j < 6; j++) {
			stiff_dofs.emplace_back(dofs * (this->node_ids[i] - 1) + j);
		}
	}
	return stiff_dofs;
}

Matrix Beam_column_element::Local_stiffness()
{
	Matrix stiff(12);
	if (this->section->Type() == "rectangular") {
		Rectangular_section* rec_section;
		rec_section = (Rectangular_section*)this->section;

		stiff.Set_Element(0, 0, rec_section->Area() * this->material->Elastic_stiffness() / this->Element_length());
		stiff.Set_Element(0, 6, -stiff.Get_Element(0, 0));
		stiff.Set_Element(1, 1, 12 * this->material->Elastic_stiffness() * rec_section->InertiaZ() / pow(this->Element_length(), 3));
		stiff.Set_Element(1, 5, 6 * this->material->Elastic_stiffness() * rec_section->InertiaZ() / pow(this->Element_length(), 2));
		stiff.Set_Element(1, 7, -stiff.Get_Element(1, 1));
		stiff.Set_Element(1, 11, stiff.Get_Element(1, 5));
		stiff.Set_Element(2, 2, 12 * this->material->Elastic_stiffness() * rec_section->InertiaY() / pow(this->Element_length(), 3));
		stiff.Set_Element(2, 4, -6 * this->material->Elastic_stiffness() * rec_section->InertiaY() / pow(this->Element_length(), 2));
		stiff.Set_Element(2, 8, -stiff.Get_Element(2, 2));
		stiff.Set_Element(2, 10, stiff.Get_Element(2, 4));
		stiff.Set_Element(3, 3, this->material->Shear_stiffness() * rec_section->J() / this->Element_length());
		stiff.Set_Element(3, 9, -stiff.Get_Element(3, 3));
		stiff.Set_Element(4, 2, -6 * this->material->Elastic_stiffness() * rec_section->InertiaY() / pow(this->Element_length(), 2));
		stiff.Set_Element(4, 4, 4 * this->material->Elastic_stiffness() * rec_section->InertiaY() / this->Element_length());
		stiff.Set_Element(4, 8, -stiff.Get_Element(4, 2));
		stiff.Set_Element(4, 10, stiff.Get_Element(4, 4) / 2);
		stiff.Set_Element(5, 1, 6 * this->material->Elastic_stiffness() * rec_section->InertiaZ() / pow(this->Element_length(), 2));
		stiff.Set_Element(5, 5, 4 * this->material->Elastic_stiffness() * rec_section->InertiaZ() / this->Element_length());
		stiff.Set_Element(5, 7, -stiff.Get_Element(5, 1));
		stiff.Set_Element(5, 11, stiff.Get_Element(5, 5) / 2);

		stiff.Set_Element(6, 0, -stiff.Get_Element(0, 0));
		stiff.Set_Element(6, 6, stiff.Get_Element(0, 0));
		stiff.Set_Element(7, 1, -stiff.Get_Element(1, 1));
		stiff.Set_Element(7, 5, -stiff.Get_Element(1, 5));
		stiff.Set_Element(7, 7, -stiff.Get_Element(1, 7));
		stiff.Set_Element(7, 11, -stiff.Get_Element(1, 11));
		stiff.Set_Element(8, 2, -stiff.Get_Element(2, 2));
		stiff.Set_Element(8, 4, -stiff.Get_Element(2, 4));
		stiff.Set_Element(8, 8, -stiff.Get_Element(2, 8));
		stiff.Set_Element(8, 10, -stiff.Get_Element(2, 10));
		stiff.Set_Element(9, 3, -stiff.Get_Element(3, 3));
		stiff.Set_Element(9, 9, -stiff.Get_Element(3, 9));
		stiff.Set_Element(10, 2, stiff.Get_Element(4, 2));
		stiff.Set_Element(10, 4, stiff.Get_Element(4, 4) / 2);
		stiff.Set_Element(10, 8, stiff.Get_Element(4, 8));
		stiff.Set_Element(10, 10, stiff.Get_Element(4, 10) / 2);
		stiff.Set_Element(11, 1, stiff.Get_Element(5, 1));
		stiff.Set_Element(11, 5, stiff.Get_Element(5, 5) / 2);
		stiff.Set_Element(11, 7, stiff.Get_Element(5, 7));
		stiff.Set_Element(11, 11, 2*stiff.Get_Element(5, 11));
			   		 	  
	}
	return stiff;
}

double Beam_column_element::Get_cosine_term(int axis_index)
{
	std::vector<double> coords_1 = this->node_domain->Get_node(Get_node_number(0))->Coordinates();
	std::vector<double> coords_2 = this->node_domain->Get_node(Get_node_number(1))->Coordinates();

	switch (axis_index)
	{
	case 1:
		return (coords_2[0] - coords_1[0]) / this->Element_length();
		break;
	case 2:
		return (coords_2[1] - coords_1[1]) / this->Element_length();
		break;
	case 3:
		return (coords_2[2] - coords_1[2]) / this->Element_length();
		break;
	default:
		return 0.0;
		break;
	}
}

Matrix Beam_column_element::Transformation()
{
	Matrix transf(12);
	double l = this->Get_cosine_term(1);
	double m = this->Get_cosine_term(2);
	double n = this->Get_cosine_term(3);
	double D = sqrt(pow(l, 2) + pow(m, 2));

	for (int i = 0; i < 10; i += 3) {
		transf.Set_Element(i, i, l);
		transf.Set_Element(i, i + 1, m);
		transf.Set_Element(i, i + 2, n);
		transf.Set_Element(i + 1, i, -m / D);
		transf.Set_Element(i + 1, i + 1, l / D);
		transf.Set_Element(i + 1, i + 2, 0);
		transf.Set_Element(i + 2, i, -l * n / D);
		transf.Set_Element(i + 2, i + 1, -m * n / D);
		transf.Set_Element(i + 2, i + 2, D);
	}

	return transf;
}
