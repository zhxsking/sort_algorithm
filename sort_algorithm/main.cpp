#include <iostream>
#include <vector>
#include <array>
#include "sort_algorithm.h"

using namespace std;

int main()
{

	// ≤‚ ‘vector
	vector<int> arr1 = { 9, 7, 5, 3, 1 };

	cout << "vector:" << endl;
	for (auto i : arr1)
		cout << i << " ";
	cout << endl;

	for (auto i : quick_sort(arr1, arr1.size()))
		cout << i << " ";
	cout << endl;

	// ≤‚ ‘array
	array<double, 5> arr2 = {1.1, 2.2, 4.4, 3.3, 5.5};

	cout << "array:" << endl;
	for (auto i : arr2)
		cout << i << " ";
	cout << endl;

	for (auto i : quick_sort(arr2, arr2.size()))
		cout << i << " ";
	cout << endl;

}