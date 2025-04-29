/*
Charlie Taylor - 29/04/25 - 11072486
yBlock class header file. This class inherits from xBlock and contains a vector of shared pointers to xBlock objects.
Its function is to serve as the parallel branches within a circuit. Components, or nested yBlocks and circuits, contained in the vector
have their impedance calculated in parallel, and the yBlock's impedance is set to the equivalent impedance of the parallel branches.
The class contains functions to add, remove, and clear yBlock elements, as well as to print the yBlock elements and generate HTML art for the yBlock.
*/

#ifndef YBLOCK_H
#define YBLOCK_H

#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>
#include<fstream>
#include<optional>
#include "Component.h"
#include "xBlock.h"
#include "Circuit.h"

class Circuit;

class yBlock : public xBlock
{
friend void activate_y_block(yBlock &y_block, double omega);
private:
  std::vector<std::shared_ptr<xBlock>> y_elements;
  void set_z_complex();
  void allocate(std::string name_prmtr, std::shared_ptr<xBlock> y_element_prmtr);
  void allocate(std::string name_prmtr, std::vector<std::shared_ptr<xBlock>> y_elements_prmtr);
  void validate_y_element(std::shared_ptr<xBlock> y_element_ptr);
  void activate_y_block(yBlock &y_block, double omega);
public:
  yBlock(){}
  yBlock(const std::string name_prmtr) : xBlock(name_prmtr){}
  yBlock(const yBlock &original);
  yBlock(yBlock &&temp);
  ~yBlock(){}
  yBlock &operator=(const yBlock &other);
  yBlock &operator=(yBlock &&temp);
  std::vector<std::shared_ptr<xBlock>> get_y_elements() const {return y_elements;}
  void print_yelements();
  void add_y_element(std::string name, std::shared_ptr<xBlock> &&y_element_ptr);
  void remove_y_element(const std::string removal_name);
  void add_y_elements(std::string name, std::vector<std::shared_ptr<xBlock>> &&y_elements_prmtr);
  void clear_y_elements();
  void html_art(std::ofstream &html) override;
};

#endif