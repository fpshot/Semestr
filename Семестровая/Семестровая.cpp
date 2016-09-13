// Семестровая.cpp: определяет точку входа для консольного приложения.
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
void createInterface();

int main()
{
	system("chcp 1251");
	system("cls");
	bool gauss = false, kramer = false;
	double **matrix, *x;
	int n, choose;
	input(n, matrix);
	x = new double[n];
	bool quit = false;
	do
	{
		createInterface();
		try {
			cin.exceptions(std::ios_base::failbit);
			cin >> choose;
			switch (choose)
			{
			case 1:
				if (CheckGaussMatrix(n, matrix))
				{
					x = methodGaussa(n, matrix);
					output(n, x);
				}				
				else { system("cls"); cout << "Данная матрица не может быть решена методом Гаусса!" << '\n';  }
				break;
			case 2:

				break;
			case 3:
				input(n, matrix);
				x = new double[n];
				system("cls");
				break;
			case 4:
				quit = true;
				break;
			default:
				system("cls");
				cout << "Нет такого пункта в меню!" << '\n';
				break;
			}
		}
		catch (ios_base::failure e) {
			system("cls");
			cout << "Введите число!" << '\n';
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (!quit);
	delete[] matrix;
	delete[] x;
	return 0;
}

void createInterface()
{
	cout << "==========МЕНЮ==========" << '\n';
	cout << "Выберите пункт меню:" << '\n';
	cout << "1: Метод Гаусса" << '\n';
	cout << "2: Метод Крамера" << '\n';
	cout << "3: Ввести другую матрицу" << '\n';
	cout << "4: Выход" << '\n';
	cout << "========================" << '\n';
}

void input(int & n, double** & matrix)
{
	system("cls");
	bool notNumer = true;
	cout << "Введите количество уравнений: ";
	do
	{	
		try {	
			cin.exceptions(std::ios_base::failbit);
			cin >> n;
			if (n <= 0)
			{
				cout << "Введите натуральное число!: ";
				notNumer = true;
			}
			else { notNumer = false; }
		}
		catch (ios_base::failure e) {
			cout << "Введите число!: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (notNumer);
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
	system("cls");
}

void swap(double & a, double & b)
{
	double temp;
	temp = a;
	b = a;
	a = temp;
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
	int mul = 2;
	bool repetition = true;
	for (int i = 0; i < n;i++)
	{
		for (int h = i+1; h < n;h++)
		{
			for (int j = 0; j < n;j++)
			{
				if (matrix[i][j] != matrix[h][j]) { repetition = false; break; }
			}
			if (repetition)
			{
				return false;
			}
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
	system("cls");
	cout << "Ответ:" << '\n';
	for (int i = 0; i < n; i++)
	{
		cout << "x" << i + 1 << " = " << matrix[i] << '\n';
	}
}

