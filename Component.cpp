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




void activate_component(Component &component, double omega)
{
    try
    {
        component.set_z_complex(component.get_value().value(), omega);
    }
    catch(const std::bad_optional_access& e)
    {
        std::cerr<<"Z complex's cannot be set for empty values."<<std::endl;
    }
}

Component::Component(const std::string name_prmtr, const double value_prmtr) : xBlock(name_prmtr)
{
    std::cout<<"Parameterised constructor for "<<name_prmtr<<" called."<<std::endl;
    
    value_validation(value_prmtr);
    value=value_prmtr;
}
void Component::value_validation(const double value_prmtr)
{
    if(value_prmtr<=0.0)
    {
        throw std::invalid_argument("Fail. Value must be greater than 0.");
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
    try
    {
        value_validation(value_input);
        value=value_input;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<< e.what()<<'\n'<< std::endl;

    }

}




void Resistor::set_z_complex(double value_input, double omega_input)
{
    
    z_complex=std::complex<double>(value_input, 0);
}



Resistor::Resistor(const Resistor&original) : Component(original)
{
    std::cout<<"Copy constructor for "<<name<<" called."<<std::endl;
}
Resistor::Resistor(Resistor &&temp) : Component(std::move(temp))
{
    std::cout<<"Move constructor for "<<name<<" called."<<std::endl;
}
Resistor &Resistor::operator=(Resistor &&temp)
{
    std::cout<<"Move assignment operator for "<<name<<" called."<<std::endl;
    if(this!=&temp)
    {
        Component::operator=(std::move(temp));
        value=std::move(temp.value);
    }
    return *this;
}
Resistor &Resistor::operator=(const Resistor &other)
{
    std::cout<<"Copy assignment operator for "<<name<<" called."<<std::endl;
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
        std::cout<<this->get_value().value()<<" [Ω]."<<std::endl;
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

void Capacitor::set_z_complex(double value_input, double omega_input)
{
    z_complex=std::complex<double>(0, -1/(omega_input*value_input));
}

Capacitor::Capacitor(const Capacitor&original) : Component(original)
{
    std::cout<<"Copy constructor for "<<name<<" called."<<std::endl;
}
Capacitor::Capacitor(Capacitor &&temp) : Component(std::move(temp))
{
    std::cout<<"Move constructor for "<<name<<" called."<<std::endl;
}
Capacitor &Capacitor::operator=(Capacitor &&temp)
{
    std::cout<<"Move assignment operator for "<<name<<" called."<<std::endl;
    if(this!=&temp)
    {
        Component::operator=(std::move(temp));
        value=std::move(temp.value);
    }
    return *this;
}
Capacitor &Capacitor::operator=(const Capacitor &other)
{
    std::cout<<"Copy assignment operator for "<<name<<" called."<<std::endl;
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

void Inductor::set_z_complex(double value_input, double omega_input)
{
    z_complex=std::complex<double>(0, omega_input*value_input);
}

Inductor::Inductor(const Inductor&original) : Component(original)
{
    std::cout<<"Copy constructor for "<<name<<" called."<<std::endl;
}
Inductor::Inductor(Inductor &&temp) : Component(std::move(temp))
{
    std::cout<<"Move constructor for "<<name<<" called."<<std::endl;
}
Inductor &Inductor::operator=(Inductor &&temp)
{
    std::cout<<"Move assignment operator for "<<name<<" called."<<std::endl;
    if(this!=&temp)
    {
        Component::operator=(std::move(temp));
        value=std::move(temp.value);
    }
    return *this;
}
Inductor &Inductor::operator=(const Inductor &other)
{
    std::cout<<"Copy assignment operator for "<<name<<" called."<<std::endl;
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









