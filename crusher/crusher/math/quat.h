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

#include "vec4.h"
#include "vec3.h"
#include "mat4.h"
#include "mat3.h"

namespace crusher
{

  /* quaternion for representing orientation */
  struct quat
  {
    // static members
    static const quat identity;

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
        vec3 v;
        float s;
      };

      float data[4];
    };

    // ctors
    quat(void);
    quat(float x, float y, float z, float w);
    quat(float radians, const vec4& axis);
    quat(float radians, const vec3& axis);
    quat(const mat4& m);
    quat(const mat3& m);

    // public methods
    quat& normalize(void);
    quat normalized(void) const;

    quat& invert(void);
    quat inverted(void) const;

    float dot(const quat& rhs) const;

    void set_explicit(float x, float y, float z, float w);
    void set_explicity(float s, const vec3& v);

    // axis-angle setters
    void set(float angle_rad, float axis_x, float axis_y, float axis_z);
    void set(float angle_rad, const vec4& axis);
    void set(float angle_rad, const vec3& axis);

    // euler
    void set_euler(float rad_x, float rad_y, float rad_z);
    vec3 get_euler(void) const;

    // matrix setters
    void set(const mat4& m);
    void set(const mat3& m);

    // conversions
    mat4 to_mat4(void) const;
    mat3 to_mat3(void) const;

    void to_matrix(mat4& out_matrix) const;
    void to_matrix(mat3& out_matrix) const;

    // operators
    quat operator*(const quat& rhs) const;
    quat& operator*=(const quat& rhs);

    quat operator-(void) const;

    bool operator==(const quat& rhs) const;
    bool operator!=(const quat& rhs) const;

  }; // struct quat

} // namespace crusher

#pragma warning(pop)
