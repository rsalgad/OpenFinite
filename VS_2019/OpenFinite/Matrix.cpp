#include "Matrix.h"
#include <iostream>

Matrix::Matrix()
{
}

Matrix::Matrix(int size_X, int size_Y)
{
	this->size_X = size_X;
	this->size_Y = size_Y;
}

Matrix::Matrix(int size)
{
	this->size_X = size;
	this->size_Y = size;
}

//0 based indexes
void Matrix::Set_Element(int row_index, int col_index, double val)
{
	this->row_index.emplace_back(row_index);
	this->col_index.emplace_back(col_index);
	this->values.emplace_back(val);
}

void Matrix::Remove_Element(int index)
{
	this->row_index.erase(this->row_index.begin() + index);
	this->col_index.erase(this->col_index.begin() + index);
	this->values.erase(this->values.begin() + index);
}

void Matrix::Remove_Row(int row_index)
{
	std::vector<int>::iterator itRow = std::find(this->row_index.begin(), this->row_index.end(), row_index);
	while (itRow != this->row_index.end())
	{
		int index = itRow - this->row_index.begin();
		this->row_index.erase(itRow);
		this->col_index.erase(this->col_index.begin() + index);
		this->values.erase(this->values.begin() + index);
		itRow = std::find(this->row_index.begin(), this->row_index.end(), row_index);
	}
	this->size_X--;
	for (int i = 0; i < this->row_index.size(); i++) {
		if (this->row_index[i] > row_index) {
			this->row_index[i]--;
		}
	}
}

void Matrix::Remove_Column(int col_index)
{
	std::vector<int>::iterator itCol = std::find(this->col_index.begin(), this->col_index.end(), col_index);
	while (itCol != this->col_index.end())
	{
		int index = itCol - this->col_index.begin();
		this->row_index.erase(this->row_index.begin() + index);
		this->col_index.erase(itCol);
		this->values.erase(this->values.begin() + index);
		itCol = std::find(this->col_index.begin(), this->col_index.end(), col_index);
	}
	this->size_Y--;
	for (int i = 0; i < this->col_index.size(); i++) {
		if (this->col_index[i] > col_index) {
			this->col_index[i]--;
		}
	}
}

double Matrix::Get_Element(int row_index, int col_index)
{
	int index;
	if (this->Search_For_Index(row_index, col_index, index)) {
		return this->values[index];
	}
	else {
		return 0;
	}
}

double Matrix::Get_Col_Element_Between_Row_Indexes(int col_index, int initRowIndex, int endRowIndex)
{
	for (int i = initRowIndex; i < endRowIndex; i++) {
		if (this->col_index[i] == col_index) {
			return this->values[i];
		}
	}
	return 0; //if didn't find it.
}

void Matrix::Organize_By_Row()
{
	int index = 0;

	while (index < this->row_index.size() - 1) {
		int min = this->row_index[index];
		for (int i = index + 1; i < this->row_index.size(); i++) {
			if (this->row_index[i] < min) {
				min = this->row_index[i];
				std::iter_swap(this->row_index.begin() + index, this->row_index.begin() + i);
				std::iter_swap(this->col_index.begin() + index, this->col_index.begin() + i);
				std::iter_swap(this->values.begin() + index, this->values.begin() + i);
			}
		}
		index++;
	}
}



void Matrix::Organize_By_Column()
{
	int index = 0;

	while (index < this->col_index.size() - 1) {
		int min = this->col_index[index];
		for (int i = index + 1; i < this->col_index.size(); i++) {
			if (this->col_index[i] < min) {
				min = this->col_index[i];
				std::iter_swap(this->row_index.begin() + index, this->row_index.begin() + i);
				std::iter_swap(this->col_index.begin() + index, this->col_index.begin() + i);
				std::iter_swap(this->values.begin() + index, this->values.begin() + i);
			}
		}

		index++;

	}
}

