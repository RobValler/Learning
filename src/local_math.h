/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
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
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(-1, 1);
    float val = distr(eng);
    return val;
}

inline float ActivationMethod(const float input)
{
    // sigmoidal function
    float result = 1 / (1 + exp(-input));
    return result;
}
