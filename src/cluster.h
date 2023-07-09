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
#include <string>

#include "constants.h"

class CNeuron;

struct SLayerContainer {
    std::string layer_name;
    ENeuronType layer_type;
    int layer_number;
    std::vector<std::shared_ptr<CNeuron>> node_list;  ///< List of neurons/inputs .. in each layer
};

class CNeuralCluster
{
public:
    CNeuralCluster() =default;
    ~CNeuralCluster() =default;

    void Setup(int numOfInputs, int numOfHiddenLayers, int numOfNeuronsPerHiddenLayer, int numOfOutputs);
    void Train(std::vector<std::vector<int>> input_data);
    void Store() {}
    void Load() {}
    bool Test(std::vector<std::vector<int>> input_data);

    void ResetAllNodes();

private:
    std::vector<SLayerContainer> layer_list;   ///< List of layers

};
