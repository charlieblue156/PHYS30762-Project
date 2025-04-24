#ifndef COMPONENTLIBRARY_H
#define COMPONENTLIBRARY_H

#include<iostream> 
#include<string>   
#include<unordered_map>
#include"xBlock.h"
#include"yBlock.h"
#include"Circuit.h"
#include"Component.h"

class componentLibrary
{
private:
  std::unordered_map<std::string, std::shared_ptr<Component>> component_library{};
  std::string name{""};
  void duplication_validation(std::shared_ptr<Component> &new_component);
public:
  componentLibrary()=default;
  componentLibrary(const std::string name_prmtr, const std::unordered_map<std::string, std::shared_ptr<Component>> &&component_library_prmtr) : name(name_prmtr), component_library(std::move(component_library_prmtr)){}
  componentLibrary(const componentLibrary&original);
  componentLibrary(componentLibrary &&temp) : component_library(std::move(temp.component_library)){}
  ~componentLibrary(){}
  componentLibrary &operator=(const componentLibrary &other);
  componentLibrary &operator=(componentLibrary &&temp);
  std::shared_ptr<Component> get_component(std::string library_index);
  void component_library_entry(std::shared_ptr<Component> &&new_component);
  std::string get_name() const {return name;}
  void set_name(std::string name_input) {name=name_input;}
};

#endif