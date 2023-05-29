/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include "local_math.h"
#include "constants.h"

#include <string>

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
        float gradient = ActivationMethod(m_input) * derivative;

        // Update the weight
        float update_weight = (l_learning_rate * gradient) + (l_momentum * m_prev_update_weight);
        m_prev_update_weight = update_weight;
        m_weight += update_weight;
    }

    void UpdateWeight2(float activation, float derivative)
    {
        // Update the weight
        float gradient = activation * derivative;

        // Update the weight
        float update_weight = (l_learning_rate * gradient) + (l_momentum * m_prev_update_weight);
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

    void Reset()
    {
        SetWeight(RandomNumGen());
        m_prev_update_weight = 0.0f;
    }

private:
    std::string m_id{""};
    float m_input{0.0f};
    float m_weight{0.0f};
    float m_prev_update_weight{0.0f};

};
