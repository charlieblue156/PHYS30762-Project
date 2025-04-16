#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
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
        for(const auto &x_ptr : y_elements) 
        {
            z_complex=(x_ptr->get_z_complex());
        }
    }
    else
    {
        std::complex<double> z_reciprocal_sum;
        for(const auto &x_ptr : y_elements) 
        {
            z_reciprocal_sum+=1.0/(x_ptr->get_z_complex());
        }
        z_complex=(1.0/z_reciprocal_sum);
  }
}



yBlock::yBlock(const yBlock&original) : xBlock(original)
{
    for(const auto &y_elements_ptr : original.y_elements) 
    {
        if(y_elements_ptr)
        { 
            y_elements.push_back(y_elements_ptr);
        }
    }
}

//catch etc
yBlock &yBlock::operator=(const yBlock &other)
{
    if(this!=&other)
    {
        y_elements.clear();
        for(const auto &y_element_ptr : other.y_elements) 
        {
            if(y_element_ptr)
            { 
                y_elements.push_back(y_element_ptr);
            }
        }
    }
    return *this;
   
}

yBlock &yBlock::operator=(yBlock &&temp)
{
    if(this!=&temp)
    {
        y_elements=std::move(temp.y_elements);
    }
    return *this;
}


void activate_y_block(yBlock &y_block, Circuit circuit)
{
    for(const auto &y_element_ptr : y_block.y_elements) 
    {
        y_block.activate_x_block(*y_element_ptr, circuit);
    }
    y_block.set_z_complex();
}