Matrix Matrix::operator+(const Matrix &m2)
{
	if (this->size_X == m2.size_X && this->size_Y == m2.size_Y) {
		
		Matrix addedMatrix = m2;

		for (int i = 0; i < this->row_index.size(); i++)
		{
			std::vector<int>::iterator itRow = addedMatrix.row_index.begin();
			while (itRow != addedMatrix.row_index.end())
			{
				itRow = std::find(itRow, addedMatrix.row_index.end(), this->row_index[i]);
				if (itRow != addedMatrix.row_index.end()) {		
					if (addedMatrix.col_index[itRow - addedMatrix.row_index.begin()] == this->col_index[i]) {
						addedMatrix.values[itRow - addedMatrix.row_index.begin()] += this->values[i];						
						break;
					}
					itRow++;
				}
				else {
					break;
				}
			}
			addedMatrix.Set_Element(this->row_index[i], this->col_index[i], this->values[i]);
		}
		return addedMatrix;
	}
	else {
		std::cout << "Error adding matrices. Dimensions don't match." << std::endl;
		return Matrix();
	}
}

Matrix Matrix::operator-(const Matrix &m2)
{
	if (this->size_X == m2.size_X && this->size_Y == m2.size_Y) {

		Matrix addedMatrix = *this;

		for (int i = 0; i < m2.row_index.size(); i++)
		{
			std::vector<int>::iterator itRow = addedMatrix.row_index.begin();
			while (itRow != addedMatrix.row_index.end())
			{
				itRow = std::find(itRow, addedMatrix.row_index.end(), m2.row_index[i]);
				if (itRow != addedMatrix.row_index.end()) {
					if (addedMatrix.col_index[itRow - addedMatrix.row_index.begin()] == m2.col_index[i]) {
						addedMatrix.values[itRow - addedMatrix.row_index.begin()] -= m2.values[i];
						break;
					}
					itRow++;
				}
			}
			if (itRow == addedMatrix.row_index.end()) {
				addedMatrix.Set_Element(m2.row_index[i], m2.col_index[i], -m2.values[i]);
			}
		}
		return addedMatrix;
	}
	else {
		std::cout << "Error subtracting matrices. Dimensions don't match." << std::endl;
		return Matrix();
	}
}

Matrix Matrix::operator*(Matrix &m2)
{
	if (this->size_Y == m2.size_X) {
		std::vector<int> previous_rows;
		Matrix multMatrix(this->size_X, this->size_Y);

		for (int i = 0; i < this->row_index.size(); i++) { //for each item in the list of row indexes
			std::vector<int>::iterator prev_row_finder;
			prev_row_finder = std::find(previous_rows.begin(), previous_rows.end(), this->row_index[i]); //search if the row index has already been taking care of
			
			if (prev_row_finder == previous_rows.end()) { //did not find a match
				

				std::vector<int>::iterator itRow = this->row_index.begin();
				std::vector<int> indexes_of_this_row;
				while (itRow != this->row_index.end())
				{
					itRow = std::find(itRow, this->row_index.end(), this->row_index[i]); //find every instance of the row
						
					if (itRow != this->row_index.end()) {
						indexes_of_this_row.emplace_back(itRow - this->row_index.begin());
						itRow++;
					}
				}

				for (int j = 0; j < m2.size_Y; j++) { //this can be optmized not to go through all the columns even if they don't exist
					double prod = 0;
					int foundIndex;

					for (int k = 0; k < indexes_of_this_row.size(); k++) { 
						if (m2.Search_For_Index(this->col_index[indexes_of_this_row[k]], j, foundIndex)) { //if found an equivalent value in m2
							prod += this->values[indexes_of_this_row[k]] * m2.values[foundIndex];
						}
					}
					if (prod != 0) {
						multMatrix.Set_Element(this->row_index[i], j, prod);
					}
				}
				previous_rows.emplace_back(this->row_index[i]);
			}
		}
		return multMatrix;
	}
	else {
		std::cout << "Error multiplying matrices. Dimensions don't match." << std::endl;
		return Matrix();
	}
}

void Matrix::operator+=(Matrix& m2)
{

	if (this->size_X == m2.size_X && this->size_Y == m2.size_Y) {

		for (int i = 0; i < m2.row_index.size(); i++)
		{
			std::vector<int>::iterator itRow =this->row_index.begin();
			while (itRow != this->row_index.end())
			{
				itRow = std::find(itRow, this->row_index.end(), m2.row_index[i]);
				if (itRow != this->row_index.end()) {
					if (this->col_index[itRow - this->row_index.begin()] == m2.col_index[i]) {
						this->values[itRow -this->row_index.begin()] += m2.values[i];
						break;
					}
					itRow++;
				}
				else {
					break;
				}
			}
			this->Set_Element(m2.row_index[i], m2.col_index[i], m2.values[i]);
		}
	}
	else {
		std::cout << "Error adding matrices. Dimensions don't match." << std::endl;
	}
}

