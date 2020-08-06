#include <iostream>
#include "Matrix.h"
#include "Structure_domain.h"
#include "Analysis.h"
#include <ctime>

int main() {
	Node n1(0, 0, 0);
	Node n2(100, 0, 0);
	Node_domain n;
	n.Add_node(&n1);
	n.Add_node(&n2);
	Material m;
	m.Set_elastic_properties(1000, 20, 0.1);
	Material_domain md;
	md.Add_material(&m);
	Rectangular_section sec(20, 10);
	Section_domain sd;
	sd.Add_section(&sec);
	Beam_column_element ele(&m, &sec, &n);
	ele.Set_node(1);
	ele.Set_node(2);
	Element_domain ed;
	ed.Add_element(&ele);
	Displacement_boundary b1;
	b1.Set_node(1);
	b1.Set_value(1, 0);
	b1.Set_value(2, 0);
	b1.Set_value(3, 0);
	b1.Set_value(4, 0);
	b1.Set_value(5, 0);
	b1.Set_value(6, 0);
	Force_boundary b2;
	b2.Set_node(2);
	b2.Set_value(1, 10);
	Boundary_domain bd;
	bd.Add_boundary(&b1);
	bd.Add_boundary(&b2);
	Structure_domain structure(n, ed, md, sd, bd);
	Analysis analysis(&structure);
	analysis.Solve_elastic_system();

	return 0;
}