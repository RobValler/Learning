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

    void UpdateWeight(float parm)
    {
        float gradient = Sigmoid(m_input) * parm;
        m_update_weight = (l_learning_rate * gradient) + (l_momentum * m_prev_update_weight);
        m_prev_update_weight = m_update_weight;
        m_weight += m_update_weight;
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
    float m_update_weight{0.0f};
    float m_prev_update_weight{0.0f};

};

class CNeuron
{
public:
    CNeuron() =default;
    ~CNeuron() =default;

    void Process();
    float Derive(float parm);
    void AddSynapse(const CSynapse& synapse);
    void SetSynapseInput(const std::string& id, const float input);
    void SetSynapseWeight(const std::string& id, const float weight);
    float GetSynapseWeight(const std::string& id);
    void SetBias(float bias);
    float GetOutput() const;

private:
    float m_bias{0};
    float m_output{0};
    float m_linear_combination{0};
    float m_activation{0};
    float m_output_derivative{0};

    std::vector<CSynapse> m_listOfConnectedSynapses;
};


