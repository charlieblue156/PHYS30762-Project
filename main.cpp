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

    component_library.component_library_entry(std::make_shared<Resistor>(parameterised_constructor<Resistor>("r1", 5.0)));
    component_library.component_library_entry(std::make_shared<Capacitor>(parameterised_constructor<Capacitor>("c1", 10.0)));
    component_library.component_library_entry(std::make_shared<Inductor>(parameterised_constructor<Inductor>("i1", 12.6)));

    //Tests the name and type value exclusivity of the component library
    component_library.component_library_entry(std::make_shared<Resistor>(parameterised_constructor<Resistor>("r1", 3.0)));
    component_library.component_library_entry(std::make_shared<Capacitor>(parameterised_constructor<Capacitor>("c2", 10.0)));


    //yBlock creation
    yBlock y1("y1");
    y1.add_y_element("r1", std::move(component_library.get_component("r1")));
    y1.add_y_element("c1", std::move(component_library.get_component("c1")));
    y1.add_y_element("i1", std::move(component_library.get_component("i1")));

    //yBlock recursion
    yBlock y1_copy= y1;
    y1.add_y_element("y2", std::make_shared<yBlock>(y1_copy));


    //Circuit creation
    Circuit c1("c1", 50);
    c1.add_circuit_element("y1", std::move(std::make_shared<yBlock>(y1)));
    c1.add_circuit_element("i1", std::move(component_library.get_component("i1")));
    c1.add_circuit_element("r1", std::move(component_library.get_component("r1")));



    yBlock y2("y2");
    Circuit c1_copy=c1;
    y2.add_y_element("y1", std::move(std::make_shared<yBlock>(y1_copy)));
    y2.add_y_element("c1", std::move(std::make_shared<Circuit>(c1_copy)));

    c1.add_circuit_element("y2", std::move(std::make_shared<yBlock>(y2)));

    c1.activate_circuit(); 
    c1.generate_circuit();

    return 0;
}

// g++ "Component.h" "Component.cpp" "xBlock.h" "xBlock.cpp" "yBlock.h" "yBlock.cpp" "Circuit.h" "Circuit.cpp" "main.cpp" "componentLibrary.cpp" "componentLibrary.h" -o Project.exe

