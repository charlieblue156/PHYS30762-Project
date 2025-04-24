#ifndef COMPONENT_H
#define COMPONENT_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>

#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"


class Circuit;

class Component : public xBlock
{
friend void activate_component(Component &component, double omega);
protected:
  double value;
  virtual void set_z_complex(double value_input, double omega_input)=0;
  Component(const std::string name_prmtr, const double value_prmtr) : xBlock(name_prmtr), value(value_prmtr){}

public:
  virtual ~Component(){}
  Component(Component &&temp) : xBlock(std::move(temp)), value(std::move(temp.value)){}
  Component(const Component &other) : xBlock(other), value(other.value){}

  Component &operator=(Component &&temp);
  Component &operator=(const Component &other);

  double get_value() const {return value;}
  void set_value(double value_input) {value=value_input;}

};


class Resistor:public Component
{
private:
  void set_z_complex(double value_input, double omega_input) override;
public:
  Resistor()=default;
  Resistor(const std::string name_prmtr, const double value_prmtr) : Component(name_prmtr, value_prmtr){}
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
private:
  void set_z_complex(double value_input, double omega_input) override;
public:
  Capacitor()=default;
  Capacitor(const std::string name_prmtr, double value_prmtr) : Component(name_prmtr, value_prmtr){}
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
private:
  void set_z_complex(double value_input, double omega_input) override;
public:
  Inductor()=default;
  Inductor(const std::string name_prmtr, const double value_prmtr) : Component(name_prmtr, value_prmtr){}
  Inductor(const Inductor&original);
  Inductor(Inductor &&temp);
  ~Inductor(){}

  Inductor &operator=(Inductor &&temp);
  Inductor &operator=(const Inductor &other);

  void print_xblock_data() override;
  void html_art(std::ofstream &html) override;
};



#endif