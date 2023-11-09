#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <random>
#include <vector>
#include "layer.h"
#include "loss.h"
#include "Initialisation.h"
#include "Activation.h"
#include "Network.h"
#include "CSV.h"
using namespace std;

int main()
{
	list<list<double>> values = CSV::read("D:\\iris.csv");
	
	vector<list<double>> valuesVector(values.begin(), values.end());
	random_device randomDevice;
	mt19937 generator(randomDevice());
	shuffle(valuesVector.begin(), valuesVector.end(), generator);

	cout << "finished" << endl;
	
	Layer* layer1 = new Layer(4, 4, "relu");
	Layer* layer2 = new Layer(4, 10, "relu");
	Layer* layer3 = new Layer(10, 8, "relu");
	Layer* layer4 = new Layer(8, 6, "relu");
	Layer* layer5 = new Layer(6, 3, "relu");
	Network* network = new Network();
	
	network->addLayer(*layer1);
	network->addLayer(*layer2);
	network->addLayer(*layer3);
	network->addLayer(*layer4);
	network->addLayer(*layer5);

	while(network->getError() > 0.5)
	{
		vector<list<double>>::iterator valuesIt = valuesVector.begin();
		for (int i = 0; i < values.size() - 1; ++i)
		{
			list<double> inputs = *valuesIt;
			list<double>::iterator inputsIt = inputs.end();
			advance(inputsIt, -1);

			list<double> expected;

			if (*inputsIt == 1)
			{
				expected = { 1,0,0 };
			}
			else if (*inputsIt == 2)
			{
				expected = { 0, 1, 0 };
			}
			else if (*inputsIt == 3)
			{
				expected = { 0, 0, 1 };
			}

			inputs.pop_back();

			network->train(inputs, 0.0001, expected);
			advance(valuesIt, 1);

			inputs.clear();
			expected.clear();
		}
	}
	
	float crossEntropyTests = Loss::crossEntropy({ 0.775,0.116,00.39,0.07 }, { 1,0,0,0 });
	cout << "loss: " << crossEntropyTests << endl;
	cout << "finished!" << endl;
	
	delete(layer1);
	delete(layer2);
	delete(layer3);
	delete(layer4);
	delete(network);
}