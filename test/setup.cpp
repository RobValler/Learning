/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
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

void CSetupNeuralCluster::Run(const std::vector<SGateFormat>& InputTable)
{
    // -- build the network --
    // hidden layer
    CNeuron n1("hidden_1");
    n1.AddSynapse("w11");   // Input 1 / A
    n1.AddSynapse("w21");   // Input 2 / B

    CNeuron n2("hidden_2");
    n2.AddSynapse("w12");   // Input 1 / A
    n2.AddSynapse("w22");   // Input 2 / B

    // output layer
    CNeuron n3("output");
    n3.AddSynapse("w31");   // Hidden 1
    n3.AddSynapse("w32");   // Hidden 2

    float errors[4] = {0,0,0,0};
    int epoch = 0;
    int numberOfDifferentInputs = InputTable.size();

    // ##############################################################################
    // -- Training --
    // ##############################################################################
    for(int learn_index = 0; learn_index < 20000; ++learn_index)
    {
        for(int input_index = 0; input_index < numberOfDifferentInputs; ++input_index)
        {
            // process inputs
            n1.SetSynapseInput("w11", InputTable[input_index].A);
            n1.SetSynapseInput("w21", InputTable[input_index].B);
            n1.Process();

            n2.SetSynapseInput("w12", InputTable[input_index].A);
            n2.SetSynapseInput("w22", InputTable[input_index].B);
            n2.Process();

            n3.SetSynapseInput("w31", n1.GetOutput());
            n3.SetSynapseInput("w32", n2.GetOutput());
            n3.Process();

            // update the derivatives
            float error = n3.GetOutput() - InputTable[input_index].Out;
            errors[input_index] = error;
            n3.SetOutputDerive(error);
            n1.SetHiddenDerive(n3.GetDerive(), n3.GetSynapseWeight("w31"));
            n2.SetHiddenDerive(n3.GetDerive(), n3.GetSynapseWeight("w32"));

            // Update the weights (inputs and bias)
            n1.UpdateHiddenSynapseWeight("w11", n1.GetDerive());
            n1.UpdateHiddenSynapseWeight("w21", n1.GetDerive());
            n1.UpdateNeuronBias();

            n2.UpdateHiddenSynapseWeight("w12", n2.GetDerive());
            n2.UpdateHiddenSynapseWeight("w22", n2.GetDerive());
            n2.UpdateNeuronBias();

            n3.UpdateOutputSynapseWeight("w31", n1.GetOutput());
            n3.UpdateOutputSynapseWeight("w32", n2.GetOutput());
            n3.UpdateNeuronBias();

        } // input_index

        float rmse_error = sqrt((   pow(errors[0], 2) +
                                    pow(errors[1], 2) +
                                    pow(errors[2], 2) +
                                    pow(errors[3], 2) / 4));

        // error too high
        if (epoch++ > 5000 && rmse_error > 0.5)
        {
            n1.Reset();
            n2.Reset();
            n3.Reset();
            epoch = 0;
        }

    } // learn_index

    // ##############################################################################
    // -- Testing --
    // ##############################################################################
    for(int input_index = 0; input_index < numberOfDifferentInputs; ++input_index)
    {
        // input
        n1.SetSynapseInput("w11", InputTable[input_index].A);
        n1.SetSynapseInput("w21", InputTable[input_index].B);
        n1.Process();

        n2.SetSynapseInput("w12", InputTable[input_index].A);
        n2.SetSynapseInput("w22", InputTable[input_index].B);
        n2.Process();

        // output
        n3.SetSynapseInput("w31", n1.GetOutput());
        n3.SetSynapseInput("w32", n2.GetOutput());
        n3.Process();

        // check the results
        float result = n3.GetOutput();
        std::cout << "Output = " << result << "(" << round(result) << "), expected output = " << InputTable[input_index].Out << std::endl;
        EXPECT_EQ(round(result), InputTable[input_index].Out);
    }

}