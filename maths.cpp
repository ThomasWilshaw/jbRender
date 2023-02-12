#include <iostream>

#include "maths.h"




Matrix::Matrix()
{
    data_ = std::vector<std::vector<double>>(4, std::vector<double>(4, 0));
}

void Matrix::SetIdentity()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			data_[i][j] = 0.0;
		}
	}
	
	data_[0][0] = 1.0;
	data_[1][1] = 1.0;
	data_[2][2] = 1.0;
	data_[3][3] = 1.0;
}

void Matrix::SetData(std::vector< std::vector<double> >data)
{
	data_ = data;
}

std::vector< std::vector<double> > Matrix::data()
{
	return data_;
}

void Matrix::SetPerspective(double alpha, double zn, double zf)
{
	SetIdentity();

	double half_alpha = alpha * 0.5;
	double s = sin(deg_to_rad(half_alpha));
	double c = cos(deg_to_rad(half_alpha));
	double Q = s / (1.0 - (zn / zf));

	data_[0][0] = c;
	data_[1][1] = c;
	data_[2][2] = Q;
	data_[2][3] = s;
	data_[3][2] = -Q * zn;
}

void Matrix::SetTranslate(double x, double y, double z)
{
	SetIdentity();
	data_[3][0] = x;
	data_[3][1] = y;
	data_[3][2] = z;
}

void Matrix::SetScale(double x, double y, double z)
{
	SetIdentity();
	data_[0][0] = x;
	data_[1][1] = y;
	data_[2][2] = z;
}

void Matrix::SetRotation(double theta, axis j)
{
	SetIdentity();

	double theta_rad = deg_to_rad(theta);
	double s = sin(theta_rad);
	double c = cos(theta_rad);

	switch (j) {
		case axis::kAxisX:
			data_[1][1] = c;
			data_[1][2] = -s;
			data_[2][1] = s;
			data_[2][2] = c;
			break;
		case axis::kAxisY:
			data_[0][0] = c;
			data_[0][2] = s;
			data_[2][0] = -s;
			data_[2][2] = c;
			break;
		case axis::kAxisZ:
			data_[0][0] = c;
			data_[0][1] = -s;
			data_[1][0] = s;
			data_[1][1] = c;
			break;
		default:
			std::cout << "ERROR: Invalid axis input" << std::endl;
			break;
	}
}

void Matrix::Multiply(Matrix T)
{
	std::vector<std::vector<double>> temp_data = std::vector<std::vector<double>>(4, std::vector<double>(4, 0));
	
	temp_data[0][0] = data_[0][0] * T.data()[0][0] + data_[1][0] * T.data()[0][1] + data_[2][0] * T.data()[0][2] + data_[3][0] * T.data()[0][3];
	temp_data[0][1] = data_[0][1] * T.data()[0][0] + data_[1][1] * T.data()[0][1] + data_[2][1] * T.data()[0][2] + data_[3][1] * T.data()[0][3];
	temp_data[0][2] = data_[0][2] * T.data()[0][0] + data_[1][2] * T.data()[0][1] + data_[2][2] * T.data()[0][2] + data_[3][2] * T.data()[0][3];
	temp_data[0][3] = data_[0][3] * T.data()[0][0] + data_[1][3] * T.data()[0][1] + data_[2][3] * T.data()[0][2] + data_[3][3] * T.data()[0][3];

	temp_data[1][0] = data_[0][0] * T.data()[1][0] + data_[1][0] * T.data()[1][1] + data_[2][0] * T.data()[1][2] + data_[3][0] * T.data()[1][3];
	temp_data[1][1] = data_[0][1] * T.data()[1][0] + data_[1][1] * T.data()[1][1] + data_[2][1] * T.data()[1][2] + data_[3][1] * T.data()[1][3];
	temp_data[1][2] = data_[0][2] * T.data()[1][0] + data_[1][2] * T.data()[1][1] + data_[2][2] * T.data()[1][2] + data_[3][2] * T.data()[1][3];
	temp_data[1][3] = data_[0][3] * T.data()[1][0] + data_[1][3] * T.data()[1][1] + data_[2][3] * T.data()[1][2] + data_[3][3] * T.data()[1][3];

	temp_data[2][0] = data_[0][0] * T.data()[2][0] + data_[1][0] * T.data()[2][1] + data_[2][0] * T.data()[2][2] + data_[3][0] * T.data()[2][3];
	temp_data[2][1] = data_[0][1] * T.data()[2][0] + data_[1][1] * T.data()[2][1] + data_[2][1] * T.data()[2][2] + data_[3][1] * T.data()[2][3];
	temp_data[2][2] = data_[0][2] * T.data()[2][0] + data_[1][2] * T.data()[2][1] + data_[2][2] * T.data()[2][2] + data_[3][2] * T.data()[2][3];
	temp_data[2][3] = data_[0][3] * T.data()[2][0] + data_[1][3] * T.data()[2][1] + data_[2][3] * T.data()[2][2] + data_[3][3] * T.data()[2][3];

	temp_data[3][0] = data_[0][0] * T.data()[3][0] + data_[1][0] * T.data()[3][1] + data_[2][0] * T.data()[3][2] + data_[3][0] * T.data()[3][3];
	temp_data[3][1] = data_[0][1] * T.data()[3][0] + data_[1][1] * T.data()[3][1] + data_[2][1] * T.data()[3][2] + data_[3][1] * T.data()[3][3];
	temp_data[3][2] = data_[0][2] * T.data()[3][0] + data_[1][2] * T.data()[3][1] + data_[2][2] * T.data()[3][2] + data_[3][2] * T.data()[3][3];
	temp_data[3][3] = data_[0][3] * T.data()[3][0] + data_[1][3] * T.data()[3][1] + data_[2][3] * T.data()[3][2] + data_[3][3] * T.data()[3][3];

	data_ = temp_data;
}

void Matrix::PrintMatrix() const
{
	for (int i = 0; i < 4; i++) {
		std::cout << "|";
		std::cout << data_[i][0] << ", ";
		std::cout << data_[i][1] << ", ";
		std::cout << data_[i][2] << ", ";
		std::cout << data_[i][3];
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}