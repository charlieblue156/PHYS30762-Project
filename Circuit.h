/*
Charlie Taylor - 29/04/25 - 11072486
Circuit class header file. The class inherits from xBlock and contains a vector of shared pointers to xBlock objects. Once circuit elements have 
been added, removed or moved using the functions. Then the circuit is activated by calling the activate_circuit function. 
This sets the complex impedance of the circuit. Any invalid components are removed during this process. The circuit is generated and displayed via
a html file.
*/

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<optional>
#include "Component.h"
#include "XBlock.h"
#include "YBlock.h"

class YBlock;

class Component;

class Circuit:public XBlock
{
  friend class XBlock;
private:
  std::vector<std::shared_ptr<XBlock>> circuit_elements{};
  double omega;
  void set_z_complex();
  void allocate(std::string name_prmtr, std::shared_ptr<XBlock> circuit_element_prmtr);
  void allocate(std::string name_prmtr, std::vector<std::shared_ptr<XBlock>> circuit_elements_prmtr);
  void validate_circuit_element(std::shared_ptr<XBlock> circuit_element_ptr);
  void generate_circuit();
public:
  Circuit(){}
  Circuit(const std::string name_prmtr, double omega_prmtr) : XBlock(name_prmtr), omega{omega_prmtr}{}
  Circuit(const Circuit&original);
  Circuit(Circuit &&temp);
  ~Circuit(){}
  Circuit &operator=(const Circuit &other);
  Circuit &operator=(Circuit &&temp);
  void set_omega(double omega_input) {omega=omega_input;}
  double get_omega() const {return omega;}
  std::vector<std::shared_ptr<XBlock>> get_circuit_elements() const {return circuit_elements;}
  void activate_circuit(); 
  void find_element(const std::string &name);
  void print_circuit_elements();
  void add_circuit_element(std::string name, std::shared_ptr<XBlock> &&circuit_element_ptr);
  void remove_circuit_element(std::string name);
  void add_circuit_elements(std::string name, std::vector<std::shared_ptr<XBlock>> &&circuit_elements_prmtr);
  void clear_circuit_elements();
  void html_art(std::ofstream &html) override;
};


#endif


