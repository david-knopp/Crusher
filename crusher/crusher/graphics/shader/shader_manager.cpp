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

#include "crusher/precompiled.h"
#include "shader_manager.h"

using namespace crusher;

shader_manager::shader_manager(void)
  : _activeShader(nullptr)
{
}

shader_manager::~shader_manager(void)
{
  // delete shaders
  for (auto& shader : _shaders)
    delete shader.second;
}

void shader_manager::bind(const std::string& name)
{
  auto it = _shaders.find(name);
  error_if(it == _shaders.end(), "cannot bind shader program '%s' - program not found.", name.c_str());

  if (it != _shaders.end())
  {
    _activeShader = it->second;
    _activeShader->bind();
  }
}

void shader_manager::unbind(void)
{
  _activeShader->unbind();
  _activeShader = nullptr;
}

void shader_manager::add_program(shader_program* program)
{
  error_if(_shaders.find(program->get_name()) != _shaders.end(), 
           "error adding shader program '%s' - program already exists.", 
           program->get_name().c_str());

  _shaders.insert(shader_pair(program->get_name(), program));
}

void shader_manager::add_program(const std::string& name, const std::string& vert, 
                                 const std::string& frag)
{
  shader_program* shader = new shader_program(name, vert, frag);
  add_program(shader);
}

void shader_manager::remove_program(const std::string& name)
{
  auto it = _shaders.find(name);
  error_if(it == _shaders.end(), "cannot remove shader program '%s' - program not found.", name.c_str());

  // remove shader
  if (it != _shaders.end())
  {
    delete it->second;
    _shaders.erase(name);
  }
}
