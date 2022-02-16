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
#include "quat.h"
#include "math.h"

using namespace crusher;

const quat quat::identity = quat(0.0f, 0.0f, 0.0f, 1.0f);

quat::quat(void)
{
}

quat::quat(float _x, float _y, float _z, float _w)
  : x(_x)
  , y(_y)
  , z(_z)
  , w(_w)
{
}

quat::quat(float radians, const vec4& axis)
{
  set(radians, axis);
}

quat::quat(float radians, const vec3& axis)
{  
  set(radians, axis);
}

quat::quat(const mat4& m)
{  
  set(m);
}

quat::quat(const mat3& m)
{  
  set(m);
}

quat& quat::normalize(void)
{  
  float length = dot(*this);

  error_if(length == 0, "cannot normalize a quaternion of length 0.");

  v /= length;
  s /= length;

  return *this;
}

quat quat::normalized(void) const
{  
  return quat(*this).normalize();
}

quat& quat::invert(void)
{  
  v = -v;
  return *this;
}

quat quat::inverted(void) const
{  
  return quat(-x, -y, -z, w);
}

float quat::dot(const quat& rhs) const
{
  return (w * rhs.w + v.dot(rhs.v));
}

void quat::set_explicit(float _x, float _y, float _z, float _w)
{
  x = _x;
  y = _y;
  z = _z;
  w = _w;
}

void quat::set_explicity(float s, const vec3& v)
{
  set_explicit(s, v.x, v.y, v.z);
}

void quat::set(float angle_rad, float axis_x, float axis_y, float axis_z)
{  
  float length = sqrt(axis_x * axis_x + axis_y * axis_y + axis_z * axis_z);
  error_if(length <= EPSILON, "can't rotate about a zero axis.");
  float half_angle = angle_rad / 2.0f;
  float sin_theta2 = sin(half_angle);

  x = sin_theta2 * axis_x / length;
  y = sin_theta2 * axis_y / length;
  z = sin_theta2 * axis_z / length;
  w = cos(half_angle);
}

void quat::set(float angle_rad, const vec4& axis)
{  
  set(angle_rad, axis.x, axis.y, axis.z);
}

void quat::set(float angle_rad, const vec3& axis)
{  
  set(angle_rad, axis.x, axis.y, axis.z);
}

void quat::set_euler(float rad_x, float rad_y, float rad_z)
{
  float cos_x = cos(rad_x / 2.0f);
  float cos_y = cos(rad_y / 2.0f);
  float cos_z = cos(rad_z / 2.0f);

  float sin_x = sin(rad_x / 2.0f);
  float sin_y = sin(rad_y / 2.0f);
  float sin_z = sin(rad_z / 2.0f);

  w = cos_y * cos_x * cos_z + sin_y * sin_x * sin_z;
  x = cos_y * sin_x * cos_z + sin_y * cos_x * sin_z;
  y = sin_y * cos_x * cos_z - cos_y * sin_x * sin_z;
  z = cos_y * cos_x * sin_z - sin_y * sin_x * cos_z;
}

vec3 quat::get_euler(void) const
{
  vec3 euler;
  float sin_x = -2.0f * (y * z - w * x);

  // check for gimbal lock
  if (float_equal(sin_x, 1.0f))
  {
    euler.x = PI_2 * sin_x;
    euler.y = atan2(-x * z + w * y, 0.5f - y * y - z * z);
    euler.z = 0.0f;
  }
  else
  {
    euler.x = asin(sin_x);
    euler.y = atan2(x * z + w * y, 0.5f - x * x - y * y);
    euler.z = atan2(x * y + w * z, 0.5f - x * x - z * z);
  }

  return euler;
}

