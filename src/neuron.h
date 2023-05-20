/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include <vector>
#include <string>

#include "local_math.h"

namespace {
    constexpr float l_learning_rate = 1.414213562;
    constexpr float l_momentum = 0.25;
}

class CSynapse
{
public:
    CSynapse(std::string id)
        : m_id(id)
    {}
    ~CSynapse()=default;

    void SetInput(float input)
    {
        m_input = input;
    }

    void SetWeight(float weight)
    {
        m_weight = weight;
    }

    void UpdateWeight(float derivative)
    {
        // get the gradient
        float gradient = Sigmoid(m_input) * derivative;

        // Update the weight
        float update_weight = (l_learning_rate * gradient) + (l_momentum * m_prev_update_weight);
        m_prev_update_weight = update_weight;
        m_weight += update_weight;
    }

    void UpdateWeight2(float derivative)
    {
        // Update the weight
        float update_weight = m_input * derivative;
        m_prev_update_weight = update_weight;
        m_weight += update_weight;
    }

    std::string& GetID()
    {
        return m_id;
    }

    float GetWeight() const
    {
        return m_weight;
    }

    float GetInput() const
    {
        return m_input;
    }

private:
    std::string m_id{""};
    float m_input{0.0f};
    float m_weight{0.0f};
    float m_prev_update_weight{0.0f};

};

class CNeuron
{
public:
    CNeuron(std::string name)
        : m_neuron_name(name)
    {}
    ~CNeuron() =default;

    void Process();
    void SetDerive(float error);
    float GetDerive();
    void AddSynapse(const CSynapse& synapse);
    void SetSynapseInput(const std::string& id, const float input);
    void SetSynapseWeight(const std::string& id, const float weight);
    void UpdateSynapseWeight(const std::string& id, const float weight);
    void UpdateSynapseWeight(const std::string& id);
    float GetSynapseWeight(const std::string& id);
    void SetBiasWeight(float bias);
    float GetOutput() const;

private:
    std::string m_neuron_name;
    float m_bias{1};
    float m_bias_weight{0};
    float m_linear_combination{0};
    float m_activation{0};
    float m_output_derivative{0};

    std::vector<CSynapse> m_listOfConnectedSynapses;
};


