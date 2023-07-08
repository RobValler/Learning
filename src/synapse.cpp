/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "synapse.h"

CSynapse::CSynapse(std::string id)
    : m_id(id)
{

}

void CSynapse::SetInput(float input)
{
    m_input = input;
}

void CSynapse::SetWeight(float weight)
{
    m_weight = weight;
}

void CSynapse::UpdateHiddenWeight(float derivative)
{
    // get the gradient
    float gradient = ActivationMethod(m_input) * derivative;
    UpdateWeight(gradient);
}

void CSynapse::UpdateOutputWeight(float activation, float derivative)
{
    // Update the weight
    float gradient = activation * derivative;
    UpdateWeight(gradient);
}

std::string& CSynapse::GetID()
{
    return m_id;
}

float CSynapse::GetWeight() const
{
    return m_weight;
}

float CSynapse::GetInput() const
{
    return m_input;
}

void CSynapse::Reset()
{
    SetWeight(RandomNumGen());
    m_prev_update_weight = 0.0f;
}

void CSynapse::UpdateWeight(float gradient)
{
    // Update the weight
    float update_weight = (l_learning_rate * gradient) + (l_momentum * m_prev_update_weight);
    m_prev_update_weight = update_weight;
    m_weight += update_weight;
}
