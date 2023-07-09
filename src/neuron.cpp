/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "neuron.h"

#include "local_math.h"
#include "constants.h"

#include <iostream>

CNeuron::CNeuron(std::string name, ENeuronType type)
    : m_neuron_name(name)
    , m_type(type)
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
    m_linear_combination += (m_bias * m_bias_weight); // Z = combination

    //activation - sigmoidal
    m_activation = ActivationMethod(m_linear_combination); // A = output
}

void CNeuron::SetOutputDerive(float error)
{
    // derivative of output neuron
    m_output_derivative = -error * (exp(m_linear_combination) / pow((1 + exp(m_linear_combination)), 2));
}

void CNeuron::SetHiddenDerive(float derivative, float weight)
{
    // derivative of hidden neuron
    m_output_derivative = (exp(m_linear_combination) / pow((1 + exp(m_linear_combination)), 2)) * weight * derivative;
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

void CNeuron::SetSynapseInput(const int index, const float input)
{
    if(index >= 0 && index < m_listOfConnectedSynapses.size()) {
        m_listOfConnectedSynapses.at(index).SetInput(input);
    }
}

void CNeuron::UpdateNeuronBias()
{
    // get the gradient
    float gradient = ActivationMethod(m_bias) * m_output_derivative;

    // Update the weight
    float update_weight = (l_learning_rate * gradient) + (l_momentum * m_prev_bias_weight);
    m_prev_bias_weight = update_weight;
    m_bias_weight += update_weight;
}


///\ todo: integrate this function into SetHiddenDerive if possible
/// same with UpdateOutputSynapseWeight (with SetOutputDerive)
void CNeuron::UpdateHiddenSynapseWeight()
{
    for(auto& it: m_listOfConnectedSynapses) {
        it.UpdateHiddenWeight(m_output_derivative);
    }
    UpdateNeuronBias();
}

void CNeuron::UpdateOutputSynapseWeight(const std::string& id, const float activation)
{
    for(auto& it: m_listOfConnectedSynapses)
    {
        if(id == it.GetID()) {
            it.UpdateOutputWeight(m_output_derivative, activation);
            return;
        }
    }
    std::cout << "UpdateSynapseWeight Error, Synapse " << id << " for " << m_neuron_name << " not found" << std::endl;
}

void CNeuron::UpdateOutputSynapseWeight(const int index, const float activation)
{
    if(index >= 0 && index < m_listOfConnectedSynapses.size()) {
        m_listOfConnectedSynapses.at(index).UpdateOutputWeight(m_output_derivative, activation);
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
    std::cout << "GetSynapseWeight Error, Synapse " << id << " not found" << std::endl;
    return 0.0f;
}

float CNeuron::GetSynapseWeight(const int index)
{
    if(index >= 0 && index < m_listOfConnectedSynapses.size()) {
        return m_listOfConnectedSynapses.at(index).GetWeight();
    } else {
        return 0.0f;
    }
}

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
