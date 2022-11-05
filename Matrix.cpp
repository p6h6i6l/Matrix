#include <iostream>
#include <algorithm>
#include <random>
#include<stdio.h>
#include <cmath>
#include "Based_Class.h"


int main(int argc, char const *argv[])
{
	Matrix a(10,10);
	Matrix b(10,1);
	a.make_one();
	b.out_matrix();
	a.out_matrix();
	b.out_matrix();
	//a.to_down_tringled(b);	
	//a.out_matrix();
	//a.to_led(b);
	a.out_matrix();
	b.out_matrix();
	std::cout << "Solved!";
	return 0;
}