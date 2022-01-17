


#include "neuron.h"

#include <stdlib.h>

void CNeuron::Process()
{
    // linear combination
    float total = 0.0f;
    for(const auto& it: m_listOfConnectedNeurons)
    {
        //m_output += m_bias * (it.GetInput() * it.GetWeight());
        total += (it.GetInput() * it.GetWeight());
    }

    //activation - sigmoidal
    m_output = total / (1 + abs(total));
}

