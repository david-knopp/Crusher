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
#include "entity.h"
#include <string>

namespace crusher
{

  class entity;

  /* an element of data or logic belonging to an entity */
  class component
  {
    public:
      // static members
      // id used to identify component, must be defined uniquely per subclass
      static const std::string id;

      // ctor / dtor
      component();
      virtual ~component();

      // public methods
      entity& owner(void) const;

      template <typename component_type>
      component_type& get_component(void) const;
      component& get_component(const std::string& id) const;

      template<typename system_type>
      system_type& get_system(void) const;

      // virtual methods
      // called when component is added to an entity
      virtual void startup(void) {}
      // called when component is removed from an entity
      virtual void shutdown(void) {}

    private:
      // private members
      entity* _owner;

      friend class entity;

  };

} // namespace crusher

// template function definitions
#include "component_template_bodies.h"
