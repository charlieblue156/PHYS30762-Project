/*
Charlie Taylor - 29/04/25 - 11072486
Component source file.
*/

#include"Component.h"
#include"xBlock.h"
#include"yBlock.h"
#include"Circuit.h"
#include<iostream>
#include<fstream>
#include<stdexcept>
#include<string>
#include<vector>
#include<memory>
#include<complex>

void Component::activate_component(Component &component, double omega)
{
    
    try
    {
        component.set_z_complex(component.get_value().value(), omega);
    }
    catch(const std::bad_optional_access& e)
    {
        std::cerr<<"Z complex for "<<component.get_name()<<" cannot be set due to an invalid value."<<std::endl;
        throw componentFailure(component.get_name(), "Removing invalid component: "+component.get_name()+".");
    }
}
Component::Component(const std::string name_prmtr, const std::optional<double> value_prmtr) : xBlock(name_prmtr)
{
    std::cout<<"Parameterised constructor for "<<name_prmtr<<" called."<<std::endl;
    name=name_prmtr;
    if(value_prmtr.value()>0)
    {
        value=value_prmtr;
    }
    else
    {
        value=std::nullopt;
    }
}
Component &Component::operator=(Component &&temp)
{
    if(this!=&temp)
    {
        xBlock::operator=(std::move(temp));
        value=std::move(temp.value);
    }
    return *this;
}
Component &Component::operator=(const Component &other)
{
    if(this!=&other)
    {
        xBlock::operator=(other);
        value=(other.value);
    }
    return *this;
}
void Component::set_value(double value_input)
{
    std::cout<<"Setting "<<name<<" to "<<value_input<<"."<<std::endl;
    if(value_input<=0)
    {
        std::cerr<<"Value cannot be negative or zero, setting to invalid."<<std::endl;
        value=std::nullopt;
    }
    else
    {
        value=value_input;
    }
}

void Resistor::set_z_complex(const double value_input, const double omega_input)
{
    z_complex=std::complex<double>(value_input, 0);
}
Resistor &Resistor::operator=(Resistor &&temp)
{
    if(this!=&temp)
    {
        Component::operator=(std::move(temp));
        value=std::move(temp.value);
    }
    return *this;
}
Resistor &Resistor::operator=(const Resistor &other)
{
    if(this!=&other)
    {
        Component::operator=(other);
        value=(other.value);
    }
    return *this;
}
void Resistor::print_xblock_data()
{
    xBlock::print_xblock_data();
    std::cout<<"Resistor: ";
    if(this->get_value().has_value())
    {
        std::cout<<this->get_value().value()<<" [Ohm]."<<std::endl;
    }
    else
    {
        std::cout<<"no value."<<std::endl;
    }
}
void Resistor::html_art(std::ofstream &html)
{
    html<<"<div class=\"component selectableComponent\"";
    html<<" data-name=\"" << name ;
    html<<"\" data-type=\"Resistor\"";
    html<<" data-value=\"";
    if(this->get_value().has_value())
    {
        html<<this->get_value().value()<<" [Ω].\"";
    }
    else
    {
        html<<"no value.\"";
    }
    html<<" data-impedance_mag=\""<<get_z_magnitude()<<"[Ω]\"";
    html<<" data-impedance_phase=\""<<get_z_phase()<<"[rad]\">";
    html<<"R";
    html<<"</div>";
    html<<"<div class=\"vline\"></div>";
}

void Capacitor::set_z_complex(const double value_input, const double omega_input)
{
    z_complex=std::complex<double>(0, -1/(omega_input*value_input));
}
Capacitor &Capacitor::operator=(Capacitor &&temp)
{
    if(this!=&temp)
    {
        Component::operator=(std::move(temp));
        value=std::move(temp.value);
    }
    return *this;
}
Capacitor &Capacitor::operator=(const Capacitor &other)
{
    if(this!=&other)
    {
        Component::operator=(other);
        value=(other.value);
    }
    return *this;
}
void Capacitor::print_xblock_data()
{
    xBlock::print_xblock_data();
    std::cout<<"Capacitor: ";
    if(this->get_value().has_value())
    {
        std::cout<<this->get_value().value()<<" [F]."<<std::endl;
    }
    else
    {
        std::cout<<"no value."<<std::endl;
    }
}
void Capacitor::html_art(std::ofstream &html)
{
    html<<"<div class=\"component selectableComponent\"";
    html<<" data-name=\"" << name ;
    html<<"\" data-type=\"Capacitor\"";
    html<<" data-value=\"";
    if(this->get_value().has_value())
    {
        html<<this->get_value().value()<<" [F].\"";
    }
    else
    {
        html<<"no value.\"";
    }
    html<<" data-impedance_mag=\""<<get_z_magnitude()<<"[Ω]\"";
    html<<" data-impedance_phase=\""<<get_z_phase()<<"[rad]\">";
    html<<"C";
    html<<"</div>";
    html<<"<div class=\"vline\"></div>";
}

void Inductor::set_z_complex(const double value_input, const double omega_input)
{
    z_complex=std::complex<double>(0, omega_input*value_input);
}
Inductor &Inductor::operator=(Inductor &&temp)
{
    if(this!=&temp)
    {
        Component::operator=(std::move(temp));
        value=std::move(temp.value);
    }
    return *this;
}
Inductor &Inductor::operator=(const Inductor &other)
{
    if(this!=&other)
    {
        Component::operator=(other);
        value=(other.value);
    }
    return *this;
}
void Inductor::print_xblock_data()
{
    xBlock::print_xblock_data();
    std::cout<<"Inductor: ";
    if(this->get_value().has_value())
    {
        std::cout<<this->get_value().value()<<" [H]."<<std::endl;
    }
    else
    {
        std::cout<<"no value."<<std::endl;
    }
}
void Inductor::html_art(std::ofstream &html)
{
    html<<"<div class=\"component selectableComponent\"";
    html<<" data-name=\"" << name ;
    html<<"\" data-type=\"Inductor\"";
    html<<" data-value=\"";
    if(this->get_value().has_value())
    {
        html<<this->get_value().value()<<" [H].\"";
    }
    else
    {
        html<<"no value.\"";
    }
    html<<" data-impedance_mag=\""<<get_z_magnitude()<<"[Ω]\"";
    html<<" data-impedance_phase=\""<<get_z_phase()<<"[rad]\">";
    html<<"L";
    html<<"</div>";
    html<<"<div class=\"vline\"></div>";
}









