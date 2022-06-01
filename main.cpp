#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/file_handler.h"
#include "headers/utils.h"
#include "headers/core_neural.h"
#include "headers/data_types.h"

using namespace std;

int main()
{

	const char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

	Layer input(3, 3);
	Layer output(3, 0);

	/*
		1 0 0
		0 1 0

		0 1 0
		0 0 1

		0 0 1
		1 0 0
	*/

	// rock paper scissors
	input.neurons = {1, 0, 0};

	vector<vector<double>> results;

	for (unsigned int i = 0; i < 2; i++)
	{
		matrix_randomizer(input.weights);

		layer_parser(input, output);

		results.push_back(output.neurons);
	}
	results = matrix_transponser(results);

	Vector3 error = {(average(results[0])) * -1, (average(results[1]) - 1) * -1, (average(results[2])) * -1};

	vector<double>
		averages = {average(results[0]), average(results[1]), average(results[2])};

	cout << averages[0] << " error: " << error.x << '\n';
	cout << averages[1] << " error: " << error.y << '\n';
	cout << averages[2] << " error: " << error.z << '\n';

	vector_packager(averages, "data/neurons/B");
	repack(input.weights, "data/weights/AB");

	return 0;
}
// ssssssssssssssssssssss