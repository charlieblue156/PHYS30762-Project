# PHYS30762-Project

Charlie Taylor - 01/05/25 - 11072486

To compile type : 
" g++ "main.cpp" "Component.h" "Component.cpp" "ComponentLibrary.h" "ComponentLibrary.cpp" "XBlock.h" "XBlock.cpp" "YBlock.h" "YBlock.cpp" "Circuit.h" "Circuit.cpp" "ComponentFailure.h" -o Project.exe " 
into gitbash terminal.

This code simulates an AC circuit. The user can construct and calculate the impedance of the circuit, as well as the components. Circuits are constructed as a vector of shared pointers to XBlock objects. These are the abstract class that is parent to Component, Circuit, and yBlock. yBlock contains vector of shared pointers to XBlocks, the constituents of which correspond to XBlocks in parallel.

In main(), the user should first add some components to the component library, the derived types allowed can be viewed in the "Component.h" file. Next construct a Circuit object, and add elements to the vector using Circuit::add_circuit_element(std::string name, std::shared_ptr<XBlock> &&circuit_element_ptr). Then activate the circuit using Circuit::activate_circuit(), and a html file displaying the circuit will be generated in the workspace folder.
