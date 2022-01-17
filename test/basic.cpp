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

#include <iostream>

TEST(Learning, BasicTest)
{
    // set inputs and outputs
    float input_1 = 1;
    float input_2 = 1;
    float output;

    // build the nextwork
    CNeuron n1;
    CSynapse w11("w11");
    CSynapse w21("w21");
    n1.AddSynapse(w11);
    n1.AddSynapse(w21);

    CNeuron n2;
    CSynapse w12("w12");
    CSynapse w22("w22");
    n1.AddSynapse(w12);
    n1.AddSynapse(w22);

    CNeuron n3;
    CSynapse w31("w31");
    CSynapse w32("w32");
    n1.AddSynapse(w31);
    n1.AddSynapse(w32);

    // set the input
    n1.SetSynapseInput("w11", input_1);
    n1.SetSynapseInput("w21", input_2);
    n2.SetSynapseInput("w12", input_1);
    n2.SetSynapseInput("w22", input_2);
    n3.SetSynapseInput("w31", n1.GetOutput());
    n3.SetSynapseInput("w32", n2.GetOutput());

    output = n3.GetOutput();

    EXPECT_EQ(output, 1);

}
