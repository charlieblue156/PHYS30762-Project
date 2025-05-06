/*
Charlie Taylor - 29/04/25 - 11072486
xBlock class source file.
*/

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include<cmath>
#include<algorithm>
#include "XBlock.h"
#include "Component.h"
#include "YBlock.h"
#include "Circuit.h"

//Finds each instance of the name within a vector of ptrs to XBlocks
std::shared_ptr<XBlock> XBlock::find_element_algorithm(const std::string &name, const std::vector<std::shared_ptr<XBlock>> &vctr)
{
    std::shared_ptr<XBlock> search_result{};
    auto iterator=std::find_if(vctr.begin(), vctr.end(), [&name](const std::shared_ptr<XBlock> &element_ptr){return element_ptr->get_name()==name;});
    if(iterator!=vctr.end())
    {
        return *iterator;
    }
    for(const auto &element_ptr : vctr)
    {
        if(!element_ptr) continue;
        if(auto circuit_ptr=dynamic_cast<Circuit*>(element_ptr.get())) 
        {
            search_result=circuit_ptr->find_element_algorithm(name, circuit_ptr->get_circuit_elements());
            if(search_result!=nullptr) 
            {
                return search_result;
            }
        }
        else if(auto y_block_ptr=dynamic_cast<YBlock*>(element_ptr.get())) 
        {
            search_result=y_block_ptr->find_element_algorithm(name, y_block_ptr->get_y_elements());
            if(search_result!=nullptr) 
            {
                return search_result;
            }
        }
    }
    return nullptr;
}
//Removes each instance of name, in a vector of shared ptrs to XBlocks
void XBlock::remove_element_algorithm(const std::string &removal_name, std::vector<std::shared_ptr<XBlock>> &vctr)
{
    auto iterator=std::remove_if(vctr.begin(), vctr.end(), [&removal_name, this](const std::shared_ptr<XBlock> &element_ptr)
    {
        if(element_ptr&&element_ptr->get_name()==removal_name)
        {
            std::cout<<removal_name<<" removed from "<<this->get_name()<<"."<<std::endl;
            return true;
        }
        return false;
    });
    vctr.erase(iterator, vctr.end());

    for(auto &element_ptr : vctr)
    {
        if(!element_ptr) continue;
        if(auto circuit_ptr=dynamic_cast<Circuit*>(element_ptr.get())) 
        {
            circuit_ptr->remove_element_algorithm(removal_name, circuit_ptr->circuit_elements);
        } 
        else if(auto y_block_ptr = dynamic_cast<YBlock*>(element_ptr.get())) 
        {
            y_block_ptr->remove_element_algorithm(removal_name, y_block_ptr->y_elements);
        }
    }
}
XBlock::XBlock(const XBlock &other) : z_complex(other.z_complex), name(other.name)
{
    std::cout<<"Calling copy constructor for "<<this->name<<"."<<std::endl;
}
XBlock::XBlock(XBlock &&temp) : z_complex(std::move(temp.z_complex)), name(std::move(temp.name))
{
    std::cout<<"Calling move constructor for "<<this->name<<"."<<std::endl;
}
XBlock &XBlock::operator=(const XBlock &other)
{
    if(this!=&other)
    {
        std::cout<<"Calling copy assignment operator for "<<this->name<<"."<<std::endl;
        name=other.name;
        z_complex=other.z_complex;
    }
    return *this;
}
XBlock &XBlock::operator=(XBlock &&temp)
{
    if(this!=&temp)
    {
        std::cout<<"Calling move assignment operator for "<<this->name<<"."<<std::endl;
        name=std::move(temp.name);
        z_complex=std::move(temp.z_complex);
    }
    return *this;
}
//Applies a dynamic cast for the derived classes, to activate each class type accordingly
void XBlock::activate_x_block(XBlock &x_block, double omega)
{
    if(auto component=dynamic_cast<Component*>(&x_block)) 
    {
        component->activate_component(omega);
    }
    else if(auto y_block=dynamic_cast<YBlock*>(&x_block)) 
    {
        y_block->activate_y_block(omega);
    }
    else if(auto identified_circuit=dynamic_cast<Circuit*>(&x_block)) 
    {
        identified_circuit->activate_circuit();
    }
}
void XBlock::print_xblock_data()
{
    std::cout<<'\n'<<"Printing data for "<<this->name<<"."<<std::endl;
    std::cout<<"Complex impedance: "<<this->get_z_real()<<(this->get_z_imaginary()<0?" ":" +")<<this->get_z_imaginary()<<"i [Ohm]."<<std::endl;
    std::cout<<"Magnitude: "<<this->get_z_magnitude()<<" [Ohm]."<<std::endl;
    std::cout<<"Phase: "<<this->get_z_phase()<<" [rad]."<<std::endl;
}




