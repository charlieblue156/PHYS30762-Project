#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include<unordered_map>

#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"


void Circuit::set_z_complex()
{
    for(const auto& [name,circuit_elements_ptr] : circuit_elements) 
    {
        if(circuit_elements_ptr)
        { 
            z_complex+=circuit_elements_ptr->get_z_complex();
        }
    }
}


Circuit::Circuit(const Circuit&original) : xBlock{original}, omega{original.omega}
{
    for(const auto &[name,circuit_element_ptr] : original.circuit_elements) 
    {
        circuit_elements[name]=circuit_element_ptr;
    }
}


Circuit &Circuit::operator=(const Circuit &other)
{
    if(this!=&other)
    {
        xBlock::operator=(other);
        omega=other.omega;
        circuit_elements.clear();
        for(const auto &[name,circuit_ptr] : other.circuit_elements) 
        {
            circuit_elements[name]=circuit_ptr;
        }
    }
    return *this;
}

Circuit &Circuit::operator=(Circuit &&temp)
{
    if(this!=&temp)
    {
        xBlock::operator=(std::move(temp));
        omega=std::move(temp.omega);
        circuit_elements=std::move(temp.circuit_elements);
    }
    return *this;
}

void Circuit::activate_circuit()
{
    std::cout<<"Activating "<<this->get_name()<<"."<<std::endl;
    for(const auto &[name,circuit_element_ptr]: this->circuit_elements) 
    {
        if(circuit_element_ptr)
            {
                this->activate_x_block(*circuit_element_ptr, omega);
            }
    }
    this->set_z_complex();
}


std::shared_ptr<xBlock> Circuit::find_element(const std::string &name)
{
    std::cout<<"Searching for "<<name<<" in "<<this->get_name()<<"."<<std::endl;
    std::shared_ptr<xBlock> search_result{};
    search_result=find_element_algorithm(name, this->get_circuit_elements());
    if(search_result==nullptr) 
    {
        std::cout<<name<<" not found in "<<this->get_name()<<"."<<std::endl;
    }
    else
    {
        std::cout<<name<<" found in "<<this->get_name()<<"."<<std::endl;
        search_result->print_data();
    }
    return search_result;
}