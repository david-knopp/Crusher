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
#include "shader_program.h"

namespace crusher
{

  class shader_manager
  {
    public:
      // ctor / dtor
      shader_manager(void);
      ~shader_manager(void);

      // public methods
      void bind(const std::string& name);
      void unbind(void);

      template <typename T>
      void set_data(const std::string& name, const T& data);

      void add_program(shader_program* program);
      void add_program(const std::string& name, const std::string& vert, const std::string& frag);

      void remove_program(const std::string& name);

    private:
      // typedefs
      typedef std::unordered_map<std::string, shader_program*> shader_map;
      typedef std::pair<std::string, shader_program*> shader_pair;

      // private members
      shader_map _shaders;
      shader_program* _activeShader;
  }; // class shader_manager

  // template bodies
  template <typename T>
  void shader_manager::set_data(const std::string& name, const T& data)
  {
    if (_activeShader != nullptr)
      _activeShader->set_data(name, data);
  }

} // namespace crusher
