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
#include "shader_data.h"
#include "graphics/types/object_type.h"
// math
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat3.h"
#include "math/mat4.h"

using namespace crusher;

shader_data::shader_data(const std::string& name, const handle& shader_id)
  : _name(name)
{
  set_location(shader_id);
}

shader_data::~shader_data(void)
{
}

int shader_data::get_location(void) const
{
  return _location;
}

const std::string& shader_data::get_name(void) const
{
  return _name;
}

template <>
void shader_data::set<>(const float& data)
{
  glUniform1f(_location, data);
}

template <>
void shader_data::set<>(const vec2& data)
{
  glUniform2fv(_location, 1, data.data);
}

template <>
void shader_data::set<>(const vec3& data)
{
  glUniform3fv(_location, 1, data.data);
}

template <>
void shader_data::set<>(const vec4& data)
{
  glUniform4fv(_location, 1, data.data);
}

template <>
void shader_data::set<>(const mat3& data)
{
  glUniformMatrix3fv(_location, 1, true, &data.data[0]);
}

template <>
void shader_data::set<>(const mat4& data)
{
  glUniformMatrix4fv(_location, 1, true, &data.data[0]);
}

template <>
void shader_data::set<>(const int& data)
{
  glUniform1i(_location, data);
}

template<>
void shader_data::set<>(const bool& data)
{
  glUniform1i(_location, data);
}

bool shader_data::valid(void) const
{
  return (_location != -1);
}

void shader_data::set_location(const handle& shader_id)
{
  _location = glGetUniformLocation(shader_id, _name.c_str());
  error_if(_location == -1, "uniform '%s' not found.", _name.c_str());
}
