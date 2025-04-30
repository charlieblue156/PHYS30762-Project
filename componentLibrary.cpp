/*
Charlie Taylor - 29/04/25 - 11072486
componentLibrary source file.
*/

#include<iostream> 
#include<string>   
#include<unordered_map>
#include<stdexcept>
#include<sstream>
#include"xBlock.h"
#include "yBlock.h"
#include "Circuit.h"
#include "Component.h"
#include "componentLibrary.h"

void componentLibrary::duplication_validation(std::shared_ptr<Component> new_component)
{
    if(component_library.empty())
    {
        if(!new_component->get_value().has_value())
        {
            throw std::invalid_argument("Value for "+new_component->get_name()+" invalid.\n");
        }
    }
    else
    {
        for(const auto& [existing_name, existing_component] : component_library)
        {
            try
            {
                if(existing_name==new_component->get_name())
                {
                    throw std::invalid_argument("A component with name "+new_component->get_name()+" already exists in "+name+". Please choose a new name.\n");
                    
                }
                else if((existing_component->get_value().value()==new_component->get_value().value())&&(typeid(*existing_component)==typeid(*new_component)))
                {
                    std::ostringstream ss;
                    ss<<new_component->get_value().value();
                    if(typeid(*existing_component)==typeid(Resistor)) 
                    {
                        throw std::invalid_argument("There exists a resistor in "+name+" of resistance "+ss.str()+"[\u2126]. Select a new resiatance.\n");
                    }
                    else if(typeid(*existing_component)==typeid(Capacitor)) 
                    {
                        throw std::invalid_argument("There exists a capacitor in "+name+" of capacitance "+ss.str()+"[F]. Select a new capacitance.\n");
                    }
                    else if(typeid(*existing_component)==typeid(Inductor)) 
                    {
                        throw std::invalid_argument("There exists an inductor in "+name+" of inductance "+ss.str()+"[H]. Select a new inductance.\n");
                    }
                }
            }
            catch(std::bad_optional_access &e){}
        }
    }
    std::cout<<"Duplication check success.\n"<<std::endl;
}
void componentLibrary::allocate(std::shared_ptr<Component> new_component)
{
    try
    {
        duplication_validation(new_component);
        component_library[new_component->get_name()]=new_component;
        std::cout<<new_component->get_name()<<" added to "<<name<<".\n"<<std::endl;
    }
    catch(const std::bad_alloc& memFail)
    {
        std::cerr<<"Memory allocation failed for "<<new_component->get_name()<<".\n"<<std::endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr<<e.what()<<std::endl;
    }
    catch(const std::bad_optional_access& e)
    {
        std::cerr<<"Value for "<<new_component->get_name()<<" invalid.\n"<<std::endl;
    }
}
componentLibrary::componentLibrary(const componentLibrary&original) : component_library{original.component_library}
{
    for(const auto &[name, component_ptr] : original.component_library) 
    {
        if(component_ptr)
        { 
            component_library[name]=component_ptr;
        }
    }
}
std::shared_ptr<Component> componentLibrary::get_component(std::string library_index)
{
    std::cout<<'\n'<<"Searching for "<<library_index<<" in "<<name<<"."<<std::endl;
    auto iterator=component_library.find(library_index);
    if (iterator!=component_library.end()) 
    {
        std::cout<<library_index<<" found in "<<name<<".\n"<<std::endl;
        return iterator->second;
    } 
    else
    {
        std::cout<<library_index<<" not found in "<<name<<".\n"<<std::endl;
        return nullptr;
    }
}
void componentLibrary::component_library_entry(const std::string &type_prmtr, const std::string &name_prmtr, const double value_prmtr)
{
    if(type_prmtr=="Resistor")
    {
        Resistor temp(name_prmtr, value_prmtr);
        allocate(std::make_shared<Resistor>(temp));
    }
    else if(type_prmtr=="Capacitor")
    {
        Capacitor temp(name_prmtr, value_prmtr);
        allocate(std::make_shared<Capacitor>(temp));
    }
    else if(type_prmtr=="Inductor")
    {
        Inductor temp(name_prmtr, value_prmtr);
        allocate(std::make_shared<Inductor>(temp));
    }
    else
    {
        std::cerr<<"Invalid type name, component entry into "<<name<<" failed for "<<name_prmtr<<". set the type name to either \"Resistor\", \"Capacitor\", or \"Inductor\" exactly.\n"<<std::endl;
    }

}
void componentLibrary::print_component_library() const
{
  std::cout<<'\n'<<"Printing component library "<<name<<":"<<std::endl;
  for(const auto& [name, component] : component_library) 
  {
    if(component)
    { 
      component->print_xblock_data();
    }
  }
}