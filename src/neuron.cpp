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
