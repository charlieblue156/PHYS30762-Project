#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include<fstream>
#include<algorithm>

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

//MOVE!! &&
void yBlock::alloc_validation(std::string name_prmtr, std::vector<std::shared_ptr<xBlock>> y_elements_prmtr)
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

yBlock::yBlock(const std::string name_prmtr,   std::vector<std::shared_ptr<xBlock>> y_elements_prmtr) : xBlock(name_prmtr)
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
    for(const auto &y_element_ptr : y_block.y_elements) 
    {
        if(y_element_ptr)
        { 
            y_block.activate_x_block(*y_element_ptr, omega);
        }
    }
    y_block.set_z_complex();
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


void yBlock::add_y_element(std::string name, std::shared_ptr<xBlock> y_element_ptr)
{
    try
    {
        y_elements.push_back(y_element_ptr);
    }
    catch(const std::bad_alloc& memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name<<"."<<std::endl;
    }
}

void yBlock::remove_y_element(const std::string name)
{
    auto iterator = std::find_if(y_elements.begin(), y_elements.end(), [&name](const std::shared_ptr<xBlock> &y_element_ptr) 
    {
        return y_element_ptr && y_element_ptr->get_name() == name; 
    });

    if(iterator!=y_elements.end()) 
    {
        y_elements.erase(iterator);
        std::cout << name << " removed from " << this->get_name() << "." << std::endl;
        return;
    } 
    else 
    {

        for(const auto &element_ptr : y_elements)
        {
            if(!element_ptr) continue;
            if(auto circuit_ptr=dynamic_cast<Circuit*>(element_ptr.get())) 
            {
                circuit_ptr->remove_circuit_element(name);
            }
            else if(auto y_block_ptr=dynamic_cast<yBlock*>(element_ptr.get())) 
            {
                y_block_ptr->remove_y_element(name);
            }
        }
        std::cout << name << " not found in " << this->get_name() << "." << std::endl;
    }

}


void yBlock::add_y_elements(std::string name, std::vector<std::shared_ptr<xBlock>> y_elements_prmtr)
{
    try
    {
        for(const auto &y_element_ptr : y_elements_prmtr) 
        {
            if(y_element_ptr) 
            {
                y_elements.push_back(y_element_ptr);
            }
        }
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


/*void yBlock::html_art(std::ofstream &html)
{
    if(y_elements.size()>1)
    {
        html<<"<div class=\"hline selectableMap\"";
        html<<" data-name=\"" << name <<"\"";
        html<<" data-impedance_mag=\""<<this->get_z_magnitude()<<"[Ω]\"";
        html<<" data-impedance_phase=\""<<this->get_z_phase()<<"[rad]\">";
        html << "</div>";

        html<<"<div class=\"parallel\">";
        for(const auto &[name,y_element_ptr] : y_elements) 
        {
            if(y_element_ptr)
            { 
                html<<"<div class=\"branch\">";
                html<<"<div class=\"vline\"></div>";
                html<<"<div class=\"component\">";
                y_element_ptr->html_art(html);
                html<<"</div>";
                html<<"<div class=\"vline\"></div>";
                html<<"</div>";
            }
        }
        html<<"</div>";
        html<<"<div class=\"hline\">";
        html<<"</div>";
    }
    else
    {
        for(const auto &[name,y_element_ptr] : y_elements) 
        {
            if(y_element_ptr)
            { 
                html<<"<div class=\"component\">";
                y_element_ptr->html_art(html);
                html<<"</div>";
                //html<<"<div class=\"component\">|</div>";
            }
        }
    }
}*/

void yBlock::html_art(std::ofstream &html)
{
    if (y_elements.size() > 1)
    {// vline before


        html << "<div class=\"parallel\">";
        html << "<div class=\"hline selectableMap\""
        << " data-name=\"" << name << "\""
        << " data-impedance_mag=\"" << get_z_magnitude() << "[Ω]\""
        << " data-impedance_phase=\"" << get_z_phase() << "[rad]\">"
        << "</div>";
        for (const auto &y_element_ptr : y_elements)
        {
            if (!y_element_ptr) continue;
            html << "<div class=\"branch\">";
            html << "<div class=\"vline\"></div>";
 // Allow nesting
            y_element_ptr->html_art(html);

            html << "<div class=\"vline\"></div>";
            html << "</div>";
        }
        html << "<div class=\"hline\"></div>";
        html << "</div>";


 // vline after
    }
    else if (!y_elements.empty())
    {
        for (const auto & y_element_ptr : y_elements)
        {

            y_element_ptr->html_art(html);
        }
    }
}
