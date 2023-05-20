/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "neuron.h"

void CNeuron::Process()
{
    // linear combination
    for(const auto& it: m_listOfConnectedSynapses)
    {
        m_linear_combination += (it.GetInput() * it.GetWeight());
    }
    m_linear_combination += m_bias; //???

    //activation - sigmoidal
    m_activation = Sigmoid(m_linear_combination);
    m_output = m_activation;
}

float CNeuron::Derive(float parm)
{
    // derivative of output
    m_output_derivative = (exp(m_linear_combination) / pow((1 + exp(m_linear_combination)), 2)) * parm;

    // calculate weightings of all connected synapses
    for(auto& it: m_listOfConnectedSynapses)
    {
        it.UpdateWeight(m_output_derivative);
    }
    return m_output_derivative;
}

void CNeuron::AddSynapse(const CSynapse& synapse)
{
    m_listOfConnectedSynapses.emplace_back(std::move(synapse));
}

void CNeuron::SetSynapseInput(const std::string& id, const float input)
{
    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            it.SetInput(input);
            break;
        }
    }
}

void CNeuron::SetSynapseWeight(const std::string& id, const float weight)
{
    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            it.SetWeight(weight);
            break;
        }
    }
}

float CNeuron::GetSynapseWeight(const std::string& id)
{
    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            return it.GetWeight();
        }
    }
    return 0.0f;
}

void CNeuron::SetBias(float bias)
{
    m_bias = bias;
}

float CNeuron::GetOutput() const
{
    return m_output;
}
