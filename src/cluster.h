/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include <vector>
#include <memory>

#include "neuron.h"
#include "constants.h"


struct SInputCluster
{
    int numOfInputs;
    int numOfHiddenLayers;
    int numOfNeuronsPerHiddenLayer;
    int numOfOutputs;
};

struct SPackInput {
    int number;
    int value;
};

struct SPackNeuron {
    int number;
    std::shared_ptr<CNeuron> pneuron;  // for hidden and output layers
};

struct SPack {
    std::string layer_name;
    ENeuronType layer_type;
    int layer_number; // used in combination with layer_type
    std::vector<SPackInput> input_list;     // for input layer only
    std::vector<SPackNeuron> neuron_list;   // for hidden and output layers
};

struct SCluster
{
    std::vector<SPack> layer_list;
};


class CNeuralCluster
{
public:
    CNeuralCluster() =default;
    ~CNeuralCluster() =default;
    void Init();
    void Setup(SInputCluster input);

private:
    SCluster m_cluster;

};
