/*
--------------------------------------------------------------------------------
this file is part of the crusher game engine
Copyright (c) 2014 David Knopp - http://www.davidknopp.net

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
--------------------------------------------------------------------------------
*/

#pragma once
#include "component.h"
#include <string>
#include <unordered_map>

namespace crusher
{

  class component;

  /* crusher's main object class which manages its own components */
  class entity
  {
    public:
      // ctor / dtor
      entity(void);
      entity(const std::string& name);
      virtual ~entity(void);

      // public methods
      const std::string& name(void) const;
      void destroy(void);
      bool dead(void);

      template <class component_type, typename... param_types>
      component_type& add_component(param_types... params);
      component& add_component(const std::string& id, component* comp);

      template <class component_type>
      void remove_component(void);
      void remove_component(const std::string& id);

      template <class component_type>
      component_type& get_component(void) const;
      component& get_component(const std::string& id) const;

      template <class component_type>
      bool has_component(void) const;
      bool has_component(const std::string& id) const;

    private: 
      // typedefs
      typedef std::unordered_map<std::string, component*> component_container;
      typedef std::pair<std::string, component*> component_pair;

      // private members
      component_container _components;
      std::string _name;
      bool _dead;

      // friends
      friend class core;

  }; // entity

} // namespace crusher

// template function definitions
#include "entity_template_bodies.h"
