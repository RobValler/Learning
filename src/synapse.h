/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#pragma once

#include "local_math.h"
#include "constants.h"

#include <string>

class CSynapse
{
public:
    CSynapse(std::string id);
    ~CSynapse()=default;

    void SetInput(float input);
    void SetWeight(float weight);
    void UpdateHiddenWeight(float derivative);
    void UpdateOutputWeight(float activation, float derivative);
    std::string& GetID();
    float GetWeight() const;
    float GetInput() const;
    void Reset();

private:
    inline void UpdateWeight(float gradient);

    std::string m_id{""};
    float m_input{0.0f};
    float m_weight{0.0f};
    float m_prev_update_weight{0.0f};
};
