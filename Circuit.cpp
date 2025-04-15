#include<iostream>
#include<string>
#include<vector>
#include<memory>

#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"



Circuit::Circuit(const Circuit&original) : omega{original.omega}
{
    for(const auto &circuit_element_ptr : original.circuit_elements) 
    {
        if(circuit_element_ptr)
        { 
            circuit_elements.push_back(circuit_element_ptr);
        }
    }
}


//activate each components impedance via frequency 
/*the circuit_elements vector can contain components, y_blocks, or circuits. Given each occurence, 
activate each x_block. ie iterate through circuit_elements, have an overloaded function that will 
iterate again through the y_block, or circuit vectors, activating the impedance for each function.

The activation of y_block and circuit iterators should be in their classes to access y_elements and circuit_elements respectively.*/


void activate_circuit(Circuit &circuit)
{
    for(const auto &circuit_element_ptr : circuit.circuit_elements) 
    {
        circuit.activate_x_block(*circuit_element_ptr, circuit);
    }
}

/*
void Circuit::activate_circuit()
{
    for(const auto &circuit_element_ptr: this->circuit_elements)
    {
        activate_x_block(*circuit_element_ptr);
    }
}
*/

