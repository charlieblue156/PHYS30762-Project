#ifndef COMPONENT_H
#define COMPONENT_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include<optional>
#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"

template<typename T> T parameterised_constructor(const std::string name_prmtr, const double value_prmtr)
{
    try
    {
        T temp(name_prmtr, value_prmtr);
        return temp;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<< e.what()<<" "<<name_prmtr <<" set to default value.\n" << std::endl;
        return T(name_prmtr, 0.0);
    }
}

class Circuit;

class Component : public xBlock
{
friend void activate_component(Component &component, double omega);
protected:
  std::optional<double> value;
  virtual void set_z_complex(double value_input, double omega_input)=0;
  Component(const std::string name_prmtr, const double value_prmtr);
  Component(){}
  void value_validation(const double value_input);
public:
  virtual ~Component(){}
  Component(Component &&temp) : xBlock(std::move(temp)), value(std::move(temp.value)){}
  Component(const Component &other) : xBlock(other), value(other.value){}
  Component &operator=(Component &&temp);
  Component &operator=(const Component &other);
  std::optional<double> get_value() const {return value;}
  void set_value(double value_input);
};

class Resistor:public Component
{
  friend Resistor parameterised_constructor<Resistor>(const std::string name_prmtr, const double value_prmtr);
private:
  void set_z_complex(double value_input, double omega_input) override;
  Resistor(const std::string name_prmtr, const double value_prmtr) : Component(name_prmtr, value_prmtr){}
public:
  Resistor(){}
  Resistor(const Resistor&original);
  Resistor(Resistor &&temp);
  ~Resistor(){}
  Resistor &operator=(Resistor &&temp);
  Resistor &operator=(const Resistor &other);
  void print_xblock_data() override;
  void html_art(std::ofstream &html) override;
};

class Capacitor:public Component
{
  friend Capacitor parameterised_constructor<Capacitor>(const std::string name_prmtr, const double value_prmtr);
private:
  void set_z_complex(double value_input, double omega_input) override;
  Capacitor(const std::string name_prmtr, double value_prmtr) : Component(name_prmtr, value_prmtr){}
public:
  Capacitor(){}
  Capacitor(const Capacitor&original);
  Capacitor(Capacitor &&temp);
  ~Capacitor(){}
  Capacitor &operator=(Capacitor &&temp);
  Capacitor &operator=(const Capacitor &other);
  void print_xblock_data() override;
  void html_art(std::ofstream &html) override;
};

class Inductor:public Component
{
  friend Inductor parameterised_constructor<Inductor>(const std::string name_prmtr, const double value_prmtr);
private:
  void set_z_complex(double value_input, double omega_input) override;
  Inductor(const std::string name_prmtr, const double value_prmtr) : Component(name_prmtr, value_prmtr){}
public:
  Inductor(){}
  Inductor(const Inductor&original);
  Inductor(Inductor &&temp);
  ~Inductor(){}
  Inductor &operator=(Inductor &&temp);
  Inductor &operator=(const Inductor &other);
  void print_xblock_data() override;
  void html_art(std::ofstream &html) override;
};

#endif