/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include <math.h>
#include <random>

inline float RandomNumGen()
{
#if 1
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(-1, 1);
    float val = distr(eng);
    return val;
#else
    float val;
    int randNum = rand() % 2;
    if (randNum == 1)
        val = -1 * (double(rand()) / (double(RAND_MAX) + 1.0)); // generate number between -1.0 and 0.0
    else
        val = double(rand()) / (double(RAND_MAX) + 1.0); // generate number between 1.0 and 0.0

    return val;
#endif

}

inline float Sigmoid(const float input)
{
    float result = 1 / (1 + exp(-input));
    return result;
}


//inline float SigmoidDerivative(const float input)
//{
//    return input * (1 - input);
//}

