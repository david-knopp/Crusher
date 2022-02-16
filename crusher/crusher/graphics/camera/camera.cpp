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
#include "camera.h"
#include "math/vec4.h"
#include "math/quat.h"
#include "math/transform/transform3d.h"
#include "math/math.h"
#include <cmath>

using namespace crusher;

const std::string camera::id = "camera";

camera::camera(void)
{
}

camera::camera(float fov, float z_near, float z_far)
  : _fov(fov * DEGREE_TO_RADIAN)
  , _near(z_near)
  , _far(z_far)
{
}

void camera::set_viewport(float width, float height)
{
  _viewport.set(width, height);
}

void camera::set_viewport(const vec2& viewport)
{
  set_viewport(viewport.x, viewport.y);
}

void camera::set_fov(float fov)
{
  _fov = fov * DEGREE_TO_RADIAN;
}

mat4 camera::get_view_matrix(void) const
{
  vec4 right(1.0f, 0.0f, 0.0f, 0.0f);
  vec4 up(0.0f, 1.0f, 0.0f, 0.0f);
  vec4 forward(0.0f, 0.0f, 1.0f, 0.0f);

  transform3d& trans = get_component<transform3d>();
  mat4 rot = trans.rotation().to_mat4();

  right = rot * right;
  up = rot * up;
  forward = rot * forward;

  mat4 view(right.x,   right.y,   right.z,   0.0f,
            up.x,      up.y,      up.z,      0.0f,
            forward.x, forward.y, forward.z, 0.0f,
            0.0f,      0.0f,      0.0f,      1.0f);

  const vec3& pos = trans.position();
  mat4 translation(1.0f, 0.0f, 0.0f, -pos.x,
                   0.0f, 1.0f, 0.0f, -pos.y,
                   0.0f, 0.0f, 1.0f, -pos.z,
                   0.0f, 0.0f, 0.0f, 1.0f);

  return view * translation;
  //return mat4::identity;
}

mat4 camera::get_proj_matrix(void) const
{
  float aspect_ratio = _viewport.x / _viewport.y;
  float x = 1.0f / tanf(_fov / 2.0f);
  float y = aspect_ratio * x;
  float z = (_far + _near) / (_near - _far);
  float trans = (2.0f * _far * _near) / (_near - _far);

  return mat4(   x, 0.0f,  0.0f,  0.0f,
              0.0f,    y,  0.0f,  0.0f,
              0.0f, 0.0f,     z, trans,
              0.0f, 0.0f, -1.0f,  0.0f);
}
