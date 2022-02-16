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

  template <typename system_type, typename... param_types>
  system_type& core::add_system(param_types... params)
  {
    system_type* sys = new system_type(params...);
    add_system(system_type::id, sys);

    return (*sys);
  }

  template <typename system_type>
  void core::remove_system(void)
  {
    remove_system(system_type::id);
  }

  template <typename system_type>
  system_type& core::get_system(void)
  {
    auto it = _system_map.find(system_type::id);
    error_if(it == _system_map.end(), 
      "attempting to get a system that the engine doesn't own: '%s'", system_type::id.c_str());

    return (*dynamic_cast<system_type*>(it->second));
  }

  template <typename system_type>
  bool core::has_system(void)
  {
    return has_system(system_type::id);
  }

}
