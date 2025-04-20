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


void xBlock::activate_x_block(xBlock &x_block, double omega)
{
    if(auto component=dynamic_cast<Component*>(&x_block)) 
    {
        activate_component(*component, omega);
    }
    else if(auto y_block=dynamic_cast<yBlock*>(&x_block)) 
    {
        activate_y_block(*y_block, omega);
    }
    else if(auto identified_circuit=dynamic_cast<Circuit*>(&x_block)) 
    {
        identified_circuit->activate_circuit();
    }
}


void xBlock::print_data()
{
    //std::cout<<'\n'<<"Printing data for "<<this->get_name()<<"."<<std::endl;
    if(this->get_z_phase()<0)
    {
        std::cout<<"Complex impedance: "<<this->get_z_real()<<" "<<this->get_z_imaginary()<<"i Ω."<<std::endl;
    }
    else
    {
        std::cout<<"Complex impedance: "<<this->get_z_real()<<" +"<<this->get_z_imaginary()<<"i Ω."<<std::endl;
    }
    std::cout<<"Magnitude: "<<this->get_z_magnitude()<<" Ω."<<std::endl;
    std::cout<<"Phase: "<<this->get_z_phase()<<" [rad]."<<std::endl;
}

std::shared_ptr<xBlock> xBlock::find_element_algorithm(const std::string &name, const std::unordered_map<std::string, std::shared_ptr<xBlock>> &map)
{
    std::shared_ptr<xBlock> search_result{};
    auto iterator=map.find(name);
    if(iterator!=map.end()) 
    {
        return iterator->second;
    } 
    else 
    {
        for(const auto &[element_name, element_ptr] : map) 
        {
            if(auto y_block_ptr=dynamic_cast<yBlock*>(element_ptr.get()))
            {
                search_result=y_block_ptr->find_element(name);
                if (search_result!=nullptr) 
                {
                  return search_result;
                }
            }
            else if(auto circuit_ptr=dynamic_cast<Circuit*>(element_ptr.get())) 
            {
                search_result=circuit_ptr->find_element(name);
                if(search_result!=nullptr) 
                {
                    return search_result;
                }
            }
        }
        return nullptr;
    }
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