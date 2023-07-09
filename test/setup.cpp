/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "setup.h"

#include "../src/neuron.h"
#include "../src/local_math.h"

#include <gtest/gtest.h>
#include <cmath>
#include <iostream>

void CSetupNeuralCluster::Setup(const std::vector<SGateFormat>& InputTable)
{
    // ##############################################################################
    // -- build the network --
    // ##############################################################################

    m_InputTable = InputTable;

    // hidden layer
    n1 = std::make_shared<CNeuron>("hidden_1", ENeuronType::EHidden);
    n1->AddSynapse("w11");   // Input 1 / A
    n1->AddSynapse("w21");   // Input 2 / B

    n2 = std::make_shared<CNeuron>("hidden_2", ENeuronType::EHidden);
    n2->AddSynapse("w12");   // Input 1 / A
    n2->AddSynapse("w22");   // Input 2 / B

    // output layer
    n3 = std::make_shared<CNeuron>("output", ENeuronType::EOutput);
    n3->AddSynapse("w31");   // Hidden 1
    n3->AddSynapse("w32");   // Hidden 2
}

void CSetupNeuralCluster::Train()
{
    // ##############################################################################
    // -- Training --
    // ##############################################################################

    float errors[4] = {0,0,0,0};
    int epoch = 0;

    for(int learn_index = 0; learn_index < l_training_loops; ++learn_index)
    {
        int input_index = 0;
        for(const auto& it : m_InputTable)
        {
            // process inputs
            n1->SetSynapseInput("w11", it.A);
            n1->SetSynapseInput("w21", it.B);
            n1->Process();

            n2->SetSynapseInput("w12", it.A);
            n2->SetSynapseInput("w22", it.B);
            n2->Process();

            n3->SetSynapseInput("w31", n1->GetOutput());
            n3->SetSynapseInput("w32", n2->GetOutput());
            n3->Process();

            // update the derivatives
            float error = n3->GetOutput() - it.Out;
            errors[input_index] = error;
            n3->SetOutputDerive(error);
            n1->SetHiddenDerive(n3->GetDerive(), n3->GetSynapseWeight("w31"));
            n2->SetHiddenDerive(n3->GetDerive(), n3->GetSynapseWeight("w32"));

            // Update the weights (inputs and bias)
            n1->UpdateHiddenSynapseWeight();
            n2->UpdateHiddenSynapseWeight();

            n3->UpdateOutputSynapseWeight("w31", n1->GetOutput());
            n3->UpdateOutputSynapseWeight("w32", n2->GetOutput());
            n3->UpdateNeuronBias();

            input_index++;

        } // range InputTable

        float rmse_error = sqrt((   pow(errors[0], 2) +
                                    pow(errors[1], 2) +
                                    pow(errors[2], 2) +
                                    pow(errors[3], 2) / 4));

        // error too high
        if (epoch++ > 5000 && rmse_error > 0.5)
        {
            n1->Reset();
            n2->Reset();
            n3->Reset();
            epoch = 0;
        }

    } // learn_index
}

void CSetupNeuralCluster::Test()
{
    // ##############################################################################
    // -- Testing --
    // ##############################################################################

    for(const auto& it : m_InputTable)
    {
        // input
        n1->SetSynapseInput("w11", it.A);
        n1->SetSynapseInput("w21", it.B);
        n1->Process();

        n2->SetSynapseInput("w12", it.A);
        n2->SetSynapseInput("w22", it.B);
        n2->Process();

        // output
        n3->SetSynapseInput("w31", n1->GetOutput());
        n3->SetSynapseInput("w32", n2->GetOutput());
        n3->Process();

        // check the results
        float result = n3->GetOutput();
        std::cout << "Output = " << result << "(" << round(result) << "), expected output = " << it.Out << std::endl;
        EXPECT_EQ(round(result), it.Out);
    }
}
