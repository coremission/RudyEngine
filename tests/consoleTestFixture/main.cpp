#include "testfixture.hpp"
#include "projection_matrix_tests.h"
#include "transform_tests.hpp"

int main(int argc, char** argv)
{
	cout << "Test Runner" << endl;
	//localToWorld_Test();
	
	projectionMatrix_Test();
	
	cout << endl << "Press any key to exit..." << endl;
	cin.get();

	return 0;
}
