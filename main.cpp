#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include<unordered_map>
#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"
#include "componentLibrary.h"

int main()
{
    componentLibrary component_library{};
    component_library.set_name("component_library");

    component_library.component_library_entry(std::make_shared<Resistor> ("r1", 5.0));
    component_library.component_library_entry(std::make_shared<Capacitor> ("c1", 10.0));
    component_library.component_library_entry(std::make_shared<Inductor> ("i1", 12.6));
    component_library.component_library_entry(std::make_shared<Resistor> ("r1", 3.0));
    component_library.component_library_entry(std::make_shared<Capacitor> ("c2", 10.0));

    std::vector<std::shared_ptr<xBlock>> y_elements_1;
    y_elements_1.push_back(component_library.get_component("r1"));
    y_elements_1.push_back(component_library.get_component("c1"));
    y_elements_1.push_back(component_library.get_component("i1"));
    std::vector<std::shared_ptr<xBlock>> y_elements_1_copy = y_elements_1;
    y_elements_1.push_back(std::make_shared<yBlock>("y1", std::move(y_elements_1_copy)));


    std::vector<std::shared_ptr<xBlock>> y_elements_2;



    std::vector<std::shared_ptr<xBlock>> circuit_1_elements;
    circuit_1_elements.push_back(std::make_shared<yBlock>("y1", std::move(y_elements_1)));
    circuit_1_elements.push_back(component_library.get_component("i1"));




    Circuit circuit2{"circuit2", 50, circuit_1_elements};
    circuit_1_elements.push_back(std::make_shared<Circuit>("C1", 50, std::move(circuit2.get_circuit_elements())));
    y_elements_2.push_back(std::make_shared<Circuit>("C1", 50, circuit_1_elements));
    y_elements_2.push_back(component_library.get_component("i1"));
    circuit_1_elements.push_back(std::make_shared<yBlock>("y3", std::move(y_elements_2)));
    Circuit circuit1{"circuit1", 50, circuit_1_elements};
    circuit1.activate_circuit(); 
    circuit1.generate_circuit();

    //Further encapsiulate, components/elements can only be added to containers via functions,
    //These funtions check for bad alloc (catch)
    //Have catch/throw for infinite 

    return 0;
}

// g++ "Component.h" "Component.cpp" "xBlock.h" "xBlock.cpp" "yBlock.h" "yBlock.cpp" "Circuit.h" "Circuit.cpp" "main.cpp" "componentLibrary.cpp" "componentLibrary.h" -o Project.exe

/*

To do list:
- try nested circuits in yBlock for ui


- Test move and copy constructors and assignment operators

*/