#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<unordered_map>
#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"

class yBlock;

class Component;


class Circuit:public xBlock
{

private:
  std::vector<std::shared_ptr<xBlock>> circuit_elements{};
  double omega;
  void set_z_complex();

public:
  Circuit()=default;
  Circuit(const std::string name_prmtr, double omega_prmtr, std::vector<std::shared_ptr<xBlock>> circuit_elements_prmtr);
  Circuit(const Circuit&original);
  Circuit(Circuit &&temp);
  ~Circuit(){}

  Circuit &operator=(const Circuit &other);
  Circuit &operator=(Circuit &&temp);

  
  void set_omega(double omega_input) {omega=omega_input;}
  double get_omega() const {return omega;}

  std::vector<std::shared_ptr<xBlock>> get_circuit_elements() const {return circuit_elements;}

  void activate_circuit();

  void find_element(const std::string &name);

  void print_circuit_elements();

  void add_circuit_element(std::string name, std::shared_ptr<xBlock> circuit_element_ptr);
  void remove_circuit_element(std::string name);
  void add_circuit_elements(std::string name, std::vector<std::shared_ptr<xBlock>> circuit_elements_prmtr);
  void clear_circuit_elements();

  void alloc_validation(std::string name_prmtr, std::vector<std::shared_ptr<xBlock>> circuit_elements_prmtr);

  void generate_circuit();

  void html_art(std::ofstream &html) override;
};


#endif


