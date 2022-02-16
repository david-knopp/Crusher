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

#ifndef EPSILON
  #define EPSILON (0.001f)
#endif

#ifndef PI
  #define PI (3.1415926535897932384626433832795f)
#endif

#ifndef PI_2
  #define PI_2 (1.5707963267948966192313216916397f)
#endif

#ifndef DEGREE_TO_RADIAN
  #define DEGREE_TO_RADIAN (PI / 180.0f)
#endif

#ifndef RADIAN_TO_DEGREE
  #define RADIAN_TO_DEGREE (180.0f / PI)
#endif

#ifndef SQRT_2
  #define SQRT_2 (1.4142135623730950488016887242097f)
#endif

namespace crusher
{

  static inline bool float_equal(float lhs, float rhs)
  {
    float diff = lhs - rhs;
    return (diff < EPSILON && -diff < EPSILON);
  }

} // namespace crusher