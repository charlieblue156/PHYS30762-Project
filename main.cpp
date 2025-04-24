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

    std::unordered_map<std::string, std::shared_ptr<xBlock>> y_elements_1;
    y_elements_1["r1"]=component_library.get_component("r1");
    y_elements_1["c1"]=component_library.get_component("c1"); 
    y_elements_1["i1"]=component_library.get_component("i1");
    y_elements_1["y1"]=std::make_shared<yBlock>("y1", y_elements_1);


    std::unordered_map<std::string, std::shared_ptr<xBlock>> y_elements_2;
    y_elements_2["i1"]=component_library.get_component("i1");


    std::unordered_map<std::string, std::shared_ptr<xBlock>> circuit_1_elements;
    circuit_1_elements["y1"]=std::make_shared<yBlock>("y1", y_elements_1);
    circuit_1_elements["y2"]=std::make_shared<yBlock>("y2", y_elements_2);
    circuit_1_elements["i1"]=component_library.get_component("i1");
    circuit_1_elements["c1"]=std::make_shared<Circuit>("c1", 50, circuit_1_elements);


    Circuit circuit1{"circuit1", 50, std::move(circuit_1_elements)};
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
- Component library, enumerate with word ie parse by word  DONE
-> Print data for specific circuit part, possible via enumerating the yBlock and Circuit etc DONE
- Check for errors with this, possibly start the catching and throwing, check for name not in circuit
-omega symbol

- For component not in the circuit segmentation fault arises, check for this and throw an exception DONE
- The find_element_algorithm returns a nullptr for each element in the iterator, it needs to return a null ptr if the iteration is over and no elements are found DONE


- Ascii 
Add in the yblock and recursive circuit clickables, tidy up then done

- Catch, throw, exceptions
inc: empty vectors, invalid values, invalid name, incorrect type etc
- Change the name of the component to be unique, check if name already exists in the library DONE


- Test move and copy constructors and assignment operators

*/