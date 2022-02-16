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
#pragma warning(push)
// disable nameless struct/union warning
#pragma warning(disable : 4201)

#include "vec3.h"

namespace crusher
{

  struct vec4
  {
    // static members
    static const vec4 zero;

    // public members
    union
    {
      struct
      {
        float x;
        float y;
        float z;
        float w;
      };

      struct
      {
        float r;
        float g;
        float b;
        float a;
      };

      float data[4];
    };

    // ctors
    vec4(void);
    vec4(float x, float y, float z, float w);
    vec4(const vec3& v, float w);

    // public methods
    void set(float x, float y, float z, float w);
    void set_zero(void);
    float length(void) const;
    float length_sq(void) const;
    vec4& normalize(void);
    vec4 normalized(void) const;

    float dot(const vec4& rhs) const;
    vec4 cross(const vec4& rhs) const;

    // operators
    vec4 operator+(const vec4& rhs) const;
    vec4& operator+=(const vec4& rhs);
    vec4 operator-(const vec4& rhs) const;
    vec4& operator-=(const vec4& rhs);

    vec4 operator*(float rhs) const;
    vec4& operator*=(float rhs);
    vec4 operator/(float rhs) const;
    vec4& operator/=(float rhs);

    vec4 operator-(void) const;

    bool operator==(const vec4& rhs) const;
    bool operator!=(const vec4& rhs) const;

    // static methods
    static float distance(const vec4& a, const vec4& b);
    static float distance_sq(const vec4& a, const vec4& b);

  }; // struct vec4

} // namespace crusher

#pragma warning(pop)
