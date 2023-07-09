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

#include <iostream>
#include <cmath>


// ##############################################################################
// -- PUBLIC --
// ##############################################################################


void CNeuralCluster::Setup(int numOfInputs, int numOfHiddenLayers, int numOfNeuronsPerHiddenLayer, int numOfOutputs)
{
    // ##############################################################################
    // -- Add the neurons --
    // ##############################################################################
    // Add the layers
    // Nothing to be done for Input

    // hidden
    for(int index_hidden_layer = 0; index_hidden_layer < numOfHiddenLayers; ++index_hidden_layer) {

        SLayerContainer hidden_pack;
        hidden_pack.layer_name = "Hidden_" + std::to_string(index_hidden_layer+1);
        hidden_pack.layer_type = ENeuronType::EHidden;
       // index_hidden_layer++;
        hidden_pack.layer_number = index_hidden_layer+1;
        for(int index_hidden_num = 0; index_hidden_num < numOfNeuronsPerHiddenLayer; ++index_hidden_num) {

            std::string n_name = "L" + std::to_string(index_hidden_layer+1) + "N" + std::to_string(index_hidden_num+1);
            std::shared_ptr<CNeuron> lNeuronPtr = std::make_shared<CNeuron>(n_name, hidden_pack.layer_type);
            lNeuronPtr->SetNumber(index_hidden_num+1);
            lNeuronPtr->SetValue(0);

            hidden_pack.node_list.emplace_back(std::move(lNeuronPtr));
        }
        layer_list.emplace_back(hidden_pack);
    }

    // output
    SLayerContainer output_pack;
    output_pack.layer_name = "Output_1"; // only ever one output layer
    output_pack.layer_type = ENeuronType::EOutput;
    output_pack.layer_number = 1;
    for(int index_output = 0; index_output < numOfOutputs; ++index_output) {

        std::string n_name = "Output_" + std::to_string(index_output+1); // start naming at one, not zero

        std::shared_ptr<CNeuron> lPtr = std::make_shared<CNeuron>(
                    n_name,
                    output_pack.layer_type);

        lPtr->SetNumber(index_output+1);
        lPtr->SetValue(0);

        output_pack.node_list.emplace_back(std::move(lPtr));
    }
    layer_list.emplace_back(output_pack);

    // ##############################################################################
    // -- Add the synapses --
    // ##############################################################################
    int layer_list_index = 0;
    for(auto& it_L : layer_list) {

        switch(it_L.layer_type)
        {
            ///\ todo: remove switch
            case ENeuronType::EHidden:
            case ENeuronType::EOutput:
            {                
                    for(auto& it_neuron : it_L.node_list) {
                        std::string s_name;

                        // connection between the first hidden layer and the inputs
                        if(0 == layer_list_index) {
                            for(int index_input_layer = 0; index_input_layer < numOfInputs; ++index_input_layer) {
                                s_name = "HL" + std::to_string(it_L.layer_number)
                                        + "N" + std::to_string(it_neuron->GetNumber())
                                        + "_S" + std::to_string(index_input_layer+1) + std::to_string(it_neuron->GetNumber());
                                std::static_pointer_cast<CNeuron>(it_neuron)->AddSynapse(s_name);
                            } // for numOfInputs
                        } else {
                            for(auto& it_neuron_prev : layer_list.at(layer_list_index-1).node_list) {
                                s_name = "OL" + std::to_string(it_L.layer_number)
                                        + "N" + std::to_string(it_neuron->GetNumber())
                                        + "_S" + std::to_string(it_neuron_prev->GetNumber()) + std::to_string(it_neuron->GetNumber());
                                std::static_pointer_cast<CNeuron>(it_neuron)->AddSynapse(s_name);
                            } // for
                        } // if
                    } // for
                break;
            } // case
            default:
                // dont care
                break;
        } // switch
        layer_list_index++;
    }
}

