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
#include "utils/debug/assert.h"

namespace crusher
{

  template <class component_type, typename... param_types>
  component_type& entity::add_component(param_types... params)
  {
    error_if(_components.find(component_type::id) != _components.end(),
      "entity '%s' already has component '%s.'", _name.c_str(), component_type::id.c_str());

    component_type* comp = new component_type(params...);
    add_component(component_type::id, comp);

    return (*comp);
  }

  template <class component_type>
  component_type& entity::get_component(void) const
  {
    auto& comp = get_component(component_type::id);
    return (dynamic_cast<component_type&>(comp));
  }

  template <class component_type>
  bool entity::has_component(void) const
  {
    return (has_component(component_type::id));
  }

  template <class component_type>
  void entity::remove_component(void)
  {
    remove_component(component_type::id);
  }

}