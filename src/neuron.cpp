/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "neuron.h"
#include "local_math.h"

#include <iostream>

CNeuron::CNeuron(std::string name)
    : m_neuron_name(name)
{
    m_bias_weight = RandomNumGen();
}

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
    m_activation = Sigmoid(m_linear_combination); // A = output
}

void CNeuron::SetOutputDerive(float error)
{
    // derivative of output neuron
    m_output_derivative = -error * (exp(m_linear_combination) / pow((1 + exp(m_linear_combination)), 2));
//    m_bias_weight = Sigmoid(m_bias) * m_output_derivative;
}

void CNeuron::SetHiddenDerive(float derivative, float weight)
{
    // derivative of hidden neuron
    m_output_derivative = (exp(m_linear_combination) / pow((1 + exp(m_linear_combination)), 2)) * weight * derivative;
//    m_bias_weight = Sigmoid(m_bias) * m_output_derivative;
}

float CNeuron::GetDerive()
{
    return m_output_derivative;
}

void CNeuron::AddSynapse(const std::string name)
{
    CSynapse synapse(name);
    synapse.SetWeight(RandomNumGen());
    m_listOfConnectedSynapses.emplace_back(std::move(synapse));
}

void CNeuron::SetSynapseInput(const std::string& id, const float input)
{
    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            it.SetInput(input);
            return;
        }
    }
    std::cout << "SetSynapseInput Error, Synapse " << id << " for " << m_neuron_name << " not found" << std::endl;
}

//void CNeuron::SetSynapseWeight(const std::string& id, const float weight)
//{
//    for(auto& it: m_listOfConnectedSynapses)
//    {
//        if(id == it.GetID()) {
//            it.SetWeight(weight);
//            return;
//        }
//    }
//    std::cout << "SetSynapseWeight Error, Synapse " << id << " for " << m_neuron_name << " not found" << std::endl;
//}

void CNeuron::UpdateHiddenSynapseWeight(const std::string& id, const float derivative)
{
    m_bias_weight = Sigmoid(m_bias) * m_output_derivative;

    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            it.UpdateWeight(derivative);
            return;
        }
    }
    std::cout << "UpdateSynapseWeight Error, Synapse " << id << " for " << m_neuron_name << " not found" << std::endl;
}

void CNeuron::UpdateOutputSynapseWeight(const std::string& id, const float activation)
{
    m_bias_weight = Sigmoid(m_bias) * m_output_derivative;

    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            it.UpdateWeight2(m_output_derivative, activation);
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

//void CNeuron::SetBiasWeight(float bias)
//{
//    m_bias_weight = bias;
//}

float CNeuron::GetOutput() const
{
    return m_activation;
}

void CNeuron::Reset()
{
    // reset neuron
    m_bias_weight = RandomNumGen();

    // reset connected synapses
    for(auto& it: m_listOfConnectedSynapses)
    {
        it.Reset();
    }
}
