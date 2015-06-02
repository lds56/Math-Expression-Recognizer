#ifndef MATHCALCULATOR_H_
#define MATHCALCULATOR_H_

#define pi 3.1415926
#define e 2.7182818
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;
class STACK
{
public:
	int top;
	double element[100];
	STACK(){top=-1; }
	double pop(){double result; result=element[top]; top--; return result; }
	void push(double input){top++; element[top]=input;}
};

double preload(string in, int integrate_state, int derivative_state, int limit_state, double point1, double point2, char key);
double calculator(string original,char key,double point);
double integration(string original, char key, double point1, double point2);
double derivative(string original, char key, double point);
double limit(char *original, char key, double point);
double compute(string original);
string type_transform(string str);
string reform(string str);
string input(string& original);
double my_pow(double x,double y);
void unary_oper(STACK& number,double optr);
void binary_oper(STACK& number,double optr);
void oper(STACK& number,double optr);
int level(double optr);


#endif
