/*****************************************************************
 * Copyright (C) 2017-2020 Robert Valler - All rights reserved.
 *
 * This file is part of the project: DevPlatformAppCMake.
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "Neuron.h"

#include "Logger.h"

#include <random>

void CNeuron::AddSynapse(std::shared_ptr<IBlock> link)
{
    CSynapse synapse(this, link);
    float value = 0;
    float weight = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    synapse.SetValue(value);
    synapse.SetWeight(weight);
    m_synapseList.emplace_back(std::move(synapse));
    CLogger::Print(LOGLEV_RUN, "Link: ", link->GetName(), " to ", GetName());
}

void CNeuron::AddSynapseLink(std::shared_ptr<CSynapse> link)
{
    m_synapseForwardList.emplace_back(link);
}

void CNeuron::AddSynapse()
{
    SSynapse synapse;
    synapse.inputFromPrevious = 0;
    synapse.weightingForCurrent = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    CLogger::Print(LOGLEV_RUN, "NEURON ", m_neuronName, " : Input = ", synapse.inputFromPrevious, ", Weighting ", synapse.weightingForCurrent);
    m_synapseList.emplace_back(std::move(synapse));

}

void CNeuron::UpdateInput(float intput)
{

}

void CNeuron::UpdateWeightings(float weighting)
{

}

float CNeuron::GetValue()
{
    return m_output;
}

// XOR define TEST
//input | output
//    --------------
//    0, 0  | 0
//    0, 1  | 1
//    1, 0  | 1
//    1, 1  | 0
// calculat the XOR result
void CNeuron::ActivationFunction()
{
    // calculate the influence
    // value1 * weighting1 + value2 * weighting2 + valueN * weightingN
    for(auto& it : m_synapseList)
    {
        m_influence += it.GetValue() * it.GetWeight();
    }
    CLogger::Print(LOGLEV_RUN, m_neuronName, " Influence value = ", m_influence);

    // run the activation and calculate the value
    // linear
    m_activationValue = m_influence;

    // sigmoid (logistic)

    // hyperbolic tangent
    CLogger::Print(LOGLEV_RUN, m_neuronName, " Activation value = ", m_activationValue);

}
