/*
 * NeuralNetwork.h
 *
 *  Created on: Jul 28, 2017
 *      Author: robert
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include <random>
#include <vector>

#include "Matrix.h"

namespace EvolutionSimulator
{

class NeuralNetwork
{
public:
	NeuralNetwork(int numInputs, int numOutputs, int hiddenLayers, int neuronsPerLayer,
			std::mt19937_64& generator);
	NeuralNetwork(NeuralNetwork& other, std::mt19937_64& generator);
	virtual ~NeuralNetwork();
	const std::vector<double>& getOutputs(const std::vector<double>& inputs);
private:
	static double sigmoid(double x);

	std::vector<Matrix> m_synapses;
	Matrix m_neurons;
	std::vector<double> m_outputs;
};

} /* namespace EvolutionSimulator */

#endif /* NEURALNETWORK_H_ */
