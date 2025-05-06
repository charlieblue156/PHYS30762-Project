/*
Charlie Taylor - 29/04/25 - 11072486
componentLibrary class header file. This class contains a library of components, which are stored in an unordered map. Only components which have 
valid and greater than zero values may be added. This gives a seal of approval for components when added to a circuit. Components may be accessed
directly by name, for creating shared ptrs to them. No duplicate names or values are allowed in the library. The class contains functions to add, 
remove, and clear components from the library, as well as to print the component library.
*/

#ifndef COMPONENTLIBRARY_H
#define COMPONENTLIBRARY_H

#include<iostream> 
#include<string>   
#include<unordered_map>
#include"XBlock.h"
#include"YBlock.h"
#include"Circuit.h"
#include"Component.h"

class ComponentLibrary
{
private:
  std::unordered_map<std::string, std::shared_ptr<Component>> component_library{};
  std::string name{""};
  void duplication_validation(std::shared_ptr<Component> new_component);
  void allocate(std::shared_ptr<Component> new_component);
public:
  ComponentLibrary(){}
  ComponentLibrary(const std::string name_prmtr, const std::unordered_map<std::string, std::shared_ptr<Component>> &&component_library_prmtr) : name(name_prmtr), component_library(std::move(component_library_prmtr)){}
  ComponentLibrary(const ComponentLibrary&original);
  ComponentLibrary(ComponentLibrary &&temp) : component_library(std::move(temp.component_library)){}
  ~ComponentLibrary(){}
  ComponentLibrary &operator=(const ComponentLibrary &other);
  ComponentLibrary &operator=(ComponentLibrary &&temp);
  std::shared_ptr<Component> get_component(std::string library_index);
  void component_library_entry(const std::string &type_prmtr, const std::string &name_prmtr, const double value_prmtr);
  std::string get_name() const {return name;}
  void set_name(std::string name_input) {name=name_input;}
  void print_component_library() const;
};

#endif