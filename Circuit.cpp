#include<iostream>
#include<string>
#include<vector>
#include<memory>

#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"


void Circuit::set_z_complex()
{
    for(const auto& circuit_elements_ptr : circuit_elements) 
    {
        if(circuit_elements_ptr)
        { 
            z_complex+=circuit_elements_ptr->get_z_complex();
        }
    }
}


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

Circuit &Circuit::operator=(const Circuit &other)
{
    if(this!=&other)
    {
        circuit_elements.clear();
        for(const auto &circuit_ptr : other.circuit_elements) 
        {
            if(circuit_ptr)
            { 
                circuit_elements.push_back(circuit_ptr);
            }
        }
    }
    return *this;
}

Circuit &Circuit::operator=(Circuit &&temp)
{
    if(this!=&temp)
    {
        circuit_elements=std::move(temp.circuit_elements);
    }
    return *this;
}

void activate_circuit(Circuit &circuit)
{
    for(const auto &circuit_element_ptr : circuit.circuit_elements) 
    {
        circuit.activate_x_block(*circuit_element_ptr, circuit);
    }
    circuit.set_z_complex();
}



