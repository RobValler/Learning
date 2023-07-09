/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include "synapse.h"
#include "constants.h"

#include <vector>
#include <string>

class CNeuron
{
public:
    CNeuron(std::string name, ENeuronType type);
    ~CNeuron() =default;

    void SetNumber(const int num) { m_number = num; }
    int GetNumber() { return m_number; }
    void SetValue(const float val) { m_value = val; }
    float GetValue() { return m_value; }
    void Reset();

    void Process();
    void SetOutputDerive(float error);
    void SetHiddenDerive(float parm, float weight);

    float GetDerive();
    void AddSynapse(const std::string name);
    void SetSynapseInput(const std::string& id, const float input);
    void SetSynapseInput(const int index, const float input);
    int GetNumberOfSynapses() { return m_listOfConnectedSynapses.size(); }
    void UpdateNeuronBias();
    void UpdateHiddenSynapseWeight();
    void UpdateOutputSynapseWeight(const std::string& id, const float activation);
    void UpdateOutputSynapseWeight(const int index, const float activation);
    float GetSynapseWeight(const std::string& id);
    float GetSynapseWeight(const int index);
    float GetOutput() const;

    ENeuronType GetType() { return m_type; }

    std::string GetName() {
        return m_neuron_name;
    }

private:
    std::string m_neuron_name;
    ENeuronType m_type;

    int m_number{0};
    float m_value{0};

    float m_bias{1};
    float m_bias_weight{0};
    float m_prev_bias_weight{0};
    float m_linear_combination{0};
    float m_activation{0};
    float m_output_derivative{0};

    std::vector<CSynapse> m_listOfConnectedSynapses;
};


