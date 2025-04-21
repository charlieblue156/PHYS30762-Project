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

void yBlock::alloc_validation(std::string name_prmtr, std::unordered_map<std::string, std::shared_ptr<xBlock>> y_elements_prmtr)
{
    try
    {
        y_elements=y_elements_prmtr;
    }
    catch(std::bad_alloc &memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name_prmtr<<"."<<std::endl;
    }
}

yBlock::yBlock(const std::string name_prmtr, std::unordered_map<std::string, std::shared_ptr<xBlock>> y_elements_prmtr) : xBlock(name_prmtr)
{
    alloc_validation(name_prmtr, y_elements_prmtr);
}

yBlock::yBlock(const yBlock&original) : xBlock(original)
{
    std::cout<<"Copy constructor for"<<name<<" called."<<std::endl;
    alloc_validation(original.name, original.y_elements);
}

yBlock::yBlock(yBlock &&temp) : xBlock(std::move(temp))
{
    std::cout<<"Move constructor for "<<name<<" called."<<std::endl;
    alloc_validation(name, temp.y_elements);
}

//catch etc
yBlock &yBlock::operator=(const yBlock &other)
{
    std::cout<<"Copy assignment operator for "<<name<<" called."<<std::endl;
    if(this!=&other)
    {
        xBlock::operator=(other);
        y_elements.clear();
        alloc_validation(other.name, other.y_elements);
    }
    return *this;
   
}

yBlock &yBlock::operator=(yBlock &&temp)
{
    std::cout<<"Move assignment operator for "<<name<<" called."<<std::endl;
    if(this!=&temp)
    {
        xBlock::operator=(std::move(temp));
        alloc_validation(name, temp.y_elements);
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

/*
std::shared_ptr<xBlock> yBlock::find_element(const std::string &name)
{
    std::shared_ptr<xBlock> search_result{};
    search_result=find_element_algorithm(name, y_elements);
    return search_result;
}
    */

void yBlock::print_yelements()
{
    std::cout<<'\n'<<"Printing yBlock elements for "<<this->get_name()<<"."<<std::endl;
    for(const auto &[name,y_element_ptr] : y_elements) 
    {
        if(y_element_ptr)
        { 
            y_element_ptr->print_xblock_data();
        }
    }
}


void yBlock::add_y_element(std::string name, std::shared_ptr<xBlock> y_element_ptr)
{
    try
    {
        y_elements.insert({name, y_element_ptr});
    }
    catch(const std::bad_alloc& memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name<<"."<<std::endl;
    }
}

void yBlock::remove_y_element(std::string name, std::shared_ptr<xBlock> y_element_ptr)
{
    auto iterator=y_elements.find(name);
    if(iterator!=y_elements.end()) 
    {
        y_elements.erase(iterator);
    } 
    else 
    {
        std::cerr<<name<<" not found in "<<this->get_name()<<"."<<std::endl;
    }
}

void yBlock::add_y_elements(std::string name, std::unordered_map<std::string, std::shared_ptr<xBlock>> y_elements_prmtr)
{
    try
    {
        y_elements.insert(y_elements_prmtr.begin(), y_elements_prmtr.end());
    }
    catch(const std::bad_alloc& memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name<<"."<<std::endl;
    }
}

void yBlock::clear_y_elements()
{
    y_elements.clear();
    std::cout<<"yBlock elements cleared."<<std::endl;
    z_complex=0.;
}
