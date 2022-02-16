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
#include <unordered_map>
#include <vector>
#include <string>
#include "shader_data.h"
#include "graphics/handle/handle.h"
#include "filesystem/path.h"

namespace crusher
{

  // forward declarations
  enum class shader_type;

  /* opengl shader program object */
  class shader_program
  {
    public:
      // ctor / dtor
      shader_program(const std::string& name, const std::string& vert, const std::string& frag);
      shader_program(const path& shader_path);
      ~shader_program(void);

      // public methods
      void bind(void);
      void unbind(void);

      template <typename T>
      void set_data(const std::string& name, const T& data);

      const std::string& get_name(void) const;

    private:
      // typedef
      typedef std::unordered_map<std::string, shader_data> data_map;
      typedef std::pair<std::string, shader_data> data_pair;
      typedef std::vector<path> shader_path_list;

      // private members
      data_map _data;
      std::string _name;
      handle _id;

      // private methods
      unsigned create_shader(shader_type type, const std::string& shader_path);
      bool link_shader(void);
      void create_program(const shader_path_list& shader_paths);

      shader_type type_from_path(const path& shader_path);

  }; // class shader_program


  // template bodies
  template <typename T>
  void shader_program::set_data(const std::string& name, const T& data)
  {
    auto it = _data.find(name);
    // add data
    if (it == _data.end())
    {
      auto data = _data.insert(data_pair(name, shader_data(name, _id)));
      it = data.first;
    }

    // set value
    it->second.set(data);
  }

} // namespace crusher
