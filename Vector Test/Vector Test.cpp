#include "../Engine/Source/Data Structures/Vector.h"
using FS12::vector;
using FS12::vector_iterator;

#include <iostream>
using std::cout;
using std::endl;

#include <ctime>

#include <vector>

int main()
{
	srand(unsigned int(time(0)));
	rand();

	vector<int> int_vec;

	std::vector<int> int_stdvec;

	for (unsigned int i = 0; i < 50; ++i)
	{
		int_vec.push_back(rand() % 100 + 1);
	}

	int_stdvec.pop_back();

	cout << "int_vec.size() = " << int_vec.size() << endl << "int_vec.capacity() = " << int_vec.capacity() << endl;

	system("pause");

	return 0;
}