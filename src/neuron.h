/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include "synapse.h"

#include <vector>
#include <string>
#include <cstdint>

class CNeuron
{
public:
    enum class ENeuronType : std::uint8_t {
        EHidden =0,
        EOutput
    };

    CNeuron(std::string name, ENeuronType type);
    ~CNeuron() =default;

    void Process();
    void SetOutputDerive(float error);
    void SetHiddenDerive(float parm, float weight);

    float GetDerive();
    void AddSynapse(const std::string name);
    void SetSynapseInput(const std::string& id, const float input);
    void UpdateNeuronBias();
    void UpdateHiddenSynapseWeight();
    void UpdateOutputSynapseWeight(const std::string& id, const float activation);
    float GetSynapseWeight(const std::string& id);
    float GetOutput() const;
    void Reset();

private:
    std::string m_neuron_name;
    ENeuronType m_type;

    float m_bias{1};
    float m_bias_weight{0};
    float m_prev_bias_weight{0};
    float m_linear_combination{0};
    float m_activation{0};
    float m_output_derivative{0};

    std::vector<CSynapse> m_listOfConnectedSynapses;
};