void CNeuralCluster::Train(std::vector<std::vector<int>> input_data)
{
// ##############################################################################
// -- Training --
// ##############################################################################

    float errors[4] = {0,0,0,0};
    int epoch = 0;

    for(int training_index = 0; training_index < l_training_loops; ++training_index)
    {

// ##############################################################################
// -- Forward propogation --

        int input_data_index = 0;
        for(const auto& it_input_data : input_data)
        {
            // Add the inputs
            int layer_list_index = 0;
            for(auto& it_ll : layer_list) {
                // layers
                for(auto& it_neuron : it_ll.node_list) {
                    // run through this node's synapse list
                    for(int nodeSynapseIndex = 0; nodeSynapseIndex < it_neuron->GetNumberOfSynapses(); ++nodeSynapseIndex) {
                        if(0 == layer_list_index) {
                            // Add the external inputs
                            ///\ todo: add a limit for number of external inputs
                            if(true) {
                                //
                                it_neuron->SetSynapseInput(nodeSynapseIndex, it_input_data.at(nodeSynapseIndex));
                            }
                        } else {
                            // other hidden/output layers, for this we need to get the outputs of the previous layer
                            auto& ref_neuron_prev = layer_list.at(layer_list_index-1).node_list.at(nodeSynapseIndex);
                            it_neuron->SetSynapseInput(nodeSynapseIndex, ref_neuron_prev->GetOutput());

                        } // if first layer or not
                    } // nodeSynapseIndex

                    // After each node has its inputs, PROCESS IT!!
                    it_neuron->Process();

                } // each neuron
                layer_list_index++;
            } // each layer

// ##############################################################################
// -- Get otuput errors --
            ///\ todo : fix the references of the nodes for both layer_list and input_data
            auto ref_layer_list = layer_list.end() -1;
            float error = ref_layer_list->node_list.at(0)->GetOutput() - it_input_data.at(2);
            errors[input_data_index] = error;

// ##############################################################################
// -- Back propogation --

            // update the derivatives
            int layer_list_last_pos = layer_list.size() -1; // last layer
            for(layer_list_index = layer_list_last_pos; layer_list_index > 0; --layer_list_index) {
                // go through the layers

                for(auto& it_neuron : layer_list.at(layer_list_index).node_list) {
                    // go through the neurons

                    // ## OUTPUT
                    if(ENeuronType::EOutput == it_neuron->GetType()) {

                        it_neuron->SetOutputDerive(error);
                        for(int nodeSynapseIndex = 0; nodeSynapseIndex < it_neuron->GetNumberOfSynapses(); ++nodeSynapseIndex) {
                            // go through the synapses

                            auto ref_neuron_prev = layer_list.at(layer_list_index-1).node_list.at(nodeSynapseIndex);
                            it_neuron->UpdateOutputSynapseWeight(nodeSynapseIndex, ref_neuron_prev->GetOutput());
                        }
                        it_neuron->UpdateNeuronBias();

                    } else if(ENeuronType::EHidden == it_neuron->GetType()) {

                        // ## HIDDEN
                        for(const auto& it_after_node_list : layer_list.at(layer_list_index+1).node_list) {
                            // go through the synapses
                            for(int nodeSynapseIndex = 0; nodeSynapseIndex < it_after_node_list->GetNumberOfSynapses(); ++nodeSynapseIndex) {
                                it_neuron->SetHiddenDerive(it_after_node_list->GetDerive(), it_after_node_list->GetSynapseWeight(nodeSynapseIndex));
                            }
                        }
                        it_neuron->UpdateHiddenSynapseWeight();

                    } else {
                        std::cout << "ERROR" << std::endl;
                    }
                }
            }

            // Update the weights (inputs and bias)

            input_data_index++;
        } // range it_input_data

// ##############################################################################
// -- Calculate mean errors --

        // add up errors
        float rmse_error = sqrt((   pow(errors[0], 2) +
                                    pow(errors[1], 2) +
                                    pow(errors[2], 2) +
                                    pow(errors[3], 2) / 4));

        // error too high
        if (epoch++ > 5000 && rmse_error > 0.5)
        {
            ResetAllNodes();
            epoch = 0;
        }

    } // training_index

}

bool CNeuralCluster::Test(std::vector<std::vector<int>> input_data)
{
    bool result = false;
    for(const auto& it_input_data : input_data)
    {

        // Add the inputs
        int layer_list_index = 0;
        for(auto& it_ll : layer_list) {
            // layers
            for(auto& it_neuron : it_ll.node_list) {
                // run through this node's synapse list
                for(int nodeSynapseIndex = 0; nodeSynapseIndex < it_neuron->GetNumberOfSynapses(); ++nodeSynapseIndex) {
                    if(0 == layer_list_index) {
                        // Add the external inputs
                        ///\ todo: add a limit for number of external inputs
                        if(true) {
                            //
                            it_neuron->SetSynapseInput(nodeSynapseIndex, it_input_data.at(nodeSynapseIndex));
                        }
                    } else {
                        // other hidden/output layers, for this we need to get the outputs of the previous layer
                        auto& ref_neuron_prev = layer_list.at(layer_list_index-1).node_list.at(nodeSynapseIndex);
                        it_neuron->SetSynapseInput(nodeSynapseIndex, ref_neuron_prev->GetOutput());

                    } // if first layer or not
                } // nodeSynapseIndex

                // After each node has its inputs, PROCESS IT!!
                it_neuron->Process();

            } // each neuron
            layer_list_index++;
        } // each layer



        // check the results
        int layer_list_last_pos = layer_list.size() -1; // last layer
        float result = layer_list.at(layer_list_last_pos).node_list.at(0)->GetOutput();

        if(it_input_data.at(2) == round(result)) {
            result = true;
        }
        std::cout << "Output = " << result << "(" << round(result) << "), expected output = " << it_input_data.at(2) << std::endl;
    }
    return result;
}

// ##############################################################################
// -- PRIVATE --
// ##############################################################################
void CNeuralCluster::ResetAllNodes()
{
    for(const auto& it_lay: layer_list) {
        for(const auto& it_node: it_lay.node_list) {
            it_node->Reset();
        }
    }
}
