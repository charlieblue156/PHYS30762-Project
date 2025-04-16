#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"

class yBlock;

class Component;


class Circuit:public xBlock
{
friend void activate_circuit(Circuit &circuit);
private:
  std::vector<std::shared_ptr<xBlock>> circuit_elements{};
  double omega;
  void set_z_complex();

public:
  Circuit()=default;
  Circuit(double omega_prmtr, std::vector<std::shared_ptr<xBlock>> circuit_elements_prmtr) : omega{omega_prmtr}, circuit_elements(circuit_elements_prmtr){}
  Circuit(const Circuit&original);
  Circuit(Circuit &&temp): omega(std::move(temp.omega)), circuit_elements(std::move(temp.circuit_elements)){}
  ~Circuit(){}

  Circuit &operator=(const Circuit &other);
  Circuit &operator=(Circuit &&temp);

  
  void set_omega(double omega_input) {omega=omega_input;}
  double get_omega() const {return omega;}

 
};


#endif






/*
OVERWRITING OMEGA
#include <iostream>
#include <vector>
#include <memory>

// Base class for all elements
class SeriesElement {
public:
    virtual ~SeriesElement() = default;
    virtual double getOmega() const = 0;
};

// Component class derived from SeriesElement
class Component : public SeriesElement {
public:
    // Component does not manage omega directly but can access it
    double getOmega() const override {
        return omega;
    }

    // Set omega indirectly from its parent (circuit)
    void setOmega(double omegaValue) {
        omega = omegaValue;
    }

private:
    double omega = 0;
};

// ParallelElement class derived from SeriesElement
class ParallelElement : public SeriesElement {
public:
    ParallelElement(std::vector<std::shared_ptr<SeriesElement>> elements)
        : elements(std::move(elements)) {}

    double getOmega() const override {
        // Return omega from the first element (or you could have more complex logic here)
        return elements.empty() ? 0 : elements[0]->getOmega();
    }

private:
    std::vector<std::shared_ptr<SeriesElement>> elements;
};

// Circuit class derived from SeriesElement
class Circuit : public SeriesElement {
public:
    Circuit(double omega = 0)
        : omega(omega) {}

    // Override omega for the circuit
    void setOmega(double newOmega) {
        omega = newOmega;
        // Also propagate this omega to all the constituent series elements (if needed)
        for (auto& elem : elements) {
            elem->setOmega(omega);
        }
    }

    double getOmega() const override {
        return omega;
    }

    // Add a series element to the circuit
    void addElement(std::shared_ptr<SeriesElement> element) {
        elements.push_back(element);
    }

    // For nested circuits, we want to make sure that the omega of the outer circuit takes precedence
    void addSubCircuit(std::shared_ptr<Circuit> subCircuit) {
        subCircuit->setOmega(omega);  // Override the sub-circuit's omega with the outer circuit's omega
        elements.push_back(subCircuit);  // Add the sub-circuit as a series element
    }

private:
    double omega;
    std::vector<std::shared_ptr<SeriesElement>> elements;
};

// Test function to demonstrate behavior
void testCircuit() {
    // Create a Component and a Circuit
    auto component = std::make_shared<Component>();
    component->setOmega(10);

    auto innerCircuit = std::make_shared<Circuit>(20);  // Omega for inner circuit is 20
    auto outerCircuit = std::make_shared<Circuit>(30);  // Omega for outer circuit is 30

    outerCircuit->addElement(component);  // Add a component to the outer circuit

    // Adding the inner circuit into the outer circuit
    outerCircuit->addSubCircuit(innerCircuit);  // The omega of the outer circuit (30) should override the inner circuit

    // Checking omega values
    std::cout << "Component omega: " << component->getOmega() << std::endl;  // Should be 10 (individual component's omega)
    std::cout << "Inner Circuit omega: " << innerCircuit->getOmega() << std::endl;  // Should be 30 (overridden omega from outer circuit)
    std::cout << "Outer Circuit omega: " << outerCircuit->getOmega() << std::endl;  // Should be 30
}

int main() {
    testCircuit();
    return 0;
}

*/