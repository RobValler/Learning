/*****************************************************************
 * Copyright (C) 2017-2020 Robert Valler - All rights reserved.
 *
 * This file is part of the project: DevPlatformAppCMake.
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#ifndef DFW_LEARNING_INPUT_H
#define DFW_LEARNING_INPUT_H

<<<<<<< HEAD
#include "INeuron.h"
=======
#include "IBlock.h"
#include "Neuron.h"

>>>>>>> 9a0becefad40eb07c82c48f80b8d63a82cab5e40
#include <string>
#include <memory>
#include <vector>

class CCluster;
class CSynapse;

class CInput : public INeuron
{
public:
    CInput(CCluster& parent, int ID, std::string name)
        : m_parent(parent)
        , m_neuronID(ID)
        , m_inputName(name)
        , m_value(0)
    {}
    CInput(const CInput& other)=default;
    CInput(CInput&& other) noexcept =default;
    CInput& operator=(const CInput& other)=default;
    CInput& operator=(CInput&& other) noexcept =default;
    ~CInput() override {}

    int GetID() override { return m_neuronID; }
    std::string GetName() override { return m_inputName; }
    float GetValue() override { return m_value; }
    void SetValue(float value) override { m_value = value; }
<<<<<<< HEAD
    void AddSynapse() override {}
=======
    void AddSynapse(std::shared_ptr<IBlock>) override {}
    void AddSynapseLink(std::shared_ptr<CSynapse> link) override
    {
        m_synapseForwardList.emplace_back(link);
    }
>>>>>>> 9a0becefad40eb07c82c48f80b8d63a82cab5e40


private:
    CCluster& m_parent;
    int m_neuronID;
    std::string m_inputName;
    float m_value;
    std::vector<std::shared_ptr<CSynapse>> m_synapseForwardList;

};

#endif // DFW_LEARNING_INPUT_H
