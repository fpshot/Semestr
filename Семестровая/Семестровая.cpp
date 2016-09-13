// �����������.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

double* methodGaussa(int n, double **matrix);
void output(int n, double *matrix);
void input(int & n, double** & matrix);
bool CheckGaussMatrix(int n, double** & matrix);

int main()
{
	system("chcp 1251");
	system("cls");
	bool gauss = false, kramer = false;
	double **matrix, *x;
	int n;
	input(n, matrix);
	if (CheckGaussMatrix(n, matrix))
	{
		x = methodGaussa(n, matrix);
		output(n, x);
		delete[] x;
	}
	else { cout << "������ ������� �� ����� ���� ������ ������� ������!"; }
	delete[] matrix;
	cin.get(); cin.get();
    return 0;
}



void input(int & n, double** & matrix)
{
	bool notNumer = true;
	cout << "������� ���������� ���������: ";
	do
	{	
		try {	
			cin.exceptions(std::ios_base::failbit);
			cin >> n;
			if (n <= 0)
			{
				cout << "������� ����������� �����!: ";
				notNumer = true;
			}
			else { notNumer = false; }
		}
		catch (ios_base::failure e) {
			cout << "������� �����!: ";
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (notNumer);
	cout << "govno";
	matrix = new double*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[n + 1];
		for (int j = 0; j < n; j++) {
			cout << "a[" << i << "][" << j << "]= ";
			cin >> matrix[i][j];
		}
		cout << "y[" << i << "]= ";
		cin >> matrix[i][n + 1];
	}
}

void swap(double & a, double & b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}

bool CheckGaussMatrix(int n, double** & matrix)
{
	int null = 0;
	bool flag = false;
	for (int j = 0; j < n; j++)
	{
		if (matrix[j][j] == 0)
		{
			for (int i = j + 1; i < n;i++)
			{
				if (matrix[i][j] != 0)
				{
					for (int h = 0; h <= n;h++)
					{
						swap(matrix[j][h], matrix[i][h]);
					}
					flag = true;
				}
			}
			if (!flag) { return false; }
			flag = false;
		}
	}
	return true;
}

double* methodGaussa(int n, double **matrix)
{
	double* x = new double[n];
	int colTemp = 0;
	double numberTemp = 0;
	for (int i = 0;i<n;i++)
	{
		numberTemp = matrix[i][colTemp];
		for (int j = colTemp; j < n; j++)
		{
			matrix[i][j] = matrix[i][j] / numberTemp;
		}
		matrix[i][n + 1] = matrix[i][n + 1] / numberTemp;
		for (int j = i + 1; j < n; j++)
		{
			numberTemp = matrix[j][colTemp];
			for (int h = colTemp; h < n; h++)
			{
				matrix[j][h] = matrix[j][h] - numberTemp * matrix[colTemp][h];
			}
			matrix[j][n + 1] = matrix[j][n + 1] - numberTemp * matrix[colTemp][n + 1];
		}
		colTemp += 1;
	}
	for (int i = n - 2; i >= 0; i--)
	{
		for (int j = 1; j <= n - 1 - i;j++)
		{
			matrix[i][n + 1] = matrix[i][n + 1] - matrix[i][i + j] * matrix[i+j][n + 1];
		}
	}
	for (int i = 0; i < n; i++)
	{
		x[i] = matrix[i][n + 1];
	}
	return x;
}




void output(int n, double *matrix)
{
	cout << "�����:" << '\n';
	for (int i = 0; i < n; i++)
	{
		cout << "x" << i + 1 << " = " << matrix[i] << '\n';
	}
}

