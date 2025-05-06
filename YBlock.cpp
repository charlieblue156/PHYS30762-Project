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
#include "XBlock.h"
#include "Component.h"
#include "YBlock.h"
#include "Circuit.h"

//calculates and sets complex impedance of YBlock
void YBlock::activate_y_block(double omega)
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
//sets complex impedance of YBlock
void YBlock::set_z_complex()
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
//Attempts to add single XBlock pointer to y_elements
void YBlock::allocate(std::string name_prmtr, std::shared_ptr<XBlock> y_element_prmtr)
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
//Attempts to add vector of XBlock pointer to y_elements
void YBlock::allocate(std::string name_prmtr, std::vector<std::shared_ptr<XBlock>> y_elements_prmtr)
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
//Validates against null ptr arguments
void YBlock::validate_y_element(std::shared_ptr<XBlock> y_element_ptr)
{
    if(!y_element_ptr) 
    {
        throw std::invalid_argument("Null pointer passed to "+name+".");
    }
}
YBlock::YBlock(const YBlock&original) : XBlock(original)
{
    y_elements.clear();
    allocate(original.name, original.y_elements);
}
YBlock::YBlock(YBlock &&temp) : XBlock(std::move(temp))
{
    allocate(temp.name, temp.y_elements);
}
YBlock &YBlock::operator=(const YBlock &other)
{
    if(this!=&other)
    {
        XBlock::operator=(other);
        y_elements.clear();
        allocate(other.name, other.y_elements);
    }
    return *this;
   
}
YBlock &YBlock::operator=(YBlock &&temp)
{
    if(this!=&temp)
    {
        XBlock::operator=(std::move(temp));
        allocate(name, temp.y_elements);
    }
    return *this;
}
void YBlock::print_yelements()
{
    std::cout<<'\n'<<"Printing YBlock elements for "<<this->name<<"."<<std::endl;
    for(const auto &y_element_ptr : y_elements) 
    {
        if(y_element_ptr)
        { 
            y_element_ptr->print_xblock_data();
        }
    }
}
//Abstraction of the allocate function
void YBlock::add_y_element(std::string name, std::shared_ptr<XBlock> &&y_element_ptr)
{

    allocate(name, y_element_ptr);
    
}
//Abstraction of the remove_y_element algorithm
void YBlock::remove_y_element(const std::string removal_name)
{
    this->remove_element_algorithm(removal_name, y_elements);
}
//Abstraction of allocate for a vector of ptrs
void YBlock::add_y_elements(std::string name, std::vector<std::shared_ptr<XBlock>> &&y_elements_prmtr)
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
//Clears y_elements
void YBlock::clear_y_elements()
{
    y_elements.clear();
    std::cout<<"yBlock elements cleared."<<std::endl;
    z_complex=0.;
}
//Contains the html symbol
void YBlock::html_art(std::ofstream &html)
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
