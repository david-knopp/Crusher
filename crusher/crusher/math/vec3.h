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

  /* 3 dimensional vector of floats */
  struct vec3
  {
    // static members
    static const vec3 zero;

    // public members
    union
    {
      struct
      {
        float x;
        float y;
        float z;
      };

      struct
      {
        float r;
        float g;
        float b;
      };

      float data[3];
    };

    // ctor / dtor
    vec3(void);
    vec3(float x, float y, float z);

    // public methods
    void set(float x, float y, float z);
    void set_zero(void);
    float length(void) const;
    float length_sq(void) const;
    vec3& normalize(void);
    vec3 normalized(void) const;

    float dot(const vec3& rhs) const;
    vec3 cross(const vec3& rhs) const;

    // operators
    vec3 operator+(const vec3& rhs) const;
    vec3& operator+=(const vec3& rhs);
    vec3 operator-(const vec3& rhs) const;
    vec3& operator-=(const vec3& rhs);

    vec3 operator*(float rhs) const;
    vec3& operator*=(float rhs);
    vec3 operator/(float rhs) const;
    vec3& operator/=(float rhs);

    vec3 operator-(void) const;

    bool operator==(const vec3& rhs) const;
    bool operator!=(const vec3& rhs) const;

    // static methods
    static float distance(const vec3& a, const vec3& b);
    static float distance_sq(const vec3& a, const vec3& b);

    static vec3 cross(const vec3& lhs, const vec3& rhs);

  }; // struct vec3

} // namespace crusher

#pragma warning(pop)
