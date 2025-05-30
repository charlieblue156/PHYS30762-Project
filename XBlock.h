/*
Charlie Taylor - 29/04/25 - 11072486
xBlock class header file, this is the abstract base class for components, circuits and yBlocks. It contains the pure virtual function set_z_complex,
which is implemented in the derived classes. It contains definitions of functions common to all derived classes, such as the find element algorithm,
and print data.
*/

#ifndef XBLOCK_H
#define XBLOCK_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>


class Circuit;
class Component;

class XBlock
{
  friend class YBlock;
  friend class Component;
protected:
  std::complex<double> z_complex;
  std::string name{""};
  XBlock(const std::string name_prmtr) : name(name_prmtr){}
  XBlock(){}
  std::shared_ptr<XBlock> find_element_algorithm(const std::string &name, const std::vector<std::shared_ptr<XBlock>> &vctr);
  void remove_element_algorithm(const std::string &name, std::vector<std::shared_ptr<XBlock>> &vctr);
  void activate_x_block(XBlock &x_block, double omega); 
public:
  virtual ~XBlock(){}
  XBlock(const XBlock &other);
  XBlock(XBlock &&temp);
  XBlock &operator=(const XBlock &other);
  XBlock &operator=(XBlock &&temp);
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
