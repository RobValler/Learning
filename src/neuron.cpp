/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "neuron.h"

#include <iostream>

void CNeuron::Process()
{
    // linear combination of all connected synapses
    m_linear_combination = 0.0f;
    for(const auto& it: m_listOfConnectedSynapses)
    {
        m_linear_combination += (it.GetInput() * it.GetWeight());
    }
    m_linear_combination += (m_bias * m_bias_weight); // Z = dot product

    //activation - sigmoidal
    m_activation = Sigmoid(m_linear_combination); // A - output
}

void CNeuron::SetDerive(float parm)
{
    // derivative of output
    m_output_derivative = (exp(m_linear_combination) / pow((1 + exp(m_linear_combination)), 2)) * parm;

    m_bias_weight = Sigmoid(m_bias) * m_output_derivative;

}

float CNeuron::GetDerive()
{
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

void CNeuron::UpdateSynapseWeight(const std::string& id, const float derivative)
{
    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            it.UpdateWeight(derivative);
            return;
        }
    }
    std::cout << "UpdateSynapseWeight Error, Synapse " << id << " for " << m_neuron_name << " not found" << std::endl;
}

void CNeuron::UpdateSynapseWeight(const std::string& id)
{
    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            it.UpdateWeight2(m_output_derivative);
            return;
        }
    }
    std::cout << "UpdateSynapseWeight Error, Synapse " << id << " for " << m_neuron_name << " not found" << std::endl;
}

float CNeuron::GetSynapseWeight(const std::string& id)
{
    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            return it.GetWeight();
        }
    }
    std::cout << "GetSynapseWeight Error, Synapse " << id << " not found" << std::endl;
    return 0.0f;
}

void CNeuron::SetBiasWeight(float bias)
{
    m_bias_weight = bias;
}

float CNeuron::GetOutput() const
{
    return m_activation;
}
