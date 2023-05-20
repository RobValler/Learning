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
    float A;
    float B;
    float Out;
};

XOR_format XORInputOutput[]
{
    {0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 0.0f},
};

TEST(Learning, XOR_Example)
{
    // -- build the network --
//    const float default_bias = 1.0f;
    // hidden layer
    CNeuron n1;
    n1.AddSynapse(CSynapse("w11"));
    n1.AddSynapse(CSynapse("w21"));
    n1.SetBias(random_num());
    n1.SetSynapseWeight("w11", random_num());
    n1.SetSynapseWeight("w21", random_num());

    CNeuron n2;
    n2.AddSynapse(CSynapse("w12"));
    n2.AddSynapse(CSynapse("w22"));
    n2.SetBias(random_num());
    n2.SetSynapseWeight("w12", random_num());
    n2.SetSynapseWeight("w22", random_num());

    // output layer
    CNeuron n3;
    n3.AddSynapse(CSynapse("w31"));
    n3.AddSynapse(CSynapse("w32"));
    n3.SetBias(random_num());
    n3.SetSynapseWeight("w31", random_num());
    n3.SetSynapseWeight("w32", random_num());

    // -- training --
    float error = 0.0f;
    float derivative_n3 = 0.0f;
    float derivative_n2 = 0.0f;
    float derivative_n1 = 0.0f;
    float derivative_A = 0.0f;
    float derivative_B = 0.0f;

    int numberOfDifferentInputs = sizeof(XORInputOutput) / sizeof(XOR_format);
    for(int learn_index = 0; learn_index < 100; ++learn_index) // learning loop
    {
        std::cout << "-- begin loop = " << learn_index << std::endl;

        for(int input_index = 0; input_index < numberOfDifferentInputs; ++input_index)
        {
            // process the network - left to right
            // input -> hidden
            n1.SetSynapseInput("w11", XORInputOutput[input_index].A);
            n1.SetSynapseInput("w21", XORInputOutput[input_index].B);
//            n1.Process();

            n2.SetSynapseInput("w12", XORInputOutput[input_index].A);
            n2.SetSynapseInput("w22", XORInputOutput[input_index].B);
//            n2.Process();

            // output
            n3.SetSynapseInput("w31", n1.GetOutput());
            n3.SetSynapseInput("w32", n2.GetOutput());

            //
            n1.Process();
            n2.Process();
            n3.Process();

            // is the result a NaN (Not a Number)
            if(std::isnan(n3.GetOutput()))
                ASSERT_TRUE(false) << "---> NaN result detected, exiting";

            // get the result
            std::cout << "output = " << n3.GetOutput() << ", expected output = " << XORInputOutput[input_index].Out << std::endl;

            // update the weightings

            float f1 = n3.GetOutput() - XORInputOutput[input_index].Out;
            float f2 = 0.5 * (f1*f1);
            error = f2;

//            error = n3.GetOutput() - XORInputOutput[input_index].Out;
            derivative_n3 = n3.Derive(-error);
            derivative_n2 = n2.Derive(n2.GetSynapseWeight("w32") * derivative_n3);
            derivative_n1 = n1.Derive(n2.GetSynapseWeight("w31") * derivative_n3);

            n1.SetSynapseWeight("w11", derivative_n1);
            n1.SetSynapseWeight("w12", derivative_n2);

            n2.SetSynapseWeight("w21", derivative_n1);
            n2.SetSynapseWeight("w22", derivative_n2);


        } // input_index
        std::cout << "-- end loop = " << learn_index << std::endl;

    } // learn_index

    // -- testing --
    for(int input_index = 0; input_index < numberOfDifferentInputs; ++input_index)
    {
        // input
        n1.SetSynapseInput("w11", XORInputOutput[input_index].A);
        n1.SetSynapseInput("w21", XORInputOutput[input_index].B);
        n1.Process();

        // hidden
        n2.SetSynapseInput("w12", XORInputOutput[input_index].A);
        n2.SetSynapseInput("w22", XORInputOutput[input_index].B);
        n2.Process();

        // output
        n3.SetSynapseInput("w31", n1.GetOutput());
        n3.SetSynapseInput("w32", n2.GetOutput());
        n3.Process();

        // check the results
        EXPECT_EQ(n3.GetOutput(), XORInputOutput[input_index].Out);
    }
}
