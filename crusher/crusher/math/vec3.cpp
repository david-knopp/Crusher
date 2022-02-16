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
#include "vec3.h"
#include "math.h"
#include "utils/debug/assert.h"
#include <cmath>

using namespace crusher;

const vec3 vec3::zero = vec3(0.0f, 0.0f, 0.0f);

vec3::vec3(void)
{
}

vec3::vec3(float _x, float _y, float _z)
  : x(_x)
  , y(_y)
  , z(_z)
{
}

void vec3::set(float _x, float _y, float _z)
{
  x = _x;
  y = _y;
  z = _z;
}

void vec3::set_zero(void)
{
  x = y = z = 0.0f;
}

float vec3::length(void) const
{
  return (sqrt(length_sq()));
}

float vec3::length_sq(void) const
{
  return (dot(*this));
}

vec3& vec3::normalize(void)
{
  float len = length();
  error_if(len == 0.0f, "can't normalize a vector with a 0 length.");
  *this /= len;
  return (*this);
}

vec3 vec3::normalized(void) const
{
  float len = length();
  error_if(len == 0.0f, "can't normalize a vector with a 0 length.");
  return (*this / len);
}

float vec3::dot(const vec3& rhs) const
{
  return (x * rhs.x + y * rhs.y + z * rhs.z);
}

vec3 vec3::cross(const vec3& rhs) const
{
  return vec3(y * rhs.z - z * rhs.y,
              z * rhs.x - x * rhs.z,
              x * rhs.y - y * rhs.x);
}

vec3 vec3::operator+(const vec3& rhs) const
{
  return (vec3(x + rhs.x, y + rhs.y, z + rhs.z));
}

vec3& vec3::operator+=(const vec3& rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;

  return (*this);
}

vec3 vec3::operator-(const vec3& rhs) const
{
  return (vec3(x - rhs.x, y - rhs.y, z - rhs.z));
}

vec3& vec3::operator-=(const vec3& rhs)
{
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;

  return (*this);
}

vec3 vec3::operator*(float rhs) const
{
  return (vec3(x * rhs, y * rhs, z * rhs));
}

vec3& vec3::operator*=(float rhs)
{
  x *= rhs;
  y *= rhs;
  z *= rhs;

  return (*this);
}

vec3 vec3::operator/(float rhs) const
{
  return (vec3(x / rhs, y / rhs, z / rhs));
}

vec3& vec3::operator/=(float rhs)
{
  x /= rhs;
  y /= rhs;
  z /= rhs;

  return (*this);
}

vec3 vec3::operator-(void) const
{
  return (vec3(-x, -y, -z));
}

bool vec3::operator==(const vec3& rhs) const
{
  return (float_equal(x, rhs.x) && 
          float_equal(y, rhs.y) &&
          float_equal(z, rhs.z));
}

bool vec3::operator!=(const vec3& rhs) const
{
  return !(*this == rhs);
}

float vec3::distance(const vec3& a, const vec3& b)
{
  vec3 diff = b - a;
  return (diff.length());
}

float vec3::distance_sq(const vec3& a, const vec3& b)
{
  vec3 diff = b - a;
  return (diff.length_sq());
}

vec3 vec3::cross(const vec3& lhs, const vec3& rhs)
{
  return lhs.cross(rhs);
}
