/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include <vector>
#include <memory>

struct SGateFormat {
    int A;
    int B;
    int Out;
};

class CNeuron;

class CSetupNeuralCluster
{
public:
    CSetupNeuralCluster() =default;
    ~CSetupNeuralCluster() =default;

    void Setup(const std::vector<SGateFormat>& InputTable);
    void Train();
    void Test();

private:
    std::shared_ptr<CNeuron> n1;
    std::shared_ptr<CNeuron> n2;
    std::shared_ptr<CNeuron> n3;
    std::vector<SGateFormat> m_InputTable;
};
