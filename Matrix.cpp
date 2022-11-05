#include <iostream>
#include <algorithm>
#include <random>
#include<stdio.h>
#include <cmath>

class Matrix
{
public: 
size_t length; 
size_t wight;
double** Head;
double epsilon;


	Matrix(size_t wight_, size_t length_)
	{
		epsilon = 0.00001;
		std::random_device r;
 		std::default_random_engine e1(r());
		std::uniform_int_distribution<int> uniform_dist(0, 100);
		length = length_;
		wight = wight_;
		Head = new double*[wight];	
		for (size_t i =0; i < wight; i++)
		{
			Head[i] = new double[length];
			for(size_t k = 0; k < length; k++)
			{
				Head[i][k] = uniform_dist(e1);
				//Head[i][k] = 2;
			}
		}
	}


	Matrix(const Matrix &another)
	{
		length = another.length;
		wight = another.wight;
		Head = another.Head;
		for (size_t i = 0; i < wight; i++)
		{
			for (size_t j = 0; j < length; j++)
			{
				Head[i][j] = another.Head[i][j];
			}
		}
	}


	Matrix& operator = (const Matrix& another)
	{
		if (&another == this)
			return *this;
		Matrix t(another);
		std::swap(wight, t.wight);
		std::swap(length, t.length);
		std::swap(Head, t.Head);
		return *this;
	}


	Matrix& swap_lines (size_t first, size_t second)
	{
		double* tmp;
		tmp = Head[first];
		Head[first] = Head[second];
		Head[second] = tmp;
		return *this;
	}


	Matrix& swap_columns (size_t first, size_t second)
	{
		for (int i = 0; i < length; i++)
		{
			std::swap(Head[i][first],Head[i][second]);
		}
		return *this;
	}


	Matrix& sum_first_to_second (size_t first, size_t second)
	{
		for (int i = 0; i < wight; i++)
		{
			Head[second][i] = Head[second][i] + Head[first][i];
		}
		return *this;
	}


	Matrix& multiply_by_constant (double constant, size_t line)
	{
		for (int i = 0; i < length; i++)
		{
			Head[line][i] = constant * Head[line][i];
		}
		return *this;
	}


	Matrix& sum_multiplied_first_to_second(size_t first, size_t second, double constant)
	{
		double t[length];
		for (int i = 0 ; i < length; i++)
		{
			t[i] = constant*Head[first][i];
			Head[second][i] = t[i] + Head[second][i];
		}
		return *this;
	}


	Matrix& make_one()
	{
		for(size_t i = 0; i < length; i++)
		{
			for(size_t j = 0 ; j < wight; j++)
			{
				if(i == j)
				{
					Head[i][j] = 1;
				}
				else
				{
					Head[i][j] = 0;
				}
				
			}
		}
		return *this;
	}


	void out_matrix()
	{
		for(size_t i = 0; i < wight; i++)
		{
			for( size_t j = 0 ; j < length; j++)
			{
				printf("%10.5f ", Head[i][j]);
			}
			std::cout << std::endl;
		}
		std::cout<<std::endl;
		return;
	}


	Matrix& to_down_tringled(Matrix& b)
	{
		size_t a = 0;
		for(size_t i = 0; i < length; i++)
		{
			for(int j = 0 ; j < wight; j++)
			{
				if(abs(Head[j][i]) > epsilon and j >=a)
				{
					swap_lines(a,j);
					b.swap_lines(a,j);
					b.multiply_by_constant(1/(Head[a][i]), a);
					multiply_by_constant(1/(Head[a][i]), a);
					for(size_t k = a+1; k < wight; k++)
					{
						b.sum_multiplied_first_to_second(a,k, -Head[k][i]);
						sum_multiplied_first_to_second(a,k, -Head[k][i]);
						//out_matrix();
					}
					a++;
					break;
				}
			}
		}
		return *this;
	}


	Matrix& to_led(Matrix &b)
	{
		for(size_t i = wight-1; i+1 > 0; i--)
			{
				for (size_t j = 0; j < length; j++)
				{
					if(abs(Head[i][j] > epsilon ))
					{
						for (size_t k = i-1; k+1 >0; k--)
						{
							b.sum_multiplied_first_to_second(i,k, -Head[k][j]);
							sum_multiplied_first_to_second(i,k, -Head[k][j]);
							//out_matrix();
						}
						break;
					}
				}
			}
			//sort_columns(b);
		return *this;
	}


	~Matrix()
	{
		for (int i = 0; i < wight; i++)
		{
			delete[] Head[i];
		}
		delete[] Head;
	}
	
};


int main(int argc, char const *argv[])
{
	Matrix a(1000,1000);
	Matrix b(1000,1);
	//b.make_one();
	//b.out_matrix();
	a.out_matrix();
	b.out_matrix();
	a.to_down_tringled(b);	
	//a.out_matrix();
	a.to_led(b);
	a.out_matrix();
	b.out_matrix();
	std::cout << "Solved!";
	return 0;
}