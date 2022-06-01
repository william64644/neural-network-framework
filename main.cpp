#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "headers/file_handler.h"
#include "headers/utils.h"
#include "headers/core_neural.h"
#include "headers/data_types.h"

using namespace std;


double absolute_difference(double test_set[], double values[])
{
	double difference;
	const unsigned int lenght = sizeof(values)/sizeof(values[0]);
	for (unsigned int i = 0; i < lenght; i++)
	{
		difference += abs(test_set[i] - values[i]);
	}
	return difference;
}

int main()
{

	double test_set[3][2][3] = {{{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},{{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},{{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}};

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

	for (unsigned int i = 0; i < 1; i++)
	{
		matrix_randomizer(input.weights);

		layer_parser(input, output);

		results.push_back(output.neurons);
	}
	results = matrix_transponser(results);

	double averages[3] = {average(results[0]), average(results[1]), average(results[2])};

	double error = absolute_difference(test_set[0][1], averages);

	print_data(averages);

	print_matrix(input.weights);

	cout << '\n';

	cout << error;
	return 0;
}
// sssssssssssssssssssssssssssss
