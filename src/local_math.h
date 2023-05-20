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
//#include <iomanip>

inline float random_num()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(-1, 1);
    float val = distr(eng);
    return val;
}

inline float Sigmoid(const float input)
{
    float result = 1 / (1 + exp(-input));
    return result;
}

inline float SigmoidDerivative(const float input)
{
    return input * (1 - input);
}

