/*****************************************************************
 * Copyright (C) 2017-2020 Robert Valler - All rights reserved.
 *
 * This file is part of the project: DevPlatformAppCMake.
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#ifndef DFW_LEARNING_IBLOCK_H
#define DFW_LEARNING_IBLOCK_H

#include <string>
#include <memory>

class INeuron
{
public:
    virtual ~INeuron(){}
    virtual int GetID() = 0;
    virtual std::string GetName() = 0;
    virtual float GetValue() = 0;
    virtual void SetValue(float) = 0;
    virtual void AddSynapse() = 0;
};


#endif // DFW_LEARNING_IBLOCK_H
