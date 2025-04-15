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
friend void activate_component(Component &component, Circuit circuit);
protected:
  std::string name{""};
  double value;
  virtual void set_z_complex(double value_input, double omega_input)=0;

//template can be inserted if necessary and if time
public:
  virtual ~Component(){}

  Component &operator=(Component &&temp);
  Component &operator=(const Component &other);

  void intialise(const std::string name_prmtr, const double value_prmtr);
  double get_value() const {return value;}
  void set_value(double value_input) {value=value_input;}
};


class Resistor:public Component
{
private:
  void set_z_complex(double value_input, double omega_input) override;
public:
  Resistor()=default;
  Resistor(const std::string name_prmtr, const double value_prmtr);
  Resistor(const Resistor&original);
  Resistor(Resistor &&temp);
  ~Resistor(){}





};

class Capacitor:public Component
{
private:
  void set_z_complex(double value_input, double omega_input) override;
public:
  Capacitor()=default;
  Capacitor(const std::string name_prmtr, const double value_prmtr);
  Capacitor(const Capacitor&original);
  Capacitor(Capacitor &&temp);
  ~Capacitor(){}

};

class Inductor:public Component
{
private:
  void set_z_complex(double value_input, double omega_input) override;
public:
  Inductor()=default;
  Inductor(const std::string name_prmtr, const double value_prmtr);
  Inductor(const Inductor&original);
  Inductor(Inductor &&temp);
  ~Inductor(){}
};



#endif