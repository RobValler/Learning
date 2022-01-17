/*****************************************************************
 * Copyright (C) 2017-2020 Robert Valler - All rights reserved.
 *
 * This file is part of the project: DevPlatformAppCMake.
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#ifndef DFW_LEARNING_CLUSTER_H
#define DFW_LEARNING_CLUSTER_H

#include "INeuron.h"


#include <vector>
#include <memory>

class INeuron;

///< Neural network cluster
class CCluster
{
public:
    CCluster();
    CCluster(const CCluster& other)=delete;
    CCluster(CCluster&& other) noexcept =delete;
    CCluster& operator=(const CCluster& other)=default;
    CCluster& operator=(CCluster&& other) noexcept =default;
    ~CCluster() =default;

    // Layer handlers
    void CreateNeuralCluster();
    void SetInput(float input1, float input2);
    void SetExpectedOutput(float output);
    void TriggerExecution();
    float GetOutput();

protected:


private:
    // Input & Output
    float m_expectedOutput;
    float m_actualOutput;

    // TOTAL NEURON LIST
    std::vector<std::shared_ptr<INeuron>> m_neurons;


    // INPUT
    std::vector<std::shared_ptr<INeuron>> m_inputs;

    // HIDDEN, 1 -> N
    std::vector<std::shared_ptr<INeuron>> m_hiddenCluster1;
    //std::vector<CNeuron> m_OutputHiddenCluster2;
    //std::vector<CNeuron> m_OutputHiddenClusterN;
    // etc..
    //OUTPUT
    std::vector<std::shared_ptr<INeuron>> m_outputNeuron;

    //MAPPING
    std::vector<int> m_NeuronRoute;
    std::vector<std::vector<int>> m_NeuronRouteList;

};


#endif // DFW_LEARNING_CLUSTER_H
