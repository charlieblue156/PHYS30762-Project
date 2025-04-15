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


