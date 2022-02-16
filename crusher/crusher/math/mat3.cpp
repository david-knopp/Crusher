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
#include "mat3.h"
#include "vec3.h"
#include "math.h"
#include "utils/debug/assert.h"
#include <algorithm>

using namespace crusher;
using namespace std;

const mat3 mat3::identity = mat3(1.0f, 0.0f, 0.0f,
                                 0.0f, 1.0f, 0.0f,
                                 0.0f, 0.0f, 1.0f);

mat3::mat3(void)
{
}

mat3::mat3(float _m00, float _m01, float _m02,
           float _m10, float _m11, float _m12,
           float _m20, float _m21, float _m22)
  : m00(_m00), m01(_m01), m02(_m02)
  , m10(_m10), m11(_m11), m12(_m12)
  , m20(_m20), m21(_m21), m22(_m22)
{
}

void mat3::set(float _m00, float _m01, float _m02,
               float _m10, float _m11, float _m12,
               float _m20, float _m21, float _m22)
{
  m00 = _m00; m01 = _m01; m02 = _m02;
  m10 = _m10; m11 = _m11; m12 = _m12;
  m20 = _m20; m21 = _m21; m22 = _m22;
}

void mat3::set_identity(void)
{
  set(1.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 1.0f);
}

mat3& mat3::invert(void)
{
  float det = determinant();
  error_if(det == 0.0f, "attempting to invert a non-invertible matrix.");

  set(m11 * m22 - m21 * m12, m02 * m21 - m22 * m01, m01 * m12 - m11 * m02,
      m12 * m20 - m22 * m10, m00 * m22 - m20 * m02, m02 * m10 - m12 * m00,
      m10 * m21 - m20 * m11, m01 * m20 - m21 * m00, m00 * m11 - m10 * m01);

  *this *= (1.0f / det);
  return (*this);
}

mat3 mat3::inverted(void) const
{
  float det = determinant();
  error_if(det == 0.0f, "attempting to invert a non-invertible matrix.");

  det = (1.0f / det);

  return mat3(det * (m11 * m22 - m21 * m12), 
              det * (m02 * m21 - m22 * m01), 
              det * (m01 * m12 - m11 * m02),

              det * (m12 * m20 - m22 * m10), 
              det * (m00 * m22 - m20 * m02), 
              det * (m02 * m10 - m12 * m00),

              det * (m10 * m21 - m20 * m11), 
              det * (m01 * m20 - m21 * m00), 
              det * (m00 * m11 - m10 * m01));
}

mat3& mat3::transpose(void)
{
  swap(m01, m10);
  swap(m02, m20);
  swap(m12, m21);

  return (*this);
}

mat3 mat3::transposed(void) const
{
  return mat3(m00, m10, m20,
              m01, m11, m21,
              m02, m12, m22);
}

float mat3::determinant(void) const
{
  return (m00 * (m11 * m22 - m12 * m21) - 
          m01 * (m10 * m22 - m12 * m20) + 
          m02 * (m10 * m21 - m11 * m20));
}

mat3 mat3::operator+(const mat3& rhs) const
{
  return mat3(m00 + rhs.m00, m01 + rhs.m01, m02 + rhs.m02,
              m10 + rhs.m10, m11 + rhs.m11, m12 + rhs.m12,
              m20 + rhs.m20, m21 + rhs.m21, m22 + rhs.m22);
}

mat3& mat3::operator+=(const mat3& rhs)
{
  m00 += rhs.m00; m01 += rhs.m01; m02 += rhs.m02;
  m10 += rhs.m10; m11 += rhs.m11; m12 += rhs.m12;
  m20 += rhs.m20; m21 += rhs.m21; m22 += rhs.m22;

  return (*this);
}

mat3 mat3::operator-(const mat3& rhs) const
{
  return mat3(m00 - rhs.m00, m01 - rhs.m01, m02 - rhs.m02,
              m10 - rhs.m10, m11 - rhs.m11, m12 - rhs.m12,
              m20 - rhs.m20, m21 - rhs.m21, m22 - rhs.m22);
}

mat3& mat3::operator-=(const mat3& rhs)
{
  m00 -= rhs.m00; m01 -= rhs.m01; m02 -= rhs.m02;
  m10 -= rhs.m10; m11 -= rhs.m11; m12 -= rhs.m12;
  m20 -= rhs.m20; m21 -= rhs.m21; m22 -= rhs.m22;

  return (*this);
}

mat3 mat3::operator*(const mat3& rhs) const
{
  return mat3(m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20,
              m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21,
              m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22,

              m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20,
              m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21,
              m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22,

              m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20,
              m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21,
              m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22);
}

mat3& mat3::operator*=(const mat3& rhs)
{
  set(m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20,
      m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21,
      m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22,

      m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20,
      m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21,
      m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22,

      m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20,
      m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21,
      m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22);

  return (*this);
}

vec3 mat3::operator*(const vec3& rhs) const
{
  return vec3(m00 * rhs.x + m01 * rhs.y + m02 * rhs.z,
              m10 * rhs.x + m11 * rhs.y + m12 * rhs.z,
              m20 * rhs.x + m21 * rhs.y + m22 * rhs.z);
}

mat3 mat3::operator*(float rhs) const
{
  return mat3(m00 * rhs, m01 * rhs, m02 * rhs,
              m10 * rhs, m11 * rhs, m12 * rhs,
              m20 * rhs, m21 * rhs, m22 * rhs);
}

mat3& mat3::operator*=(float rhs)
{
  set(m00 * rhs, m01 * rhs, m02 * rhs,
      m10 * rhs, m11 * rhs, m12 * rhs,
      m20 * rhs, m21 * rhs, m22 * rhs);

  return (*this);
}

mat3 mat3::operator/(float rhs) const
{
  return mat3(m00 / rhs, m01 / rhs, m02 / rhs,
              m10 / rhs, m11 / rhs, m12 / rhs,
              m20 / rhs, m21 / rhs, m22 / rhs);
}

mat3& mat3::operator/=(float rhs)
{
  set(m00 / rhs, m01 / rhs, m02 / rhs,
      m10 / rhs, m11 / rhs, m12 / rhs,
      m20 / rhs, m21 / rhs, m22 / rhs);

  return (*this);
}

bool mat3::operator==(const mat3& rhs) const
{
  return (float_equal(m00, rhs.m00) &&
          float_equal(m01, rhs.m01) &&
          float_equal(m02, rhs.m02) &&
          float_equal(m10, rhs.m10) &&
          float_equal(m11, rhs.m11) &&
          float_equal(m12, rhs.m12) &&
          float_equal(m20, rhs.m20) &&
          float_equal(m21, rhs.m21) &&
          float_equal(m22, rhs.m22));
}

bool mat3::operator!=(const mat3& rhs) const
{
  return !(*this == rhs);
}