void quat::set(const mat4& m)
{  
  float trace = m.m00 + m.m11 + m.m22;

  if (trace > 0) 
  { 
    float s = sqrt(trace + 1.0f) * 2.0f;
    w = 0.25f * s;
    x = (m.m21 - m.m12) / s;
    y = (m.m02 - m.m20) / s; 
    z = (m.m10 - m.m01) / s; 
  } 
  else if (m.m00 > m.m11 && m.m00 > m.m22) 
  { 
    float s = sqrt(1.0f + m.m00 - m.m11 - m.m22) * 2.0f;
    w = (m.m21 - m.m12) / s;
    x = 0.25f * s;
    y = (m.m01 + m.m10) / s; 
    z = (m.m02 + m.m20) / s; 
  } 
  else if (m.m11 > m.m22) 
  { 
    float s = sqrt(1.0f + m.m11 - m.m00 - m.m22) * 2.0f;
    w = (m.m02 - m.m20) / s;
    x = (m.m01 + m.m10) / s; 
    y = 0.25f * s;
    z = (m.m12 + m.m21) / s; 
  } 
  else 
  { 
    float s = sqrt(1.0f + m.m22 - m.m00 - m.m11) * 2.0f;
    w = (m.m10 - m.m01) / s;
    x = (m.m02 + m.m20) / s;
    y = (m.m12 + m.m21) / s;
    z = 0.25f * s;
  }
}

void quat::set(const mat3& m)
{  
  float trace = m.m00 + m.m11 + m.m22;

  if (trace > 0) 
  { 
    float s = sqrt(trace + 1.0f) * 2.0f;
    w = 0.25f * s;
    x = (m.m21 - m.m12) / s;
    y = (m.m02 - m.m20) / s; 
    z = (m.m10 - m.m01) / s; 
  } 
  else if (m.m00 > m.m11 && m.m00 > m.m22) 
  { 
    float s = sqrt(1.0f + m.m00 - m.m11 - m.m22) * 2.0f;
    w = (m.m21 - m.m12) / s;
    x = 0.25f * s;
    y = (m.m01 + m.m10) / s; 
    z = (m.m02 + m.m20) / s; 
  } 
  else if (m.m11 > m.m22) 
  { 
    float s = sqrt(1.0f + m.m11 - m.m00 - m.m22) * 2.0f;
    w = (m.m02 - m.m20) / s;
    x = (m.m01 + m.m10) / s; 
    y = 0.25f * s;
    z = (m.m12 + m.m21) / s; 
  } 
  else 
  { 
    float s = sqrt(1.0f + m.m22 - m.m00 - m.m11) * 2.0f;
    w = (m.m10 - m.m01) / s;
    x = (m.m02 + m.m20) / s;
    y = (m.m12 + m.m21) / s;
    z = 0.25f * s;
  }
}

mat4 quat::to_mat4(void) const
{  
  float xx = 2 * x * x;
  float yy = 2 * y * y;
  float zz = 2 * z * z;
  float xy = 2 * x * y;
  float xz = 2 * x * z;
  float yz = 2 * y * z;
  float wx = 2 * w * x;
  float wy = 2 * w * y;
  float wz = 2 * w * z;

  return mat4(1.0f - (yy + zz), xy - wz,          xz + wy,          0.0f, 
              xy + wz,          1.0f - (xx + zz), yz - wx,          0.0f,
              xz - wy,          yz + wx,          1.0f - (xx + yy), 0.0f,
              0.0f,             0.0f,             0.0f,             1.0f);
}

mat3 quat::to_mat3(void) const
{  
  float xx = 2 * x * x;
  float yy = 2 * y * y;
  float zz = 2 * z * z;
  float xy = 2 * x * y;
  float xz = 2 * x * z;
  float yz = 2 * y * z;
  float wx = 2 * w * x;
  float wy = 2 * w * y;
  float wz = 2 * w * z;

  return mat3(1.0f - (yy + zz), xy - wz,          xz + wy,        
              xy + wz,          1.0f - (xx + zz), yz - wx,        
              xz - wy,          yz + wx,          1.0f - (xx + yy));
}

void quat::to_matrix(mat4& out_matrix) const
{  
  out_matrix = to_mat4();
}

void quat::to_matrix(mat3& out_matrix) const
{  
  out_matrix = to_mat3();
}

quat quat::operator*(const quat& rhs) const
{  
  vec3 v_res = v.cross(rhs.v) + (rhs.v * s) + (v * rhs.s);
  return quat(v_res.x, v_res.y, v_res.z, s * rhs.s - v.dot(rhs.v));
}

quat& quat::operator*=(const quat& rhs)
{  
  *this = *this * rhs;
  return *this;
}

quat quat::operator-(void) const
{  
  return quat(-x, -y, -z, -w);
}

bool quat::operator==(const quat& rhs) const
{  
  return (float_equal(s, rhs.s) && v == rhs.v);
}

bool quat::operator!=(const quat& rhs) const
{  
  return !(*this == rhs);
}
