#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <string>


class Matrix
{
public:
	Matrix();
	Matrix(int size_X, int size_Y);
	Matrix(int size);
	void Set_Element(int row_index, int col_index, double val);
	void Remove_Element(int index);
	void Remove_Row(int row_index);
	void Remove_Column(int col_index);
	double Get_Element(int row_index, int col_index);
	double Get_Col_Element_Between_Row_Indexes(int col_index, int initRowIndex, int endRowIndex);
	void Organize_By_Row();
	void Organize_By_Column();
	Matrix operator+(const Matrix &m2);
	Matrix operator-(const Matrix &m2);
	Matrix operator*(Matrix &m2);
	void operator+=(Matrix& m2);
	void Transpose();
	bool Search_For_Index(int row_index, int col_index, int &index);
	bool Search_For_Row_Index(int row_index, int& index, bool last = false);
	bool Search_For_Column_Index(int col_index, int& index, bool last = false);
	int Size_x();
	int Size_y();

	static Matrix Identity(int dimension);
	static Matrix Transpose(Matrix* m);
	std::string To_String();

	~Matrix();

private:
	int size_X, size_Y;
	std::vector<int> row_index;
	std::vector<int> col_index;
	std::vector<double> values;
};

#endif // !MATRIX_H

