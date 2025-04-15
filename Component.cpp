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



void Component::intialise(const std::string name_prmtr, const double value_prmtr)
{
    this->name=name_prmtr;
    this->value=value_prmtr;
}

Component &Component::operator=(Component &&temp)
{
    if(this!=&temp)
    {
      name=std::move(temp.name);
      value=std::move(temp.value);
    }
    return *this;
}
Component &Component::operator=(const Component &other)
{
    if(this!=&other)
    {
        name=(other.name);
        value=(other.value);
    }
    return *this;
}

Resistor::Resistor(const std::string name_prmtr, const double value_prmtr)
{
    intialise(name_prmtr, value_prmtr);
}
Resistor::Resistor(const Resistor&original)
{
    intialise(original.name, original.value);
}
Resistor::Resistor(Resistor &&temp)
{
    //double check this works
    intialise(std::move(temp.name), std::move(temp.value));
}

Capacitor::Capacitor(const std::string name_prmtr, const double value_prmtr)
{
    intialise(name_prmtr, value_prmtr);
}
Capacitor::Capacitor(const Capacitor&original)
{
    intialise(original.name, original.value);
}
Capacitor::Capacitor(Capacitor &&temp)
{
    //double check this works
    intialise(std::move(temp.name), std::move(temp.value));
}


Inductor::Inductor(const std::string name_prmtr, const double value_prmtr)
{
    intialise(name_prmtr, value_prmtr);
}
Inductor::Inductor(const Inductor&original)
{
    intialise(original.name, original.value);
}
Inductor::Inductor(Inductor &&temp)
{
    //double check this works
    intialise(std::move(temp.name), std::move(temp.value));
}

void Resistor::set_z_complex(double value_input, double omega_input)
{
    z_complex=std::complex<double>(value_input, 0);
}

void Capacitor::set_z_complex(double value_input, double omega_input)
{
    z_complex=std::complex<double>(0, 1/(omega_input*value_input));
}

void Inductor::set_z_complex(double value_input, double omega_input)
{
    z_complex=std::complex<double>(0, omega_input*value_input);
}

void activate_component(Component &component, Circuit circuit)
{
    component.set_z_complex(component.get_value(), circuit.get_omega());
}