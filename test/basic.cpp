/*****************************************************************
 * Copyright (C) 2017-2019 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Comms
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include <gtest/gtest.h>

#include "../src/neuron.h"

//#include <iostream>


/* ANN XOR example
 *
 * Input    Output
 *  A  B    A XOR B
 *  0  0      0
 *  0  1      1
 *  1  0      1
 *  1  1      0
 *
 */
TEST(Learning, XOR_Example)
{
    // set inputs and outputs - INPUT LAYER
    float input_1 = 1;
    float input_2 = 0;
    float output = 1;
    float expected_output = 1;
    float initial_weight = 0.1f;
    float bias = 0.5f;

    // build the network
    // HIDDEN LAYER
    CNeuron n1;
    n1.SetBias(bias);
    CSynapse w11("w11");
    CSynapse w21("w21");
    n1.AddSynapse(w11);
    n1.AddSynapse(w21);
    n1.SetSynapseWeight("w11", initial_weight);
    n1.SetSynapseWeight("w21", initial_weight);

    CNeuron n2;
    n2.SetBias(bias);
    CSynapse w12("w12");
    CSynapse w22("w22");
    n2.AddSynapse(w12);
    n2.AddSynapse(w22);
    n2.SetSynapseWeight("w12", initial_weight);
    n2.SetSynapseWeight("w22", initial_weight);

    // OUTPUT LAYER
    CNeuron n3;
    n3.SetBias(bias);
    CSynapse w31("w31");
    CSynapse w32("w32");
    n3.AddSynapse(w31);
    n3.AddSynapse(w32);
    n3.SetSynapseWeight("w31", initial_weight);
    n3.SetSynapseWeight("w32", initial_weight);

    int numberOfLearningLoops =1; // for now
    for(int index = 0; index < numberOfLearningLoops; ++index)
    {
        // process the network - left to right
        n1.SetSynapseInput("w11", input_1);
        n1.SetSynapseInput("w21", input_2);
        n1.Process();

        n2.SetSynapseInput("w12", input_1);
        n2.SetSynapseInput("w22", input_2);
        n2.Process();

        n3.SetSynapseInput("w31", n1.GetOutput());
        n3.SetSynapseInput("w32", n2.GetOutput());
        n3.Process();


        output = n3.GetOutput();
        std::cout << "output = " << output << std::endl;


        float reverse_weight = 0.5f * (expected_output - output);
        std::cout << "reverse_weight = " << reverse_weight << std::endl;

    }

    // get the results
    output = n3.GetOutput();
//    EXPECT_EQ(output, 1);

}
