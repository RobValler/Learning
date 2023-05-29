/*****************************************************************
 * Copyright (C) 2017-2022 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/


#pragma once

#include <vector>

struct SGateFormat {
    int A;
    int B;
    int Out;
};

class CSetupNeuralCluster
{
public:
    CSetupNeuralCluster() =default;
    ~CSetupNeuralCluster() =default;

    void Run(const std::vector<SGateFormat>& InputTable);
    int FloatToInt(const float input){
        return static_cast<int>(input);
    }

};
