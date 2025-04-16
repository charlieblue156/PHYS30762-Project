#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"



void xBlock::activate_x_block(xBlock &x_block, Circuit circuit)
{
    if(auto component=dynamic_cast<Component*>(&x_block)) 
    {
        activate_component(*component, circuit);
    }
    else if(auto y_block=dynamic_cast<yBlock*>(&x_block)) 
    {
        activate_y_block(*y_block, circuit);
    }
    else if(auto circuit=dynamic_cast<Circuit*>(&x_block)) 
    {
        activate_circuit(*circuit);
    }
}


void xBlock::print_data()
{
    std::cout<<'\n'<<"Printing data for "<<this->get_name()<<"."<<std::endl;
    if(this->get_z_phase()<0)
    {
        std::cout<<"Complex impedance: "<<this->get_z_real()<<" "<<this->get_z_imaginary()<<"i [\u03A9]."<<std::endl;
    }
    else
    {
        std::cout<<"Complex impedance: "<<this->get_z_real()<<" +"<<this->get_z_imaginary()<<"i [\u03A9]."<<std::endl;
    }
    std::cout<<"Magnitude: "<<this->get_z_magnitude()<<" [\u03A9]."<<std::endl;
    std::cout<<"Phase: "<<this->get_z_phase()<<" [rad]."<<std::endl;
}