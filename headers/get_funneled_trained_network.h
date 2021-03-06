#pragma once

#include "Network.h"
#include "train_network.h"
#include "get_variation_scope.h"
Network get_funneled_trained_network(Network &network, vector<vector<vector<double>>> &in_out_settings, int phases = 20)
{
	cout << "traingn network ..." << '\n';

	for (unsigned int i = 0; i < phases; i++)
	{
		cout << "phase " << i + 1 << " - ";
		train_network(network, get_variation_scope(phases - i), in_out_settings);
		cout << "Error: " << network.error << '\n';
	}

	return network;
}