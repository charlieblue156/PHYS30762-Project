/*
Charlie Taylor - 29/04/25 - 11072486
Circuit class source file.
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<memory>
#include<complex>
#include<algorithm>
#include "Component.h"
#include "xBlock.h"
#include "yBlock.h"
#include "Circuit.h"

void Circuit::set_z_complex()
{
    for(const auto& circuit_elements_ptr : circuit_elements) 
    {
        if(circuit_elements_ptr)
        { 
            z_complex+=circuit_elements_ptr->get_z_complex();
        }
    }
}
void Circuit::allocate(std::string name_prmtr, std::shared_ptr<xBlock> circuit_element_prmtr)
{
    try
    {
        validate_circuit_element(circuit_element_prmtr);
        circuit_elements.push_back(circuit_element_prmtr);
    }
    catch(std::bad_alloc &memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name_prmtr<<"."<<std::endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<<e.what()<<std::endl;
    }
}
void Circuit::allocate(std::string name_prmtr, std::vector<std::shared_ptr<xBlock>> circuit_elements_prmtr)
{
    try
    {
        for(const auto &circuit_element_ptr: circuit_elements_prmtr) 
        {
            validate_circuit_element(circuit_element_ptr);
            circuit_elements.push_back(circuit_element_ptr);
        }
    }
    catch(std::bad_alloc &memFail)
    {
        std::cerr<<"Memory allocation failed for "<<name_prmtr<<"."<<std::endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<<e.what()<<std::endl;
    }
}
void Circuit::validate_circuit_element(std::shared_ptr<xBlock> circuit_element_ptr)
{
    if(!circuit_element_ptr) 
    {
        throw std::invalid_argument("Null pointer passed to"+name+".");
    }
}
Circuit::Circuit(const Circuit&original) : xBlock{original}, omega{original.omega}
{
    allocate(original.name, original.circuit_elements);
}
Circuit::Circuit(Circuit &&temp): xBlock(std::move(temp)), omega(std::move(temp.omega))
{
    circuit_elements.clear();
    allocate(name, temp.circuit_elements);
}
Circuit &Circuit::operator=(const Circuit &other)
{
    if(this!=&other)
    {
        xBlock::operator=(other);
        omega=other.omega;
        allocate(other.name, other.circuit_elements);
    }
    return *this;
}
Circuit &Circuit::operator=(Circuit &&temp)
{
    circuit_elements.clear();
    if(this!=&temp)
    {
        xBlock::operator=(std::move(temp));
        omega=std::move(temp.omega);
        allocate(name, temp.circuit_elements);
    }
    return *this;
}
void Circuit::activate_circuit()
{
    std::cout<<"Activating "<<this->get_name()<<"."<<std::endl;
    for(const auto &circuit_element_ptr: this->circuit_elements) 
    {
        if(circuit_element_ptr)
        {
          try
          {
            this->activate_x_block(*circuit_element_ptr, omega);
          }
          catch(const componentFailure &e)
          {
            std::cerr<<e.what()<<std::endl;
            this->remove_circuit_element(e.get_component_name());
          }
        }
    }
    this->set_z_complex();
    this->generate_circuit();
}
void Circuit::find_element(const std::string &name)
{
    std::cout<<'\n'<<"Searching for "<<name<<" in "<<this->get_name()<<"."<<std::endl;
    std::shared_ptr<xBlock> search_result{};
    search_result=find_element_algorithm(name, this->get_circuit_elements());
    if(search_result==nullptr) 
    {
        std::cout<<name<<" not found in "<<this->get_name()<<"."<<std::endl;
    }
    else
    {
        std::cout<<name<<" found in "<<this->get_name()<<"."<<std::endl;
        search_result->print_xblock_data();
    }
}
void Circuit::print_circuit_elements()
{
    std::cout<<'\n'<<"Printing circuit elements for "<<this->get_name()<<"."<<std::endl;
    for(const auto &circuit_element_ptr : this->circuit_elements) 
    {
        if(circuit_element_ptr)
        { 
            circuit_element_ptr->print_xblock_data();
        }
    }
}
void Circuit::add_circuit_element(std::string name, std::shared_ptr<xBlock> &&circuit_element_ptr)
{
    allocate(name, circuit_element_ptr);
}
void Circuit::remove_circuit_element(std::string removal_name)
{
    auto iterator=circuit_elements.begin();
    while (iterator!=circuit_elements.end()) 
    {
        if (*iterator&&(*iterator)->get_name()==removal_name) 
        {
            iterator=circuit_elements.erase(iterator);
            std::cout<<removal_name<<" removed from "<<this->get_name()<< "."<<std::endl;
        } 
        else 
        {
            ++iterator;
        }
    }
    for(auto& element_ptr : circuit_elements) 
    {
        if(!element_ptr) continue;
        if(auto circuit_ptr=dynamic_cast<Circuit*>(element_ptr.get())) 
        {
            circuit_ptr->remove_circuit_element(removal_name);
        }
        else if(auto y_block_ptr=dynamic_cast<yBlock*>(element_ptr.get())) 
        {
            y_block_ptr->remove_y_element(removal_name);
        }
    }
}
void Circuit::add_circuit_elements(std::string name, std::vector<std::shared_ptr<xBlock>> &&circuit_elements_prmtr)
{
  allocate(name, circuit_elements_prmtr);
}
void Circuit::clear_circuit_elements()
{
    circuit_elements.clear();
    std::cout<<this->get_name()<<" circuit elements cleared."<<std::endl;
    z_complex=0.0;
}
void Circuit::html_art(std::ofstream &html)
{
    for (const auto circuit_element_ptr : this->circuit_elements)
    {
        if (!circuit_element_ptr)
        {
            continue;
        } 
        circuit_element_ptr->html_art(html);
    }
}
void Circuit::generate_circuit()
{
    std::ofstream html("circuit.html");
    if (!html.is_open())
    {
        std::cerr << "Failed to create HTML file." << std::endl;
        return;
    }
    html<<R"(<!DOCTYPE html>
          <html>
            <head>
            <meta charset="UTF-8">
            <title>Generated Circuit</title>
            <style>
              body 
              {
                margin: 0;
                font-family: monospace;
                background: #111;
                color: #eee;
                overflow-y: auto;
                text-align: center;
              }
              .wrapper 
              {
                display: flex;
                align-items: flex-start;
                padding: 40px;
                gap: 40px;
              }
              .circuit 
              {
                display: flex;
                flex-direction: column; /* Stack components vertically */
                align-items: center; /* Center components horizontally */
                font-size: 2rem;
                white-space: nowrap;
                min-width: 0; /* Prevent shrinking */
                flex-shrink: 0; /* Prevent shrinking of circuit */
                gap: 20px; /* Space between the components */
                width: auto;  /* Make the circuit container width auto-adjust based on content */
              }
              .component 
              {
                display: flex;
                flex-direction: column;
                align-items: center; /* Ensures the content is centered horizontally */
                justify-content: center; /* Ensures the content is centered vertically */
                margin: 5px 0;
                white-space: nowrap;
                min-width: 50px;
                width: auto;
                display: inline-block;
                font-size: 2rem;
              }
              .spacer 
              {
                width: 20px;
              }
              .branch 
              {
                display: flex;
                flex-direction: column;
                align-items: center;

              }
              .hline 
              {
                height: 4px;
                background: #eee;
                width: 100%;
                margin: 10px 0;
                display: inline-block;
              }
              .vline 
              {
                width: 2px;
                background: #eee;
                flex-grow: 1;
                margin: 5px 0;
                min-height: 30px;
              }
              .parallel 
              {
                display: flex;
                flex-direction: row;
                justify-content: center;
                margin: 10px 0;
                gap: 40px;
                width: auto; 
                flex-wrap: wrap; 
              }
              .wire 
              {
                display: flex;
                justify-content: center; 
                width: 100%;
              }
              .selectableComponent,
              .selectableMap 
              {
                cursor: pointer;
                transition: background 0.3s;
              }
              .selectableComponent:hover,
              .selectableMap:hover 
              {
                background: #444;
              }
              #info-box 
              {
                position: sticky;
                top: 40px;
                background: #222;
                border: 1px solid #555;
                width: 300px;
                font-size: 1.2rem;
                box-shadow: 2px 2px 10px #000;
                border-radius: 5px;
                overflow: hidden;
                height: fit-content;
              }
              #info-header 
              {
                background: #333;
                padding: 5px 10px;
                display: flex;
                justify-content: space-between;
                align-items: center;
                cursor: pointer;
                font-weight: bold;
                color: #ccc;
                border-bottom: 1px solid #555;
              }
              #minimize-btn 
              {
                background: none;
                border: none;
                color: #ccc;
                font-size: 1rem;
                cursor: pointer;
              }
              #minimize-btn:hover 
              {
                color: #fff;
              }
              #info-content 
              {
                padding: 10px;
              }
              #impedance-box 
              {
                position: sticky;
                top: 40px;
                right: 40px; 
                background: #222;
                border: 1px solid #555;
                width: 300px;
                font-size: 1.2rem;
                box-shadow: 2px 2px 10px #000;
                border-radius: 5px;
                overflow: hidden;
                height: fit-content;
                margin-top: 20px; 
              }
              #impedance-header 
              {
                background: #333;
                padding: 5px 10px;
                display: flex;
                justify-content: space-between;
                align-items: center;
                cursor: pointer;
                font-weight: bold;
                color: #ccc;
                border-bottom: 1px solid #555;
              }
              #minimize-impedance-btn 
              {
                background: none;
                border: none;
                color: #ccc;
                font-size: 1rem;
                cursor: pointer;
              }
              #minimize-impedance-btn:hover 
              {
                color: #fff;
              }
              #impedance-content {
                padding: 10px;
                display: block;
              }
            </style>
            </head>
            <body>
            )";

    html<<"<div class=\"circuit\">";
    html<<"<div class=\"component\">+</div>";
    html<<"<div class=\"vline\"></div>";
    this->html_art(html); 
    html << "<div class=\"component\">⏚</div>";
    html << "</div>"; 

    html << R"HTML(
    <div id="info-box">
      <div id="info-header" onclick="toggleInfoBox()">
        <span>ℹ️ Component Info</span>
        <button id="minimize-btn">🗕</button>
      </div>
      <div id="info-content">
        Click a component to see value and impedance.
      </div>
    </div>

    <div id="impedance-box">
      <div id="impedance-header" onclick="toggleImpedanceBox()">
        <span>ℹ️ Circuit Info</span>
        <button id="minimize-impedance-btn">🗕</button>
      </div>
      <div id="impedance-content">
        Impedance Magnitude: )HTML" << this->get_z_magnitude() << R"HTML( [Ω]<br> 
        Impedance Phase: )HTML" << this->get_z_phase() << R"HTML( [rad]
      </div>
    </div>
  
    <script>
      document.addEventListener('DOMContentLoaded', () => {
        document.querySelectorAll('.selectableComponent').forEach(component => {
          component.addEventListener('click', () => {
            const name = component.getAttribute('data-name');
            const type = component.getAttribute('data-type');
            const value = component.getAttribute('data-value');
            const impedance_mag = component.getAttribute('data-impedance_mag');
            const impedance_phase = component.getAttribute('data-impedance_phase');
            document.getElementById('info-content').innerHTML = `
              Name: ${name}<br>
              Type: ${type}<br>
              Value: ${value}<br>
              Impedance Magnitude: ${impedance_mag}<br>
              Impedance Phase: ${impedance_phase}<br>
            `;
          });
        });

        document.querySelectorAll('.selectableMap').forEach(component => {
          component.addEventListener('click', () => {
            const name = component.getAttribute('data-name');
            const impedance_mag = component.getAttribute('data-impedance_mag');
            const impedance_phase = component.getAttribute('data-impedance_phase');
            document.getElementById('info-content').innerHTML = `
              Name: ${name}<br>
              Impedance Magnitude: ${impedance_mag}<br>
              Impedance Phase: ${impedance_phase}<br>
            `;
          });
        });
      });

      function toggleInfoBox() {
        const content = document.getElementById('info-content');
        const btn = document.getElementById('minimize-btn');
        const isVisible = content.style.display !== 'none';

        content.style.display = isVisible ? 'none' : 'block';
        btn.textContent = isVisible ? '🗖' : '🗕';
      }

        function toggleImpedanceBox() {
        const content = document.getElementById('impedance-content');
        const btn = document.getElementById('minimize-impedance-btn');
        const isVisible = content.style.display !== 'none';
        content.style.display = isVisible ? 'none' : 'block';
        btn.textContent = isVisible ? '🗖' : '🗕';
      }
    </script>

    </body>
    </html>
    )HTML";
    html.close();
    std::cout << "HTML file generated successfully!" << std::endl;
}
