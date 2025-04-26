#ifndef XBLOCK_H
#define XBLOCK_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>

class Circuit;

class xBlock
{
protected:
  std::complex<double> z_complex;
  std::string name{""};
  xBlock(const std::string name_prmtr) : name(name_prmtr){}
  xBlock(){}
  std::shared_ptr<xBlock> find_element_algorithm(const std::string &name, const std::vector<std::shared_ptr<xBlock>> &vctr); //Algorithm to find ptr<xBlock> within a circuit
  void activate_x_block(xBlock &x_block, double omega); //Sets the complex impedance of the xBlock object
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
  virtual void print_xblock_data();
  virtual void html_art(std::ofstream &html)=0;
};

#endif