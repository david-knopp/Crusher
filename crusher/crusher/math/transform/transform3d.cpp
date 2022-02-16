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
#include "transform3d.h"
#include "math/math.h"

using namespace crusher;

const std::string transform3d::id = "transform3d";

transform3d::transform3d(void)
  : _m_to_w(mat4::identity)
  , _orient(quat::identity)
  , _pos(0.0f, 0.0f, 0.0f)
  , _scale(1.0f, 1.0f, 1.0f)
  , _dirty(true)
{
}

const vec3& transform3d::position(void) const
{
  return _pos;
}

const quat& transform3d::rotation(void) const
{
  return _orient;
}

vec3 transform3d::rotation_euler_rad(void) const
{
  return _orient.get_euler();
}

vec3 transform3d::rotation_euler_deg(void) const
{
  return rotation_euler_rad() * RADIAN_TO_DEGREE;
}

const vec3& transform3d::scale(void) const
{
  return _scale;
}

vec3 transform3d::right(void)
{
  const mat4& m_to_w = model_to_world();
  return vec3(m_to_w.m00, m_to_w.m10, m_to_w.m20);
}

vec3 transform3d::up(void)
{
  const mat4& m_to_w = model_to_world();
  return vec3(m_to_w.m01, m_to_w.m11, m_to_w.m21);
}

vec3 transform3d::forward(void)
{
  const mat4& m_to_w = model_to_world();
  return vec3(m_to_w.m02, m_to_w.m12, m_to_w.m22);
}

void transform3d::set_position(const vec3& pos)
{
  _dirty = true;
  _pos = pos;
}

void transform3d::set_position(float x, float y, float z)
{
  _dirty = true;
  _pos.set(x, y, z);
}

void transform3d::set_rotation(const quat& rot)
{
  _dirty = true;
  _orient = rot;
}

void transform3d::set_euler_rad(const vec3& rad)
{
  set_euler_rad(rad.x, rad.y, rad.z);
}

void transform3d::set_euler_rad(float rad_x, float rad_y, float rad_z)
{
  _dirty = true;
  _orient.set_euler(rad_x, rad_y, rad_z);
}

void transform3d::set_euler_deg(const vec3& deg)
{
  set_euler_deg(deg.x, deg.y, deg.z);
}

void transform3d::set_euler_deg(float deg_x, float deg_y, float deg_z)
{
  _dirty = true;
  _orient.set_euler(deg_x * DEGREE_TO_RADIAN, deg_y * DEGREE_TO_RADIAN, deg_z * DEGREE_TO_RADIAN);
}

void transform3d::set_scale(const vec3& scale)
{
  _dirty = true;
  _scale = scale;
}

void transform3d::set_scale(float x, float y, float z)
{
  _dirty = true;
  _scale.set(x, y, z);
}

const mat4& transform3d::model_to_world(void)
{
  if (_dirty)
    return calculate_m_to_w();

  return _m_to_w;
}

const mat4& transform3d::calculate_m_to_w(void)
{
  _dirty = false;

  // combine rotation and translation
  _m_to_w = _orient.to_mat4();
  _m_to_w.m03 = _pos.x;
  _m_to_w.m13 = _pos.y;
  _m_to_w.m23 = _pos.z;

  // create scale mat
  mat4 scale(_scale.x, 0.0f,     0.0f,     0.0f,
             0.0f,     _scale.y, 0.0f,     0.0f,
             0.0f,     0.0f,     _scale.z, 0.0f,
             0.0f,     0.0f,     0.0f,     1.0f);
  
  _m_to_w *= scale;

  return _m_to_w;
}
