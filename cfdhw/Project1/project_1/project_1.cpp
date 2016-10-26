// project_1.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void show_1darray(double *,int);
void show_2darray(double **, int);
void initial_1darray(double *, int);
void initial_2darray(double **, int);
void fillupperbc(double**, int);
void out2darray(char*, double**, int);
void out1darray(char*, double*, int);
void fillchannelarray(double**, int,int,int);


int main()
{
	int l = 2;
	int xinf = 2 * l;
	int length = l+xinf;
	int height = 1;
	double delx = 0.2;
	int row = (length / delx)+1;
	int column = (height / delx)+1;
	int mesh_amount = row*column;

	double *ax = new double[mesh_amount];
	double *as = new double[mesh_amount];
	double **an = new double *[mesh_amount];

	for (int i = 0; i < mesh_amount; i++)
		*(an + i) = new double[mesh_amount];

	char *aa = "mainmatrix.txt";
	char *sf = "streamfunction.txt";
	char *nu = "number.txt";

	
	fstream sfmatrix;
	fstream numatrix;

	
	sfmatrix.open(sf, ios::out);
	numatrix.open(nu, ios::out);

	
	initial_1darray(ax, mesh_amount);
	initial_1darray(as, mesh_amount);
	initial_2darray(an, mesh_amount);

	fillupperbc(an, row);
	




	out2darray(aa, an, mesh_amount);
    return 0;
}

void show_1darray(double *arr,int number) 
{
	int am = number;
	
	for (int i = 0; i < am; i++) 
	{
		cout << *(arr + i) << endl;		
	}
}

void show_2darray(double **arr, int number) 
{
	int am = number;
	for (int i = 0; i < am; i++) 
	{
		for (int j = 0; j < am; j++) 
		{
			cout << *(*(arr + i) + j) << " ";
			if (j == am - 1)
				cout << endl;
		}
	}
}
void initial_1darray(double *arr, int am) 
{
	for (int i = 0; i < am; i++)
	{
		*(arr + i) =0.0;
	}
}
void initial_2darray(double **arr, int am) 
{
	for (int i = 0; i < am; i++)
	{
		for (int j = 0; j < am; j++)
		{
			 *(*(arr + i) + j) =0.0;			 
		}
	}
}
void fillupperbc(double **arr, int number) 
{
	for (int i = 0; i < number-1;i++) 
	{
		for (int j = 0; j < number-1; j++) 
		{
			if (i == j)
				*(*(arr + i) + j) = 1;
		}
	}
}

void out2darray(char*a1, double**arr, int number) 
{
	fstream amatrix;
	amatrix.open(a1, ios::out);
	amatrix << setw(4)<<" ";
	for (int i = 0; i < number; i++) 
	{
		amatrix <<setw(3)<<i + 1 << " ";
	}
	amatrix << endl;

	for (int i = 0; i < number; i++)
	{
		amatrix <<setw(3) <<i + 1 << " ";
		for (int j = 0; j < number; j++)
		{

			amatrix << setw(3) <<*(*(arr + i) + j) << " ";
			if (j == number - 1)
				amatrix << endl;
		}
	}
}

void out1darray(char*a2, double*arr, int number) 
{

}

void fillchannelarray(double**arr, int number) 
{


}


