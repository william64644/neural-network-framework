#pragma once

#include <vector>
#include <sstream>
#include <chrono>
#include <math.h>

using namespace std;

void matrix_randomizer(vector<vector<double>> &data)
{
    srand(std::chrono::system_clock::now().time_since_epoch().count());
    for (long unsigned int i = 0; i < data.size(); i++)
    {
        for (long unsigned int j = 0; j < data[i].size(); j++)
        {
            data[i][j] = (rand() % 100) / 100.0;
        }
    }
}

void reset_matrix(vector<vector<double>> &matrix)
{
    for (unsigned int i = 0; i < matrix.size(); i++)
    {
        for (unsigned int j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void reset_vector(vector<double> &vec)
{
    fill(vec.begin(), vec.end(), 0);
}

void layer_parser(Layer &A_layer, Layer &B_layer)
{
    reset_vector(B_layer.neurons);
    for (unsigned int i = 0; i < A_layer.neurons.size(); i++)
    {
        for (unsigned int j = 0; j < A_layer.weights[0].size(); j++)
        {
            B_layer.neurons[j] += A_layer.neurons[i] * A_layer.weights[i][j];
        }
    }
	for (unsigned int k = 0; k < B_layer.neurons.size(); k ++)
	{
		B_layer.neurons[k] = tanh(B_layer.neurons[k]);
	}
}

void print_layer_data(Layer &layer)
{
	//cout << "================================\n";
	cout << '\t' << layer.name << " Neurons:" << '\n';
	print_data(layer.neurons); // print neuron values

	if (layer.weights[0].size() > 0) // only print weights if there are any
	{
		cout << '\t' << layer.name << " Weights:" << '\n';
		print_matrix(layer.weights);
	}
	else
	{
		cout << '\t' << layer.name << " Weights: None" << '\n';
	}
}

struct Layer // give it the size of the layer and the size of the next layer (0 for the output layer)
{
    vector<double> neurons;
    vector<vector<double>> weights;
    string name;
    Layer(unsigned int size, unsigned int next_layer_size, string name = "Layer")
    {
        neurons = vector<double>(size);
        weights = vector<vector<double>>(size, vector<double>(next_layer_size));
        this->name = name;
    }
};

struct Network
{
	vector<Layer> layers;

	Network(vector<Layer> layers)
	{
		this->layers = layers;
	}

	void print_network()
	{
		cout << "================================\n";
		for (unsigned int i = 0; i < layers.size(); i++)
		{
			print_layer_data(layers[i]);
		}
		cout << "================================\n";
	}
};
