#pragma once
#include <list>
#include <string>
#include "Layer.h"

class Network
{
public:
	Network(list<Layer> layers);
	Network();
	void train(list<float> inputs, float learningRaye, list<float>expected);
	void predict(list<float> inputs);
	list<float> getPrediction();
	void addLayer(Layer layer);
	void addLayer(int previousLayerCount, int neuronCount, string activation);
	void traverseLayers(int layerCount, int weightIndex);
	void traverseLayerTest();
private:
	list<Layer> layers;
	int getMax(list<float> predictions);
	Layer getLayer(int index);
};