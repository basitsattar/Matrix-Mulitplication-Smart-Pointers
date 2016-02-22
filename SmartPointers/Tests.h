
#include "Matrix.h"
#include <memory>
#include <iostream>

bool test_create() 
{
	bool temp = true;
	MyClass obj(16, 16);
	temp &= (obj.row == 16 && obj.col == 16);
	MyClass obj2(16, 16);
	temp &= (obj2.row == 16 && obj2.col == 16);

    cout << "\n\nMatrix 1 is \n\n" <<endl;
    obj.print_array();
    cout << "\n\nMatrix 2 is \n\n" <<endl;
    obj2.print_array();
	return temp;
}


bool test_crt()
{
	bool temp = true;
	MyClass obj(16, 16, 0);
    
	for (int i = 0; i < obj.row; i++)
	{
		for (int j = 0; j < obj.col; j++)
		{
			temp &= (obj.array_[i][j] == 0);
		}
	}

	MyClass obj2(16, 16, 2);
		
	for (int i = 0; i < obj2.row; i++)
	{
		for (int j = 0; j < obj2.col; j++)
		{
			temp &= (obj2.array_[i][j] == 2);
		}
	}

	return temp;
}

bool test_Iterative_algo()
{
	bool temp = true;
	
	MyClass obj(16, 16);
	MyClass obj2(16, 16);
	obj.Iterative_algo(16, 16, 16, 16, &obj2);
	
	for (int i = 0, r = 16; r < 16; r++, i++)
	{
		for (int j = 0, c = 16; c < 16; c++, j++)
		{
			temp &= (obj.array_[i][j] == obj2.array_[r][c]);
		}
	}
	return temp;
}

bool test_StrassenAlgo()
{
	bool temp = true;
	
	MyClass obj(16, 16);
	
	MyClass obj2(16, 16);

	std::auto_ptr<MyClass> matrix1(obj * obj2);
	std::auto_ptr<MyClass> matrix2(obj.StrassenAlgo(&obj2));

	temp &= (*matrix1 == *matrix2);

	return temp;
}
