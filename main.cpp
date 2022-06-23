#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <sys/stat.h>

#include "headers/Layer.h"
#include "headers/print_layer_data.h"
#include "headers/layer_parser.h"
#include "headers/matrix_randomizer.h"
#include "headers/Network.h"
#include "headers/vector_packager.h"
#include "headers/absolute_difference.h"
#include "headers/double_packager.h"
#include "headers/repack_network.h"
#include "headers/read_file.h"
#include "headers/variate.h"
#include "headers/variate_matrix.h"
#include "headers/print_matrix.h"
#include "headers/print_data.h"
#include "headers/split.h"
//ssssssssssss
using namespace std;

double test_network(Network network, vector<vector<vector<double>>> &in_out_settings)
{
	double total_error;
	for (unsigned int test_set = 0; test_set < in_out_settings.size(); test_set ++)
	{
	network.layers[0].neurons = in_out_settings[test_set][0];
	network.expected_output = in_out_settings[test_set][1];
	
	network.parse_network();
	
	total_error += network.error;
	}
	return total_error * network.error;
}

void variate_network(Network &network, int variation)
{
	for (unsigned int layer = 0; layer < network.layers.size(); layer ++)
	{
		variate_matrix(network.layers[layer].weights, variation);
	}
}

Network train(Network network, int variation, vector<vector<vector<double>>> in_out_settings, int iterations = 100)
{
	Network best_network = network;
	Network cache_network = network;
	
	double best_error = network.layers.back().neurons.size();
	double current_error = best_error;

	for (unsigned int iteration = 0; iteration < iterations; iteration ++)
	{
		variate_network(cache_network, variation);
		cache_network.parse_network();
		current_error = test_network(cache_network, in_out_settings);
		
		if (current_error < best_error)
		{
			best_error = current_error;
			best_network = cache_network;
		} else {
			cache_network = best_network;
		}
	}
	return best_network;
}

vector<double> get_input(int numbers_ammount)
{
	vector<double> nums;
	cout << "Type " << numbers_ammount << " numbers" << '\n';
	for (unsigned int i = 0; i < numbers_ammount; i ++)
	{
		cout << ">>> ";
		string num;
		cin >> num;
		nums.push_back(stod(num));
	}
	return nums;
}

int main()
{
	vector<vector<vector<double>>> in_out_settings = {{{1, 0, 0}, {0, 1, 0}}, {{0, 1, 0}, {0, 0, 1}}, {{0, 0, 1}, {1, 0, 0}}};

	const string input_names[3] = {"Rock", "Paper", "Scissors"};

	// setup
	Layer input(3, 3, "Input", {"Input_Rock", "Input_Paper", "Input_Scissors"});
	Layer output(3, 0, "Output", {"Output_Rock", "Output_Paper", "Output_Scissors"});
	
	Network network({input, output});
	
	// configure
	matrix_randomizer(network.layers[0].weights);
	
	// train
	Network trained = train(network, 100, in_out_settings);
	
	// runtime
	cout << "Training phase complete, the network error is " << test_network(trained, in_out_settings) << '\n';
	
	vector<double> game_input = get_input(3);
	
	print_data(game_input);
	

	return 0;
}
