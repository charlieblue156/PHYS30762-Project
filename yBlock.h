#ifndef YBLOCK_H
#define YBLOCK_H


#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>
#include<unordered_map>
#include "Component.h"
#include "xBlock.h"
#include "Circuit.h"

class Circuit;

class yBlock : public xBlock
{
friend void activate_y_block(yBlock &y_block, double omega);
private:
  std::unordered_map<std::string, std::shared_ptr<xBlock>> y_elements;
  void set_z_complex();
public:
  yBlock()=default;
  yBlock(const std::string name_prmtr, std::unordered_map<std::string, std::shared_ptr<xBlock>> y_elements_prmtr);
  yBlock(const yBlock &original);
  yBlock(yBlock &&temp);
  ~yBlock(){}

  yBlock &operator=(const yBlock &other);
  yBlock &operator=(yBlock &&temp);

  std::shared_ptr<xBlock> find_element(const std::string &name) override;

  std::unordered_map<std::string, std::shared_ptr<xBlock>> get_y_elements() const {return y_elements;}
};




#endif