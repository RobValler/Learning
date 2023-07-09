/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include <cstdint>

namespace {
    constexpr int l_training_loops = 15000;
    constexpr float l_learning_rate = 1.414213562;
    constexpr float l_momentum = 0.25;    
}


enum class ENeuronType : std::uint8_t {
    EHidden =0,
    EOutput
};


