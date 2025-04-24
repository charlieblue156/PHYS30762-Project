#include <iostream> 
#include <string>   
#include<unordered_map>
#include"xBlock.h"
#include "yBlock.h"
#include "Circuit.h"
#include "Component.h"
#include "componentLibrary.h"

void componentLibrary::duplication_validation(std::shared_ptr<Component> &new_component)
{
    for(const auto& [existing_name, existing_component] : component_library)
    {
        if(existing_name==new_component->get_name())
        {
            std::cout<<"A component with name "<<new_component->get_name()<<" already exists in "<<name<<". Please choose a new name."<<std::endl;
            return;
        }
        else if((existing_component->get_value()==new_component->get_value())&&(typeid(*existing_component)==typeid(*new_component)))
        {
            if(typeid(*existing_component)==typeid(Resistor)) 
            {
                std::cout<<"There exists a resistor in "<<name<<" of resistance "<<new_component->get_value()<<"[\u2126]. Select a new resiatance."<<std::endl;
                return;
            }
            else if(typeid(*existing_component)==typeid(Capacitor)) 
            {
                std::cout<<"There exists a capacitor in "<<name<<" of capacitance "<<new_component->get_value()<<"[F]. Select a new capacitance."<<std::endl;
                return;
            }
            else if(typeid(*existing_component)==typeid(Inductor)) 
            {
                std::cout<<"There exists an inductor in "<<name<<" of inductance "<<new_component->get_value()<<"[H]. Select a new inductance."<<std::endl;
                return;
            }
        }
    }
    std::cout<<"Duplication check success."<<std::endl;
    component_library[new_component->get_name()]=new_component;
    std::cout<<new_component->get_name()<<" added to "<<name<<"."<<std::endl;
    return;
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
        std::cout<<library_index<<" found in "<<name<<"."<<std::endl;
        return iterator->second;
    } 
    else
    {
        std::cout<<library_index<<" not found in "<<name<<"."<<std::endl;
        return nullptr;
    }
}
void componentLibrary::component_library_entry(std::shared_ptr<Component> &&new_component)
{
    try
    {
        duplication_validation(new_component);
    }
    catch(const std::bad_alloc& memFail)
    {
        std::cerr<<"Memory allocation failed for "<<new_component->get_name()<<"."<<std::endl;
    }
}