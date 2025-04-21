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

void Circuit::alloc_validation(std::string name_prmtr, std::unordered_map<std::string, std::shared_ptr<xBlock>> circuit_elements_prmtr)
{
    try
    {
        circuit_elements=circuit_elements_prmtr;
    }
    catch(std::bad_alloc &memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name_prmtr<<"."<<std::endl;
    }
}

Circuit::Circuit(const std::string name_prmtr, double omega_prmtr, std::unordered_map<std::string, std::shared_ptr<xBlock>> circuit_elements_prmtr) : xBlock(name_prmtr), omega{omega_prmtr}
{
    alloc_validation(name_prmtr, circuit_elements_prmtr);
}

Circuit::Circuit(const Circuit&original) : xBlock{original}, omega{original.omega}
{
    std::cout<<"Copy constructor for "<<name<<" called."<<std::endl;
    alloc_validation(original.name, original.circuit_elements);
}

Circuit::Circuit(Circuit &&temp): xBlock(std::move(temp)), omega(std::move(temp.omega))
{
    std::cout<<"Move constructor for "<<name<<" called."<<std::endl;
    circuit_elements.clear();
    alloc_validation(name, temp.circuit_elements);
}

Circuit &Circuit::operator=(const Circuit &other)
{
    std::cout<<"Copy assignment operator for "<<name<<" called."<<std::endl;
    if(this!=&other)
    {
        xBlock::operator=(other);
        omega=other.omega;
        alloc_validation(other.name, other.circuit_elements);
    }
    return *this;
}

Circuit &Circuit::operator=(Circuit &&temp)
{
    std::cout<<"Move assignment operator for "<<name<<" called."<<std::endl;
    circuit_elements.clear();
    if(this!=&temp)
    {
        xBlock::operator=(std::move(temp));
        omega=std::move(temp.omega);
        alloc_validation(name, temp.circuit_elements);
    }
    return *this;
}

void Circuit::activate_circuit()
{
    std::cout<<'\n'<<"Activating "<<this->get_name()<<"."<<std::endl;
    for(const auto &[name,circuit_element_ptr]: this->circuit_elements) 
    {
        if(circuit_element_ptr)
            {
                this->activate_x_block(*circuit_element_ptr, omega);
            }
    }
    this->set_z_complex();
}




void Circuit::find_element(const std::string &name)
{
    std::cout<<'\n'<<"Searching for "<<name<<" in "<<this->get_name()<<"."<<std::endl;
    std::shared_ptr<xBlock> search_result{};
    search_result=find_element_algorithm(name, this->get_circuit_elements());
    if(search_result==nullptr) 
    {
        std::cout<<name<<" not found in "<<this->get_name()<<"."<<std::endl;
    }
    else
    {
        std::cout<<name<<" found in "<<this->get_name()<<"."<<std::endl;
        search_result->print_xblock_data();
    }
}

void Circuit::print_circuit_elements()
{
    std::cout<<'\n'<<"Printing circuit elements for "<<this->get_name()<<"."<<std::endl;
    for(const auto &[name,circuit_element_ptr] : this->circuit_elements) 
    {
        if(circuit_element_ptr)
        { 
            circuit_element_ptr->print_xblock_data();
        }
    }
}


void Circuit::add_circuit_element(std::string name, std::shared_ptr<xBlock> circuit_element_ptr)
{
    try
    {
        circuit_elements.insert({name, circuit_element_ptr});
    }
    catch(const std::bad_alloc& memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name<<"."<<std::endl;
    }
}
void Circuit::remove_circuit_element(std::string name, std::shared_ptr<xBlock> circuit_element_ptr)
{
    auto iterator=circuit_elements.find(name);
    if (iterator!=circuit_elements.end()) 
    {
        circuit_elements.erase(iterator);
        std::cout<<name<<" removed from "<<this->get_name()<<"."<<std::endl;
    } 
    else 
    {
        std::cout<<name<<" not found in "<<this->get_name()<<"."<<std::endl;
    }

}
void Circuit::add_circuit_elements(std::string name, std::unordered_map<std::string, std::shared_ptr<xBlock>> circuit_elements_prmtr)
{
    try
    {
        circuit_elements.insert(circuit_elements_prmtr.begin(), circuit_elements_prmtr.end());
    }
    catch(const std::bad_alloc& memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name<<"."<<std::endl;
    }
}

void Circuit::clear_circuit_elements()
{
    circuit_elements.clear();
    std::cout<<this->get_name()<<" circuit elements cleared."<<std::endl;
    z_complex=0.0;
}