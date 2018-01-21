/*
 * NeuralNetwork.cpp
 *
 *  Created on: Jul 28, 2017
 *      Author: robert
 */

#include "NeuralNetwork.h"

#include <cmath>
#include <random>

namespace EvolutionSimulator
{

NeuralNetwork::NeuralNetwork(int numInputs, int numOutputs, int hiddenLayers, int neuronsPerLayer,
		std::mt19937_64& generator) :
		m_neurons(neuronsPerLayer, hiddenLayers), m_outputs(numOutputs)
{
	m_synapses.emplace_back(numInputs, neuronsPerLayer);
	for (int i = 0; i < hiddenLayers - 1; i++)
	{
		m_synapses.emplace_back(neuronsPerLayer, neuronsPerLayer);
	}
	m_synapses.emplace_back(neuronsPerLayer, numOutputs);

	std::uniform_real_distribution<double> dist(-1.0, 1.0);
	for (unsigned int i = 0; i < m_synapses.size(); i++)
	{
		for (int j = 0; j < m_synapses[i].ROWS; j++)
		{
			for (int k = 0; k < m_synapses[i].COLS; k++)
			{
				m_synapses[i][j][k] = dist(generator);
			}
		}
	}
}

NeuralNetwork::NeuralNetwork(NeuralNetwork& other, std::mt19937_64& generator) :
		m_synapses(other.m_synapses), m_neurons(other.m_neurons.ROWS, other.m_neurons.COLS), m_outputs(
				other.m_outputs.size())
{
	std::uniform_int_distribution<int> countDist(0, m_synapses.size() - 1);

	for (unsigned int i = 0; i < m_synapses.size(); i++)
	{
		std::uniform_int_distribution<int> jDist(0, m_synapses[i].ROWS - 1);
		std::uniform_int_distribution<int> kDist(0, m_synapses[i].COLS - 1);
		int count = countDist(generator);
		for (int c = 0; c < count; c++)
		{
			int j = jDist(generator);
			int k = kDist(generator);
			std::normal_distribution<double> mutationDist(m_synapses[i][j][k], 1.0);
			m_synapses[i][j][k] = mutationDist(generator);
		}
	}
}

NeuralNetwork::~NeuralNetwork()
{
}

const std::vector<double>& NeuralNetwork::getOutputs(const std::vector<double>& inputs)
{
	for (int i = 0; i < m_neurons.ROWS; i++)
	{
		m_neurons[i][0] = 0.0;
		for (unsigned int j = 0; j < inputs.size(); j++)
		{
			m_neurons[i][0] += m_synapses[0][j][i] * inputs[j];
		}
		m_neurons[i][0] = sigmoid(m_neurons[i][0]);
	}
	for (int i = 1; i < m_neurons.COLS; i++)
	{
		for (int j = 0; j < m_neurons.ROWS; j++)
		{
			m_neurons[j][i] = 0.0;
			for (int k = 0; k < m_neurons.ROWS; k++)
			{
				m_neurons[j][i] += m_synapses[i][k][j] * m_neurons[k][i - 1];
			}
			m_neurons[j][i] = sigmoid(m_neurons[j][i]);
		}
	}
	for (unsigned int i = 0; i < m_outputs.size(); i++)
	{
		m_outputs[i] = 0.0;
		for (int j = 0; j < m_neurons.ROWS; j++)
		{
			m_outputs[i] += m_synapses[m_synapses.size() - 1][j][i]
					* m_neurons[j][m_neurons.COLS - 1];
		}
		m_outputs[i] = sigmoid(m_outputs[i]);
	}
	return m_outputs;
}

double NeuralNetwork::sigmoid(double x)
{
	return 1.0 / (1.0 + std::exp(-x));
}

} /* namespace EvolutionSimulator */
