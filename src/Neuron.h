/*****************************************************************
 * Copyright (C) 2017-2020 Robert Valler - All rights reserved.
 *
 * This file is part of the project: DevPlatformAppCMake.
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#ifndef DFW_LEARNING_NEURON_H
#define DFW_LEARNING_NEURON_H

#include "INeuron.h"

#include <memory>
#include <vector>
#include <string>

class CCluster;

class CSynapse
{
public:
    CSynapse(IBlock* parent,
             std::shared_ptr<IBlock> link)
        :p_parentNeuron(parent)
        ,p_linkedNeuron(link)
    {}
    CSynapse(const CSynapse& other)=default;
    CSynapse(CSynapse&& other) noexcept =default;
    CSynapse& operator=(const CSynapse& other)=default;
    CSynapse& operator=(CSynapse&& other) noexcept =default;
    ~CSynapse(){}

    void SetWeight(float weight){ m_weight = weight; }
    void SetValue(float value){ m_inputValue = value; }
    float GetValue(){ return m_inputValue; }
    float GetWeight(){ return m_weight; }

private:
 //   std::shared_ptr<IBlock> p_parentNeuron;
    IBlock *p_parentNeuron;
    std::shared_ptr<IBlock> p_linkedNeuron;
    float m_weight;
    float m_inputValue;
};

<<<<<<< HEAD
class CNeuron : public INeuron
=======

class CNeuron : public IBlock
>>>>>>> 9a0becefad40eb07c82c48f80b8d63a82cab5e40
{
public:
    CNeuron(CCluster& parent, int ID, std::string name)
        : m_parent(parent)
        , m_neuronID(ID)
        , m_neuronName(name)
        , m_influence(0)
        , m_activationValue(0)
    {}
    CNeuron(const CNeuron& other)=default;
    CNeuron(CNeuron&& other) noexcept =default;
    CNeuron& operator=(const CNeuron& other)=default;
    CNeuron& operator=(CNeuron&& other) noexcept =default;
    ~CNeuron() override {}

    int GetID() override { return m_neuronID; }
    std::string GetName() override { return m_neuronName; }
    void SetValue(float value) override { }
    void AddSynapse() override;


    // Layer handlers
<<<<<<< HEAD
=======
    void AddSynapse(std::shared_ptr<IBlock> link) override;
    void AddSynapseLink(std::shared_ptr<CSynapse> link) override;

    void AddInput(float input);
>>>>>>> 9a0becefad40eb07c82c48f80b8d63a82cab5e40
    void UpdateInput(float intput);
    void UpdateWeightings(float weighting);
    float GetValue() override;

    // calculate the XOR result
    void ActivationFunction();

protected:

private:
    CCluster& m_parent;
    int m_neuronID;
    std::string m_neuronName;
    float m_influence;
    float m_activationValue;
    float m_output;
    std::vector<CSynapse> m_synapseList;
    std::vector<std::shared_ptr<CSynapse>> m_synapseForwardList;

};


#endif // DFW_LEARNING_NEURON_H
