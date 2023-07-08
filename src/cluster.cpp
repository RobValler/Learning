/*****************************************************************
 * Copyright (C) 2017-2023 Robert Valler - All rights reserved.
 *
 * This file is part of the project: Learning
 *
 * This project can not be copied and/or distributed
 * without the express permission of the copyright holder
 *****************************************************************/

#include "cluster.h"

#include "neuron.h"

#include <string>

void CNeuralCluster::Init()
{
    SInputCluster input;
    input.numOfInputs = 2;
    input.numOfHiddenLayers = 1;
    input.numOfNeuronsPerHiddenLayer = 2;
    input.numOfOutputs = 1;
    Setup(input);
}

void CNeuralCluster::Setup(SInputCluster input)
{
    // ##############################################################################
    // -- Add the neurons --
    // ##############################################################################
    // Add the layers
    // input
    SPack intput_pack;
    intput_pack.layer_name = "Input_1"; // only ever one input layer
    intput_pack.layer_type = ENeuronType::EInput;
    intput_pack.layer_number = 1;
    for(int index_input_layer = 0; index_input_layer < input.numOfInputs; ++index_input_layer) {

        SPackInput pack_input;
        pack_input.number = index_input_layer+1;
        pack_input.value = 0; // initial value
        intput_pack.input_list.emplace_back(std::move(pack_input));
    }
    m_cluster.layer_list.emplace_back(intput_pack);

    // hidden
    for(int index_hidden_layer = 0; index_hidden_layer < input.numOfHiddenLayers; ++index_hidden_layer) {

        SPack hidden_pack;
        hidden_pack.layer_name = "Hidden_" + std::to_string(index_hidden_layer+1);
        hidden_pack.layer_type = ENeuronType::EHidden;
        index_hidden_layer++;
        hidden_pack.layer_number = index_hidden_layer;
        for(int index_hidden_num = 0; index_hidden_num < input.numOfNeuronsPerHiddenLayer; ++index_hidden_num) {

            std::string n_name = "Hidden_L" + std::to_string(index_hidden_layer) + "N" + std::to_string(index_hidden_num+1);
            SPackNeuron pack_neuron;
            pack_neuron.number = index_hidden_num+1;
            pack_neuron.pneuron = std::make_shared<CNeuron>(n_name, hidden_pack.layer_type);
            hidden_pack.neuron_list.emplace_back(std::move(pack_neuron));
        }
        m_cluster.layer_list.emplace_back(hidden_pack);
    }

    // output
    SPack output_pack;
    output_pack.layer_name = "Output_1"; // only ever one output layer
    output_pack.layer_type = ENeuronType::EOutput;
    output_pack.layer_number = 1;
    for(int index_output = 0; index_output < input.numOfOutputs; ++index_output) {

        std::string n_name = "Output_" + std::to_string(index_output+1); // start naming at one, not zero
        SPackNeuron pack_neuron;
        pack_neuron.number = index_output+1;
        pack_neuron.pneuron = std::make_shared<CNeuron>(n_name, output_pack.layer_type);
        output_pack.neuron_list.emplace_back(std::move(pack_neuron));
    }
    m_cluster.layer_list.emplace_back(output_pack);

    // ##############################################################################
    // -- Add the synapses --
    // ##############################################################################
    int layer_list_index = 0;
    for(auto& it_L : m_cluster.layer_list) {

        switch(it_L.layer_type)
        {
            case ENeuronType::EHidden:
            {
                if(1 == it_L.layer_number) {
                    for(auto& it_N : it_L.neuron_list) {
                        for(auto& prev_L : m_cluster.layer_list.at(layer_list_index-1).input_list) {

                            std::string s_name = "W" + std::to_string(prev_L.number) + std::to_string(it_N.number);
                            it_N.pneuron->AddSynapse(s_name);

                        } // for
                    } // for
                } else {
                    for(auto& it_N : it_L.neuron_list) {
                        for(auto& prev_L : m_cluster.layer_list.at(layer_list_index-1).neuron_list) {

                            std::string s_name = "W" + std::to_string(prev_L.number) + std::to_string(it_N.number);
                            it_N.pneuron->AddSynapse(s_name);

                        } // for
                    } // for
                }
                break;
            } // case
            case ENeuronType::EOutput:
            {
                for(auto& it_N : it_L.neuron_list) {
                    for(auto& prev_L : m_cluster.layer_list.at(layer_list_index-1).neuron_list) {

                        // create the synaps and register it
                        std::string s_name = "W" + std::to_string(prev_L.number) + std::to_string(it_N.number);
                        it_N.pneuron->AddSynapse(s_name);

                        // link the synaps to the relevant neuron of the previous layer
                        ///\ todo : add this




                    } // for
                } // for
                break;
            }
            default:
                // dont care
                break;
        }
        layer_list_index++;
    }
}
