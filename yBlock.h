#ifndef YBLOCK_H
#define YBLOCK_H

#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>
#include<fstream>
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
  void alloc_validation(std::string name_prmtr, std::vector<std::shared_ptr<xBlock>> y_elements_prmtr);
public:
  yBlock()=default;
  yBlock(const std::string name_prmtr, std::vector<std::shared_ptr<xBlock>> &&y_elements_prmtr);
  yBlock(const yBlock &original);
  yBlock(yBlock &&temp);
  ~yBlock(){}
  yBlock &operator=(const yBlock &other);
  yBlock &operator=(yBlock &&temp);
  std::vector<std::shared_ptr<xBlock>> get_y_elements() const {return y_elements;}
  void print_yelements();
  void add_y_element(std::string name, std::shared_ptr<xBlock> y_element_ptr);
  void remove_y_element(std::string name);
  void add_y_elements(std::string name, std::vector<std::shared_ptr<xBlock>> y_elements_prmtr);
  void clear_y_elements();
  void html_art(std::ofstream &html) override;
};

#endif