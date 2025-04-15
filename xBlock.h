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
public:
  virtual ~xBlock(){}
  std::complex<double> get_z_complex() const {return z_complex;} 
  double get_z_magnitude() const {return std::abs(z_complex);}
  double get_z_phase() const {return std::arg(z_complex);}

  void activate_x_block(xBlock &x_block, Circuit circuit);
};

#endif