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
#include "vec4.h"
#include "math.h"
#include "utils/debug/assert.h"
#include <cmath>

using namespace crusher;

const vec4 vec4::zero = vec4(0.0f, 0.0f, 0.0f, 0.0f);

vec4::vec4(void)
{
}

vec4::vec4(float _x, float _y, float _z, float _w)
  : x(_x)
  , y(_y)
  , z(_z)
  , w(_w)
{
}

vec4::vec4(const vec3& v, float _w)
  : x(v.x)
  , y(v.y)
  , z(v.z)
  , w(_w)
{
}

void vec4::set(float _x, float _y, float _z, float _w)
{
  x = _x;
  y = _y;
  z = _z;
  w = _w;
}

void vec4::set_zero(void)
{
  x = y = z = w = 0.0f;
}

float vec4::length(void) const
{
  return sqrt(length_sq());
}

float vec4::length_sq(void) const
{
  return (x * x + y * y + z * z + w * w);
}

vec4& vec4::normalize(void)
{
  float len = length();
  error_if(len == 0.0f, "can't normalize a vector with a 0 length.");

  *this /= len;
  return (*this);
}

vec4 vec4::normalized(void) const
{
  float len = length();
  error_if(len == 0.0f, "can't normalize a vector with a 0 length.");

  return (*this / len);
}

float vec4::dot(const vec4& rhs) const
{
  return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
}

vec4 vec4::cross(const vec4& rhs) const
{
  return vec4(y * rhs.z - z * rhs.y,
              z * rhs.x - x * rhs.z,
              x * rhs.y - y * rhs.x,
              0.0f);
}

vec4 vec4::operator+(const vec4& rhs) const
{
  return vec4(x + rhs.x,
              y + rhs.y,
              z + rhs.z,
              w + rhs.w);
}

vec4& vec4::operator+=(const vec4& rhs)
{
  set(x + rhs.x,
      y + rhs.y,
      z + rhs.z,
      w + rhs.w);

  return (*this);
}

vec4 vec4::operator-(const vec4& rhs) const
{
  return vec4(x - rhs.x,
              y - rhs.y,
              z - rhs.z,
              w - rhs.w);
}

vec4& vec4::operator-=(const vec4& rhs)
{
  set(x - rhs.x,
      y - rhs.y,
      z - rhs.z,
      w - rhs.w);

  return (*this);
}

vec4 vec4::operator*(float rhs) const
{
  return vec4(x * rhs,
              y * rhs,
              z * rhs,
              w * rhs);
}

vec4& vec4::operator*=(float rhs)
{
  set(x * rhs,
      y * rhs,
      z * rhs,
      w * rhs);

  return (*this);
}

vec4 vec4::operator/(float rhs) const
{
  return vec4(x / rhs,
              y / rhs,
              z / rhs,
              w / rhs);
}

vec4& vec4::operator/=(float rhs)
{
  set(x / rhs,
      y / rhs,
      z / rhs,
      w / rhs);

  return (*this);
}

vec4 vec4::operator-(void) const
{
  return vec4(-x, -y, -z, -w);
}

bool vec4::operator==(const vec4& rhs) const
{
  return (float_equal(x, rhs.x) && 
          float_equal(y, rhs.y) &&
          float_equal(z, rhs.z) &&
          float_equal(w, rhs.w));
}

bool vec4::operator!=(const vec4& rhs) const
{
  return !(*this == rhs);
}

float vec4::distance(const vec4& a, const vec4& b)
{
  vec4 diff = b - a;
  return (diff.length());
}

float vec4::distance_sq(const vec4& a, const vec4& b)
{
  vec4 diff = b - a;
  return (diff.length_sq());
}
