

#pragma once

#include <vector>
#include <string>

class CSynapse
{
public:
    CSynapse(std::string id)
        : m_id(id)
    {}
    ~CSynapse()=default;

    void SetInput(float input){
        m_input = input;
    }

    void SetWeight(float weight){
        m_weight = weight;
    }

    std::string& GetID()
    {
        return m_id;
    }

private:
    std::string m_id{""};
    float m_weight{0.0F};
    float m_input{0.0F};
};

class CNeuron
{
public:
    CNeuron() =default;
    ~CNeuron() =default;

    void AddSynapse(CSynapse& synapse)
    {
        m_listOfConnectedNeurons.emplace_back(synapse);
    }

    void SetSynapseInput(std::string id, float input)
    {
        for(auto& it: m_listOfConnectedNeurons)
        {
            if(id == it.GetID())
                it.SetInput(input);
        }
    }

    void SetSynapseWeight(std::string id, float weight)
    {
        for(auto& it: m_listOfConnectedNeurons)
        {
            if(id == it.GetID())
                it.SetWeight(weight);
        }
    }

    void SetBias(float bias)
    {
        m_bias = bias;
    }

    float GetOutput()
    {
        return m_output;
    }

private:
    float m_bias{0};
    float m_output{0};

    std::vector<CSynapse> m_listOfConnectedNeurons;

};


