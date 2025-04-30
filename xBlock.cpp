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
#include "xBlock.h"
#include "Component.h"
#include "yBlock.h"
#include "Circuit.h"

std::shared_ptr<xBlock> xBlock::find_element_algorithm(const std::string &name, const std::vector<std::shared_ptr<xBlock>> &vctr)
{
    std::shared_ptr<xBlock> search_result{};
    auto iterator=std::find_if(vctr.begin(), vctr.end(), [&name](const std::shared_ptr<xBlock> &element_ptr){return element_ptr->get_name()==name;});
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
        else if(auto y_block_ptr=dynamic_cast<yBlock*>(element_ptr.get())) 
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
xBlock::xBlock(const xBlock &other) : z_complex(other.z_complex), name(other.name)
{
    std::cout<<"Calling copy constructor for "<<this->get_name()<<"."<<std::endl;
}
xBlock::xBlock(xBlock &&temp) : z_complex(std::move(temp.z_complex)), name(std::move(temp.name))
{
    std::cout<<"Calling move constructor for "<<this->get_name()<<"."<<std::endl;
}
xBlock &xBlock::operator=(const xBlock &other)
{
    if(this!=&other)
    {
        std::cout<<"Calling copy assignment operator for "<<this->get_name()<<"."<<std::endl;
        name=other.name;
        z_complex=other.z_complex;
    }
    return *this;
}
xBlock &xBlock::operator=(xBlock &&temp)
{
    if(this!=&temp)
    {
        std::cout<<"Calling move assignment operator for "<<this->get_name()<<"."<<std::endl;
        name=std::move(temp.name);
        z_complex=std::move(temp.z_complex);
    }
    return *this;
}
void xBlock::activate_x_block(xBlock &x_block, double omega)
{
    if(auto component=dynamic_cast<Component*>(&x_block)) 
    {
        component->activate_component(*component, omega);
    }
    else if(auto y_block=dynamic_cast<yBlock*>(&x_block)) 
    {
        y_block->activate_y_block(*y_block, omega);
    }
    else if(auto identified_circuit=dynamic_cast<Circuit*>(&x_block)) 
    {
        identified_circuit->activate_circuit();
    }
}
void xBlock::print_xblock_data()
{
    std::cout<<'\n'<<"Printing data for "<<this->get_name()<<"."<<std::endl;
    std::cout<<"Complex impedance: "<<this->get_z_real()<<(this->get_z_imaginary()<0?" ":" +")<<this->get_z_imaginary()<<"i [Ohm]."<<std::endl;
    std::cout<<"Magnitude: "<<this->get_z_magnitude()<<" [Ohm]."<<std::endl;
    std::cout<<"Phase: "<<this->get_z_phase()<<" [rad]."<<std::endl;
}




