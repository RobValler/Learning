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

<<<<<<< HEAD:Learning/INeuron.h
class INeuron
=======
class CSynapse;
class IBlock
>>>>>>> 9a0becefad40eb07c82c48f80b8d63a82cab5e40:Learning/IBlock.h
{
public:
    virtual ~INeuron(){}
    virtual int GetID() = 0;
    virtual std::string GetName() = 0;
    virtual float GetValue() = 0;
    virtual void SetValue(float) = 0;
<<<<<<< HEAD:Learning/INeuron.h
    virtual void AddSynapse() = 0;
=======
    virtual void AddSynapse(std::shared_ptr<IBlock>) = 0;
    virtual void AddSynapseLink(std::shared_ptr<CSynapse>) = 0;

>>>>>>> 9a0becefad40eb07c82c48f80b8d63a82cab5e40:Learning/IBlock.h
};


#endif // DFW_LEARNING_IBLOCK_H
