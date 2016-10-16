// p2_(b).cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

const double e = 2.718;
double f_diff(const int,double);	//forward difference
double b_diff(const int,double);  //backward difference
double c_diff(const int,double);  //central difference
double t_diff(const int,double);  //difference from 2-(a)

int main()
{

	const int x = 2;

	cout <<"h   |"<<" forward diff |" << " backward diff |" << " central diff |" << " taylor diff |"<<"exact diff"<<endl;
	double *f_ans=new double [5];
	double *b_ans = new double[5];
	double *c_ans = new double[5];
	double *t_ans = new double[5];
	const double e_ans = pow(e, 2);
	int count=0;	

	for (double h = 0.01; h < 0.06; h = h + 0.01) 
	{
		*(f_ans + count) = f_diff(x, h);
		*(b_ans + count) = b_diff(x, h);
		*(c_ans + count) = c_diff(x, h);
		*(t_ans + count) = t_diff(x, h);
		count++;
	}
	count = 0;
	double h_int = 0.01;
	
	double *f_err = new double[5];
	double *b_err = new double[5];
	double *c_err = new double[5];
	double *t_err = new double[5];

	for (double h = 0.01; h < 0.06; h = h + 0.01)
	{
		*(f_err + count) = abs(f_diff(x, h)- e_ans);
		*(b_err + count) = abs(b_diff(x, h)- e_ans);
		*(c_err + count) = abs(c_diff(x, h)- e_ans);
		*(t_err + count) = abs(t_diff(x, h)- e_ans);
		count++;
	}


	
	for (int i = 0; i < 5; i++) 
	{
		cout << h_int <<"|"
			 << setw(14) <<*(f_ans + i) << "|" << setw(15)<<*(b_ans + i)<<"|" 
			 << setw(14) << *(c_ans + i) << "|" << setw(13)<<*(t_ans+i)<<"|"
			 << setw(10) <<e_ans <<endl;
		h_int = h_int + 0.01;
					
	}
	h_int = 0.01;
	
	
	cout << endl;
	cout << "h   |" << " forward error |" << " backward error |" << " central error |" << " taylor error |" << endl;
	
	for (int i = 0; i < 5; i++)
	{
		cout << h_int << "|"
			 << setw(15) << *(f_err + i) << "|" << setw(16) << *(b_err + i) << "|"
			 << setw(15) << *(c_err + i) << "|" << setw(14) << *(t_err + i) << "|"
			 << endl;
		
		h_int += 0.01;		
			
	}
	h_int = 0.01;
	char *number = "number.txt";
	char *error = "error.txt";

	fstream countnumber;
	fstream errornumber;

	countnumber.open(number, ios::out);
	errornumber.open(error, ios::out);

	for (int i = 0; i < 5; i++) 
	{
		countnumber << h_int<<" "<<*(f_ans + i) << " " << *(b_ans + i) << " " << *(c_ans + i) << " " << *(t_ans + i) << " " <<e_ans<<endl;
		errornumber << h_int << " "<<*(f_err + i) << " " << *(b_err + i) << " " << *(c_err + i) << " " << *(t_err + i) << " " << endl;
		h_int += 0.01;
	}

	delete[]f_ans;
	delete[]b_ans;
	delete[]c_ans;
	delete[]t_ans;
	


    return 0;
}

double f_diff(const int x, double h)
{
	double ans;

	ans = (pow(e, x+h)- pow(e,x))/h;

	return ans;
}

double b_diff(const int x, double h)
{
	double ans;
	ans = (pow(e, x) - pow(e, x-h)) / h;
	return ans;
}

double c_diff(const int x, double h)
{
	double ans;
	ans = (pow(e, x + h) - pow(e, x-h)) / (2*h);
	return ans;
}

double t_diff(const int x, double h)
{
	double ans;

	ans = (((-2)* pow(e,x-h))+((-3)* pow(e,x))+ (6* pow(e, x+h))+ ((-1)* pow(e, x+2*h)))/(6*h);

	return ans;
}