#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"
#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>





//the initialise method is probably not optimal, try templates



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
    std::cout<<"Resistance: "<<this->get_value()<<" [Ω]."<<std::endl;
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
    std::cout<<"Capacitor: "<<this->get_value()<<" [F]."<<std::endl;
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
    std::cout<<"Inductor: "<<this->get_value()<<" [H]."<<std::endl;

}


void Resistor::set_z_complex(double value_input, double omega_input)
{
    z_complex=std::complex<double>(value_input, 0);
}

void Capacitor::set_z_complex(double value_input, double omega_input)
{
    z_complex=std::complex<double>(0, -1/(omega_input*value_input));
}

void Inductor::set_z_complex(double value_input, double omega_input)
{
    z_complex=std::complex<double>(0, omega_input*value_input);
}

void activate_component(Component &component, double omega)
{
    component.set_z_complex(component.get_value(), omega);
    //component.print_data();
}
