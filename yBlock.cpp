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

//logic for parallel impedance
  //add in catch throw except, especially for .size()=0
void yBlock::set_z_complex()
{
    if(y_elements.size()==1)
    {
        for(const auto &[name,x_ptr] : y_elements) 
        {
            z_complex=(x_ptr->get_z_complex());
        }
    }
    else
    {
        std::complex<double> z_reciprocal_sum;
        for(const auto &[name,x_ptr] : y_elements) 
        {
            z_reciprocal_sum+=1.0/(x_ptr->get_z_complex());
        }
        z_complex=(1.0/z_reciprocal_sum);
  }
}

yBlock::yBlock(const std::string name_prmtr, std::unordered_map<std::string, std::shared_ptr<xBlock>> y_elements_prmtr) : xBlock(name_prmtr), y_elements(y_elements_prmtr)
{
    name=name_prmtr;
}

yBlock::yBlock(const yBlock&original) : xBlock(original)
{
    std::cout<<"Copy constructor for"<<name<<" called."<<std::endl;
    for(const auto &[y_element_name,y_elements_ptr] : original.y_elements) 
    {
        if(y_elements_ptr)
        { 
            y_elements[y_element_name]=y_elements_ptr;
        }
    }
}

yBlock::yBlock(yBlock &&temp) : xBlock(std::move(temp)), y_elements(std::move(temp.y_elements))
{
    std::cout<<"Move constructor for "<<name<<" called."<<std::endl;
}

//catch etc
yBlock &yBlock::operator=(const yBlock &other)
{
    std::cout<<"Copy assignment operator for "<<name<<" called."<<std::endl;
    if(this!=&other)
    {
        xBlock::operator=(other);
        y_elements.clear();
        for(const auto &[y_element_name,y_element_ptr] : other.y_elements) 
        {
            if(y_element_ptr)
            { 
                y_elements[y_element_name]=y_element_ptr;
            }
        }
    }
    return *this;
   
}

yBlock &yBlock::operator=(yBlock &&temp)
{
    std::cout<<"Move assignment operator for "<<name<<" called."<<std::endl;
    if(this!=&temp)
    {
        xBlock::operator=(std::move(temp));
        y_elements=std::move(temp.y_elements);
    }
    return *this;
}


void activate_y_block(yBlock &y_block, double omega)
{
    for(const auto &[name,y_element_ptr] : y_block.y_elements) 
    {
        if(y_element_ptr)
        { 
            y_block.activate_x_block(*y_element_ptr, omega);
        }
    }
    y_block.set_z_complex();
}


std::shared_ptr<xBlock> yBlock::find_element(const std::string &name)
{
    std::shared_ptr<xBlock> search_result{};
    search_result=find_element_algorithm(name, y_elements);
    return search_result;
}