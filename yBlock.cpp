/*
Charlie Taylor - 29/04/25 - 11072486
yBlock class source file.
*/

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include<fstream>
#include<algorithm>
#include "xBlock.h"
#include "Component.h"
#include "yBlock.h"
#include "Circuit.h"

void yBlock::activate_y_block(double omega)
{
    for(const auto &y_element_ptr : this->y_elements) 
    {
        if(y_element_ptr)
        { 
            this->activate_x_block(*y_element_ptr, omega);
        }
    }
    try
    {
        this->set_z_complex();
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<<e.what()<<'\n';
    }
}
void yBlock::set_z_complex()
{

    if(y_elements.empty())
    {
        throw std::invalid_argument(this->get_name()+" has no elements.");
    }
    if(y_elements.size()==1)
    {
        for(const auto &x_ptr : y_elements) 
        {
            if(x_ptr->get_z_complex()!=(0.0, 0.0))
            {
                z_complex=(x_ptr->get_z_complex());
            }

        }
    }
    else
    {
        std::complex<double> z_reciprocal_sum;
        for(const auto &x_ptr : y_elements) 
        {
            if(x_ptr->get_z_complex()!=(0.0, 0.0))
            {
                z_reciprocal_sum+=1.0/(x_ptr->get_z_complex());
            }
        }
        z_complex=(1.0/z_reciprocal_sum);
    }
}
void yBlock::allocate(std::string name_prmtr, std::shared_ptr<xBlock> y_element_prmtr)
{
    try
    {
        validate_y_element(y_element_prmtr);
        y_elements.push_back(y_element_prmtr);
    }
    catch(std::bad_alloc &memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name_prmtr<<"."<<std::endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<<e.what()<<std::endl;
    }
}
void yBlock::allocate(std::string name_prmtr, std::vector<std::shared_ptr<xBlock>> y_elements_prmtr)
{
    try
    {
        for(const auto &y_element_ptr: y_elements_prmtr) 
        {
            validate_y_element(y_element_ptr);
            y_elements.push_back(y_element_ptr);
        }
    }
    catch(std::bad_alloc &memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name_prmtr<<"."<<std::endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<<e.what()<<std::endl;
    }
}
void yBlock::validate_y_element(std::shared_ptr<xBlock> y_element_ptr)
{
    if(!y_element_ptr) 
    {
        throw std::invalid_argument("Null pointer passed to "+name+".");
    }
}
yBlock::yBlock(const yBlock&original) : xBlock(original)
{
    y_elements.clear();
    allocate(original.name, original.y_elements);
}
yBlock::yBlock(yBlock &&temp) : xBlock(std::move(temp))
{
    allocate(temp.name, temp.y_elements);
}
yBlock &yBlock::operator=(const yBlock &other)
{
    if(this!=&other)
    {
        xBlock::operator=(other);
        y_elements.clear();
        allocate(other.name, other.y_elements);
    }
    return *this;
   
}
yBlock &yBlock::operator=(yBlock &&temp)
{
    if(this!=&temp)
    {
        xBlock::operator=(std::move(temp));
        allocate(name, temp.y_elements);
    }
    return *this;
}
void yBlock::print_yelements()
{
    std::cout<<'\n'<<"Printing yBlock elements for "<<this->get_name()<<"."<<std::endl;
    for(const auto &y_element_ptr : y_elements) 
    {
        if(y_element_ptr)
        { 
            y_element_ptr->print_xblock_data();
        }
    }
}
void yBlock::add_y_element(std::string name, std::shared_ptr<xBlock> &&y_element_ptr)
{
    if(!y_element_ptr) 
    {
        std::cerr<<"Null pointer passed to add_y_element."<< std::endl;
        return;
    }
    else
    {
        allocate(name, y_element_ptr);
    }
    
}
void yBlock::remove_y_element(const std::string removal_name)
{
    this->remove_element_algorithm(removal_name, y_elements);
}
void yBlock::add_y_elements(std::string name, std::vector<std::shared_ptr<xBlock>> &&y_elements_prmtr)
{
    for(const auto &y_element_ptr: y_elements_prmtr) 
    {
        if(!y_element_ptr) 
        {
            std::cerr<<"Null pointer passed to add_y_element."<< std::endl;
            return;
        }
        else
        {
            allocate(name, y_element_ptr);
        }
    }
}
void yBlock::clear_y_elements()
{
    y_elements.clear();
    std::cout<<"yBlock elements cleared."<<std::endl;
    z_complex=0.;
}
void yBlock::html_art(std::ofstream &html)
{
    if (y_elements.size() > 1)
    {
        html<<"<div class=\"parallel\">";
        html<<"<div class=\"hline selectableMap\"";
        html<<"data-name=\""<<name<<"\"";
        html<<"data-impedance_mag=\""<<get_z_magnitude()<<"[Ω]\"";
        html<<"data-impedance_phase=\""<< get_z_phase()<<"[rad]\">";
        html<<"</div>";
        for (const auto &y_element_ptr : y_elements)
        {
            if(!y_element_ptr) continue;
            html<<"<div class=\"branch\">";
            html<<"<div class=\"vline\"></div>";
            y_element_ptr->html_art(html);
            html<<"</div>";
        }
        html<<"<div class=\"hline\"></div>";
        html<<"</div>";
        html<<"<div class=\"vline\"></div>";
    }
    else if(!y_elements.empty())
    {
        for(const auto &y_element_ptr : y_elements)
        {
            y_element_ptr->html_art(html);
        }
    }
}
