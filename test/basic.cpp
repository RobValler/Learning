/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include <gtest/gtest.h>

#include "../src/neuron.h"
#include "../src/local_math.h"

#include <cmath>

/* ANN XOR example
 *
 * Input    Output
 *  A  B    A XOR B
 *  0  0      0
 *  0  1      1
 *  1  0      1
 *  1  1      0
 */
struct XOR_format {
    int A;
    int B;
    int Out;
};

XOR_format XORInputOutput[]
{
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 0},
};

TEST(Learning, XOR_Example)
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

    float errors[4];

    // ##############################################################################
    // -- Training --
    // ##############################################################################

    // set the input
    int epoch = 0;
    int numberOfDifferentInputs = sizeof(XORInputOutput) / sizeof(XOR_format);
    for(int learn_index = 0; learn_index < 20000; ++learn_index) // learning loop
    {
//        std::cout << "-- begin loop = " << learn_index << std::endl;

        for(int input_index = 0; input_index < numberOfDifferentInputs; ++input_index)
        {
            // process hidden layer
            n1.SetSynapseInput("w11", XORInputOutput[input_index].A);
            n1.SetSynapseInput("w21", XORInputOutput[input_index].B);
            n1.Process();

            n2.SetSynapseInput("w12", XORInputOutput[input_index].A);
            n2.SetSynapseInput("w22", XORInputOutput[input_index].B);            
            n2.Process();

            n3.SetSynapseInput("w31", n1.GetOutput());
            n3.SetSynapseInput("w32", n2.GetOutput());
            n3.Process();

            // is the result a NaN (Not a Number)
//            if(std::isnan(n3.GetOutput()))
//                ASSERT_TRUE(false) << "---> NaN result detected, exiting";

            // get the result
//            std::cout << "output = " << n3.GetOutput() << ", expected output = " << XORInputOutput[input_index].Out << std::endl;

            // update the derivatives
            float error = n3.GetOutput() - XORInputOutput[input_index].Out;
            errors[input_index] = error;
            n3.SetOutputDerive(error);
            n1.SetHiddenDerive(n3.GetDerive(), n3.GetSynapseWeight("w31"));
            n2.SetHiddenDerive(n3.GetDerive(), n3.GetSynapseWeight("w32"));

            // Update the weights
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

//        std::cout << "RMSE error: " << rmse_error << std::endl;
//        std::cout << "-- end loop = " << learn_index << std::endl;

        // error too high
        if (epoch > 5000 && rmse_error > 0.5)
        {
            epoch = 0;

            n1.Reset();
            n2.Reset();
            n3.Reset();
        }

        epoch++;

    } // learn_index



    // ##############################################################################
    // -- Testing --
    // ##############################################################################
    for(int input_index = 0; input_index < numberOfDifferentInputs; ++input_index)
    {
        // input
        n1.SetSynapseInput("w11", XORInputOutput[input_index].A);
        n1.SetSynapseInput("w21", XORInputOutput[input_index].B);
        n1.Process();

        n2.SetSynapseInput("w12", XORInputOutput[input_index].A);
        n2.SetSynapseInput("w22", XORInputOutput[input_index].B);
        n2.Process();

        // output
        n3.SetSynapseInput("w31", n1.GetOutput());
        n3.SetSynapseInput("w32", n2.GetOutput());
        n3.Process();

        // check the results
        float result = n3.GetOutput();
        std::cout << "output = " << result << ", expected output = " << XORInputOutput[input_index].Out << std::endl;
//        EXPECT_EQ(result, XORInputOutput[input_index].Out);
    }

}
