#ifndef COMPONENTFAILURE_H
#define COMPONENTFAILURE_H

#include<iostream>
#include<string>

class ComponentFailure : public std::invalid_argument
{
public:
  std::string component_name;
  ComponentFailure(const std::string &name, const std::string &message) : component_name(name), std::invalid_argument(message) {}
  const std::string &get_component_name() const { return component_name; }
};
#endif