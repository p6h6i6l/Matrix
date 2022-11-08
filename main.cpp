#include <iostream>
#include <algorithm>
#include <random>
#include<stdio.h>
#include <cmath>
#include "Matrix.h"


int main(int argc, char const *argv[])
{
	Matrix<double> a(5,5);
	Matrix<double> b(5,1);
	a.out_matrix();
	//a.make_one();
	//b.out_matrix();
	//a.out_matrix();
	b.out_matrix();
	a.to_down_tringled(b);	
	a.out_matrix();
	a.to_led(b);
	a.out_matrix();
	b.out_matrix();
	std::cout << "Solved!";
	return 0;
}