/*****************************************************************
 * Copyright (C) 2017-2020 Robert Valler - All rights reserved.
 *
 * This file is part of the project: DevPlatformAppCMake.
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "Cluster.h"

#include "Neuron.h"
#include "Input.h"

#include "Logger.h"

#include <random>

CCluster::CCluster()
    : m_expectedOutput(0)
    , m_actualOutput(1)
{

}

void CCluster::CreateNeuralCluster()
{
    // all hard coded for now

    // CREATE THE NEURAL CLUSTER STRUCTURE
    // INPUTS: 2 inputs
    m_inputs.emplace_back(std::make_shared<CInput>(*this, 1, "Input1"));
    m_inputs.emplace_back(std::make_shared<CInput>(*this, 2, "Input2"));

    // HIDDEN: 1 hidden layer with three neurons for now
    m_hiddenCluster1.emplace_back(std::make_shared<CNeuron>(*this, 3, "Layer1_Neuron1"));
    m_hiddenCluster1.emplace_back(std::make_shared<CNeuron>(*this, 4, "Layer1_Neuron2"));
    m_hiddenCluster1.emplace_back(std::make_shared<CNeuron>(*this, 5, "Layer1_Neuron3"));

    // OUTPUTS: One output
    m_outputNeuron.emplace_back(std::make_shared<CNeuron>(*this, 6, "Output"));


    // ADD ALL SYNAPSES
    m_hiddenCluster1[0]->AddSynapse();
    m_hiddenCluster1[0]->AddSynapse();
    m_hiddenCluster1[1]->AddSynapse();
    m_hiddenCluster1[1]->AddSynapse();
    m_hiddenCluster1[2]->AddSynapse();
    m_hiddenCluster1[2]->AddSynapse();

    m_outputNeuron[0]->AddSynapse();
    m_outputNeuron[0]->AddSynapse();
    m_outputNeuron[0]->AddSynapse();

    // CREATE THE NEURAL CLUSTER MAPPING
    std::vector<int> m_NeuronRoute;
    for(const auto& it_inputs: m_inputs)
    {


        for(const auto& it_hidden1: m_hiddenCluster1)
        {
            it_hidden1->AddSynapse(it_inputs);
            it_hidden1->AddSynapseLink();

            for(const auto& it_outputs: m_outputNeuron)
            {
                m_NeuronRoute = {it_inputs->GetID(), it_hidden1->GetID(), it_outputs->GetID()};
                m_NeuronRouteList.emplace_back(m_NeuronRoute);

                CLogger::Print(LOGLEV_RUN, "Input = ", m_NeuronRoute[0] );
                CLogger::Print(LOGLEV_RUN, "Hidden = ", m_NeuronRoute[1] );
                CLogger::Print(LOGLEV_RUN, "Output = ", m_NeuronRoute[2] );

            }
        }
    }
}

void CCluster::SetInput(float input1, float input2)
{
    m_inputs[0]->SetValue(input1);
    m_inputs[1]->SetValue(input2);
}

void CCluster::SetExpectedOutput(float output)
{
    m_expectedOutput = output;
}

void CCluster::TriggerExecution()
{
    for(auto& it : m_hiddenCluster1)
    {


    }
}

float CCluster::GetOutput()
{
    return m_actualOutput;
}
