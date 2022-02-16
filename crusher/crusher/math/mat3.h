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

namespace crusher
{
  // forward declarations
  struct vec3;

  /* 3x3 matrix of floats */
  struct mat3
  {
    // static members
    static const mat3 identity;

    // public members
    union
    {
      struct
      {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
      };

      float m[3][3];
      float data[9];
    };

    // ctors
    mat3(void);
    mat3(float m00, float m01, float m02,
         float m10, float m11, float m12,
         float m20, float m21, float m22);

    // public methods
    void set(float m00, float m01, float m02,
             float m10, float m11, float m12,
             float m20, float m21, float m22);
    void set_identity(void);

    mat3& invert(void);
    mat3 inverted(void) const;

    mat3& transpose(void);
    mat3 transposed(void) const;

    float determinant(void) const;

    // operators
    mat3 operator+(const mat3& rhs) const;
    mat3& operator+=(const mat3& rhs);
    mat3 operator-(const mat3& rhs) const;
    mat3& operator-=(const mat3& rhs);

    mat3 operator*(const mat3& rhs) const;
    mat3& operator*=(const mat3& rhs);

    vec3 operator*(const vec3& rhs) const;

    mat3 operator*(float rhs) const;
    mat3& operator*=(float rhs);
    mat3 operator/(float rhs) const;
    mat3& operator/=(float rhs);

    bool operator==(const mat3& rhs) const;
    bool operator!=(const mat3& rhs) const;

  }; // struct mat3

} // namespace crusher

#pragma warning(pop)
