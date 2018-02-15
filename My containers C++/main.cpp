#include <vld.h>
#include <iostream>
#include <string>
#include "Matrix.h"
using namespace std;

int main()
{
	spaceMatrix::Matrix<int> matrix(3, 3, 1), m(3, 3, 2), a;
	matrix -= m;
	matrix.Show();
	system("pause");
	return 0;
}