void Matrix::Transpose()
{
	std::vector<int> tempColIndexVec;

	tempColIndexVec = this->col_index;
	this->col_index = this->row_index;
	this->row_index = tempColIndexVec;
}

bool Matrix::Search_For_Index(int row_index, int col_index, int& index)
{
	std::vector<int>::iterator itRow = this->row_index.begin();
	while (itRow != this->row_index.end())
	{
		itRow = std::find(itRow, this->row_index.end(), row_index);
		if (itRow != this->row_index.end()) {
			if (this->col_index[itRow - this->row_index.begin()] == col_index) {
				index = itRow - this->row_index.begin();
				return true;
			}
			itRow++;
		}
	}
	return false;
}

//
bool Matrix::Search_For_Row_Index(int row_index, int& index, bool last)
{
	std::vector<int>::iterator itRow = this->row_index.begin();
	int lastIndex = -1, firstIndex = -1;
	while (itRow != this->row_index.end())
	{
		itRow = std::find(itRow, this->row_index.end(), row_index);
		if (itRow != this->row_index.end()) {
			if (!last) {
				firstIndex = itRow - this->row_index.begin();
				index = firstIndex;
				return true;
			}
			else {
				lastIndex = itRow - this->row_index.begin();
			}
		}
		else {
			if (lastIndex != -1) {
				index = lastIndex;
				return true;
			}
			else {
				index = 0;
				return false;
			}
		}
		itRow++;
	}
}

bool Matrix::Search_For_Column_Index(int col_index, int& index, bool last)
{
	std::vector<int>::iterator itCol = this->col_index.begin();
	int lastIndex = -1, firstIndex = -1;
	while (itCol != this->col_index.end())
	{
		itCol = std::find(itCol, this->col_index.end(), col_index);
		if (itCol != this->col_index.end()) {
			if (!last) {
				firstIndex = itCol - this->col_index.begin();
				index = firstIndex;
				return true;
			}
			else {
				lastIndex = itCol - this->col_index.begin();
			}
		}
		else {
			if (lastIndex != -1) {
				index = lastIndex;
				return true;
			}
			else {
				return false;
			}
		}
		itCol++;
	}
}

int Matrix::Size_x()
{
	return this->size_X;
}

int Matrix::Size_y()
{
	return this->size_Y;
}

Matrix Matrix::Identity(int dimension)
{
	Matrix I(dimension, dimension);
	for (int i = 0; i < dimension; i++) {
		I.Set_Element(i, i, 1);
	}
	return I;
}

Matrix Matrix::Transpose(Matrix* m)
{
	Matrix transp(m->size_Y, m->size_X);
	transp.row_index.reserve(m->row_index.size());
	transp.col_index.reserve(m->col_index.size());
	transp.values.reserve(m->values.size());

	for (int i = 0; i < m->row_index.size(); i++) {
		transp.row_index.emplace_back(m->col_index[i]);
		transp.col_index.emplace_back(m->row_index[i]);
		transp.values.emplace_back(m->values[i]);
	}

	return transp;
}

std::string Matrix::To_String()
{
	std::string s = "";

	for (int i = 0; i < this->row_index.size(); i++) {
		s += std::to_string(this->row_index[i]);
		if (i != this->row_index.size() - 1) {
			s += ",";
		}
		else {
			s += "\n";
		}
	}

	for (int i = 0; i < this->col_index.size(); i++) {
		s += std::to_string(this->col_index[i]);
		if (i != this->col_index.size() - 1) {
			s += ",";
		}
		else {
			s += "\n";
		}
	}

	for (int i = 0; i < this->values.size(); i++) {
		s += std::to_string(this->values[i]);
		if (i != this->values.size() - 1) {
			s += ",";
		}
		else {
			s += "\n";
		}
	}

	return s;
}

Matrix::~Matrix()
{
}
