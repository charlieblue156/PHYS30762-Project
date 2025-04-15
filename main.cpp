#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"

int main()
{
    std::shared_ptr<Resistor> r1{std::make_shared<Resistor> ("r1", 5.0)};
    std::shared_ptr<Capacitor> c1{std::make_shared<Capacitor> ("c1", 10.0)};
    std::shared_ptr<Inductor> i1{std::make_shared<Inductor> ("i1", 12.6)};

    std::vector<std::shared_ptr<xBlock>> y_elements_1;
    y_elements_1.push_back(r1);
    y_elements_1.push_back(c1);


    std::vector<std::shared_ptr<xBlock>> y_elements_2;
    y_elements_2.push_back(r1);


    std::vector<std::shared_ptr<xBlock>> circuit_1_elements;
    circuit_1_elements.push_back(std::make_shared<yBlock> (y_elements_1));
    circuit_1_elements.push_back(std::make_shared<yBlock> (y_elements_2));


    Circuit circuit1{50, std::move(circuit_1_elements)};
    activate_circuit(circuit1);

    return 0;
}

// g++ "Component.h" "Component.cpp" "xBlock.h" "xBlock.cpp" "yBlock.h" "yBlock.cpp" "Circuit.h" "Circuit.cpp" "main.cpp" -o Project.exe