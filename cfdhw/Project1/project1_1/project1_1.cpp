// project1_1.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
void initialarray(double **, int,int);

void outputarray(char*, double**);
void fillbc(double**, int,int );
void pointcount(double**, int,int);
void pointreplace(double**, double**, double**, double);

int l = 2;
int xinf = 3* l;
int length = l + xinf;
int height = 1;
double delx = 0.05;
int row = (length / delx) ;		  //30
int column = (height / delx) ;	  //5	
int mesh_amount = row*column;
double d = 0.4;

int main()
{

	char *sf = "streamfunction.txt";
	double **strfunc = new double*[row];
	double **ffunc = new double*[row];
	double **sfunc = new double*[row];

	for (int i = 0; i <= row; i++) 
	{
		*(strfunc + i) = new double[row];
		*(ffunc + i) = new double[row];
		*(sfunc + i) = new double[row];
	}
	initialarray(strfunc, row, column);	
	initialarray(ffunc, row, column);
	initialarray(sfunc, row, column);
	fillbc(strfunc, row,column);
	fillbc(ffunc, row, column);
	fillbc(sfunc, row, column);
	
	
	double error = 1.0;
	
	pointreplace(strfunc, ffunc, sfunc, error);
	int dd = column - (d / delx);

	
	
	outputarray(sf, sfunc);

    return 0;
}

void initialarray(double **arr, int ro, int co)
{
	for (int i = 0; i <= co; i++)
	{
		for (int j = 0; j <= ro; j++) 
		{
			*(*(arr + i) + j) = 0.0;
			
		}		
	}
}


void fillbc(double**arr, int ro, int co) 
{
	for (int i = 0; i <= co; i++)
	{
		for (int j = 0; j <= ro; j++)
		{
			if (i == 0) 
			{
				*(*(arr + i) + j) = 1;
			}
			else if (j == 0) 
			{
				if(((co-i)/(double)co)>=d)
					*(*(arr + i) + j) = (((co - i)/(double)co)-d) / (1 - d);
			}
			else if (j == ro) 
			{
				*(*(arr + i) + j) = (co-i) / (double)co;
			}
		}
	}	
}

void pointcount(double **arr,int ro,int co) 
{
	for (int i = 1; i < co; i++)
	{
		for (int j = 1; j < ro; j++)
		{
			*(*(arr + i) + j) = 0.25*(*(*(arr+i)+j-1)+ *(*(arr + i) + j + 1)+ *(*(arr + i-1) + j )+ *(*(arr + i+1) + j - 1));			
		}
	}
	int dd = co - (d / delx);
	for (int i=dd;i<=co;i++) 
	{
		for (int j=0;j<=(l/delx);j++) 
		{
			*(*(arr + i) + j) = 0;
		}
	}

}
void pointreplace(double**aro, double**arf, double**ars, double er) 
{
	int i = 0;
	do
	{
		er = 0.0;
		for (int i = 0; i <= column; i++)
		{
			for (int j = 0; j <= row; j++)
			{
				*(*(arf + i) + j) = *(*(aro + i) + j);
			}
		}
		pointcount(aro, row, column);
		for (int i = 0; i <= column; i++)
		{
			for (int j = 0; j <= row; j++)
			{
				*(*(ars + i) + j) = *(*(aro + i) + j);
			}
		}
		for (int i = 0; i <= column; i++)
		{
			for (int j = 0; j <= row; j++)
			{
				er+= *(*(ars + i) + j) - *(*(arf + i) + j);
			}
		}
		i++;		

	} while (er > 0.0001); 
	

	cout << i;

}

void outputarray(char*fname, double**arr)
{
	fstream sfmatrix;
	sfmatrix.open(fname, ios::out);
	sfmatrix << "variables=x,y,psi" << endl;
	sfmatrix << "zone "<<"i="<<row+1<<"	,"<<"j= "<< column+1 <<" ,"<<"f=point"<<endl;	
	
	for (int i = 0; i <= column; i++) 
	{
		for (int j = 0; j <= row; j++) 
		{
			sfmatrix << (j)/(double)(column) << " " <<(column-i)/double(column) << " " << fixed<<setprecision(6)<<*(*(arr + i) + j) << endl;
			
		}
	}
	
	/*
	for (int i = 0; i <= column; i++)
	{
		for (int j = 0; j <= row; j++)
		{
			sfmatrix <<fixed<<setprecision(5)<<*(*(arr + i) + j) << " ";
			if (j == row)
				sfmatrix << endl;

		}
	}
	*/

}