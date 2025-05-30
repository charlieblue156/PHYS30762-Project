/*
Charlie Taylor - 29/04/25 - 11072486
Component class header file, which contains the Component class and its derived classes: Resistor, Capacitor, and Inductor.
Component is an abstract class that inherits from XBlock. It contains a pure virtual function set_z_complex, which is implemented in the derived classes.
The derived classes also implement the print_xblock_data and html_art functions, which are used to print the component data and generate HTML art for the components, respectively.
The class contains a unique error handling class ComponentFailure, which is used to handle errors related to components, and their removal from circuits.
*/

#ifndef COMPONENT_H
#define COMPONENT_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include<optional>
#include "XBlock.h"
#include "YBlock.h"
#include "Circuit.h"
#include "ComponentFailure.h"

class Circuit;
class ComponentLibrary;

class Component : public XBlock
{
 friend class XBlock;
protected:
  std::optional<double> value;
  virtual void set_z_complex(const double value_input, const double omega_input)=0;
  Component(const std::string name_prmtr, const std::optional<double> value_prmtr);
  Component(){}
  void activate_component(double omega);
public:
  virtual ~Component(){}
  Component(Component &&temp) : XBlock(std::move(temp)), value(std::move(temp.value)){}
  Component(const Component &other) : XBlock(other), value(other.value){}
  Component &operator=(Component &&temp);
  Component &operator=(const Component &other);
  std::optional<double> get_value() const {return value;}
  void set_value(double value_input);
};

class Resistor:public Component
{
  friend class ComponentLibrary;
private:
  void set_z_complex(const double value_input, const double omega_input) override;
  Resistor(){}
  Resistor(const std::string name_prmtr, const std::optional<double> value_prmtr) : Component(name_prmtr, value_prmtr){}
public:
  Resistor(const Resistor&original): Component(original){}
  Resistor(Resistor &&temp): Component(std::move(temp)){}
  ~Resistor(){}
  Resistor &operator=(Resistor &&temp);
  Resistor &operator=(const Resistor &other);
  void print_xblock_data() override;
  void html_art(std::ofstream &html) override;
};

class Capacitor:public Component
{
  friend class ComponentLibrary;
private:
  void set_z_complex(const double value_input, const double omega_input) override;
  Capacitor(){}
  Capacitor(const std::string name_prmtr, const double value_prmtr) : Component(name_prmtr, value_prmtr){}
public:
  Capacitor(const Capacitor&original) : Component(original){}
  Capacitor(Capacitor &&temp) : Component(std::move(temp)){}
  ~Capacitor(){}
  Capacitor &operator=(Capacitor &&temp);
  Capacitor &operator=(const Capacitor &other);
  void print_xblock_data() override;
  void html_art(std::ofstream &html) override;
};

class Inductor:public Component
{
  friend class ComponentLibrary;
private:
  void set_z_complex(const double value_input, const double omega_input) override;
  Inductor(){}
  Inductor(const std::string name_prmtr, const double value_prmtr) : Component(name_prmtr, value_prmtr){}
public:
  Inductor(const Inductor&original) : Component(original){}
  Inductor(Inductor &&temp) : Component(std::move(temp)){}
  ~Inductor(){}
  Inductor &operator=(Inductor &&temp);
  Inductor &operator=(const Inductor &other);
  void print_xblock_data() override;
  void html_art(std::ofstream &html) override;
};
#endif