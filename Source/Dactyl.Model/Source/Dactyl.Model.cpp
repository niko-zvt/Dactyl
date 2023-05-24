#include <iostream>
#include "Calc.h"
#include "Dactyl.Model.h"
#include <Core>
#include <Dense>

void hello_model()
{
	auto suma = test_sum(5.1, 4.2);
	std::cout << "Hello, Model!\n\t5.1 + 4.2 = 9.3 == " << suma << std::endl;

	Eigen::Matrix3d test; //3 by 3 double precision matrix initialization

    // Let's make it a symmetric matrix
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            test(i,j) = (i+1)*(1+j);
    }

    print_matrix(test);
}

void print_matrix(Eigen::MatrixX3d m)
{
    std::cout << m << std::endl;
}