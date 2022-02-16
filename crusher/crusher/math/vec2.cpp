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
#include "vec2.h"
#include "math.h"
#include "utils/debug/assert.h"
#include <cmath>

using namespace crusher;

const vec2 vec2::zero = vec2(0.0f, 0.0f);

vec2::vec2(void)
{
}

vec2::vec2(float _x, float _y)
  : x(_x)
  , y(_y)
{
}

void vec2::set(float _x, float _y)
{
  x = _x;
  y = _y;
}

void vec2::set_zero(void)
{
  x = y = 0.0f;
}

float vec2::length(void) const
{
  return (sqrt(length_sq()));
}

float vec2::length_sq(void) const
{
  return (x * x + y * y);
}

vec2& vec2::normalize(void)
{
  float len = length();
  error_if(len == 0.0f, "can't normalize a vector with a 0 length.");
  *this /= len;
  return (*this);
}

vec2 vec2::normalized(void) const
{
  float len = length();
  error_if(len == 0.0f, "can't normalize a vector with a 0 length.");
  return (*this / len);
}

vec2 vec2::operator+(const vec2& rhs) const
{
  return (vec2(x + rhs.x, y + rhs.y));
}

vec2& vec2::operator+=(const vec2& rhs)
{
  x += rhs.x;
  y += rhs.y;

  return (*this);
}

vec2 vec2::operator-(const vec2& rhs) const
{
  return (vec2(x - rhs.x, y - rhs.y));
}

vec2& vec2::operator-=(const vec2& rhs)
{
  x -= rhs.x;
  y -= rhs.y;

  return (*this);
}

vec2 vec2::operator*(float rhs) const
{
  return (vec2(x * rhs, y * rhs));
}

vec2& vec2::operator*=(float rhs)
{
  x *= rhs;
  y *= rhs;

  return (*this);
}

vec2 vec2::operator/(float rhs) const
{
  error_if(rhs == 0.0f, "attempted division by zero.");
  return (vec2(x / rhs, y / rhs));
}

vec2& vec2::operator/=(float rhs)
{
  error_if(rhs == 0.0f, "attempted division by zero.");

  x /= rhs;
  y /= rhs;

  return (*this);
}

vec2 vec2::operator-(void) const
{
  return (vec2(-x, -y));
}

bool vec2::operator==(const vec2& rhs) const
{
  return (float_equal(x, rhs.x) && float_equal(y, rhs.y));
}

bool vec2::operator!=(const vec2& rhs) const
{
  return !(*this == rhs);
}
