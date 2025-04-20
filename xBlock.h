#ifndef XBLOCK_H
#define XBLOCK_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include<unordered_map>

class Circuit;

class xBlock
{
protected:
  std::complex<double> z_complex;
  std::string name{""};
  xBlock(const std::string name_prmtr) : name(name_prmtr){}

public:
  virtual ~xBlock(){}
  xBlock(const xBlock &other);
  xBlock(xBlock &&temp);

  xBlock &operator=(const xBlock &other);
  xBlock &operator=(xBlock &&temp);


  std::complex<double> get_z_complex() const {return z_complex;} 
  double get_z_magnitude() const {return std::abs(z_complex);}
  double get_z_phase() const {return std::arg(z_complex);}
  double get_z_real() const {return z_complex.real();}
  double get_z_imaginary() const {return z_complex.imag();}

  


  std::string get_name() const {return name;}
  void set_name(std::string name_input) {name=name_input;}
  

  std::shared_ptr<xBlock> find_element_algorithm(const std::string &name, const std::unordered_map<std::string, std::shared_ptr<xBlock>> &map);
  virtual std::shared_ptr<xBlock> find_element(const std::string &name)=0;

  void activate_x_block(xBlock &x_block, double omega);

  virtual void print_data();
};

#endif