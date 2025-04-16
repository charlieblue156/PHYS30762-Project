#ifndef YBLOCK_H
#define YBLOCK_H


#include<iostream>
#include<string>
#include<vector>
#include<complex>
#include<memory>
#include "Component.h"
#include "xBlock.h"
#include "Circuit.h"

class Circuit;

class yBlock : public xBlock
{
friend void activate_y_block(yBlock &y_block, Circuit circuit);
private:
  std::vector<std::shared_ptr<xBlock>> y_elements;
  void set_z_complex();
public:
  yBlock()=default;
  yBlock(std::vector<std::shared_ptr<xBlock>> y_elements_prmtr) : y_elements(y_elements_prmtr){}
  yBlock(const yBlock &original);
  yBlock(yBlock &&temp) : xBlock(std::move(temp)), y_elements(std::move(temp.y_elements)){}
  ~yBlock(){}

  yBlock &operator=(const yBlock &other);
  yBlock &operator=(yBlock &&temp);


  //access the y elements
  std::vector<std::shared_ptr<xBlock>> get_y_elements() const {return y_elements;}




};




#endif