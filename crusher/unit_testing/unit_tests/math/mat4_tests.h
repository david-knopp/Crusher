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
#include "unit_tests/catch.hpp"
#include "math/mat4.h"
#include "math/vec4.h"
#include "math/math.h"

namespace mat4_tests
{

  TEST_CASE("mat4 tests")
  {
    SECTION("constructor and getter / setter", "")
    {
      // default
      crusher::mat4 def;

      // non-default
      {
        crusher::mat4 n_def(1.0f, 2.0f, 3.0f, 4.0f, 
                            5.0f, 6.0f, 7.0f, 8.0f, 
                            9.0f, 10.0f, 11.0f, 12.0f,
                            13.0f, 14.0f, 15.0f, 16.0f);
        float j = 1.0f;
        for (int i = 0; i < 16; ++i, ++j)
          REQUIRE(n_def.data[i] == j);
      }

      // set test
      {
        crusher::mat4 set_test(0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 0.0f);
        set_test.set(1.0f, 2.0f, 3.0f, 4.0f, 
                     5.0f, 6.0f, 7.0f, 8.0f, 
                     9.0f, 10.0f, 11.0f, 12.0f,
                     13.0f, 14.0f, 15.0f, 16.0f);
        float j = 1.0f;
        for (int i = 0; i < 16; ++i, ++j)
          REQUIRE(set_test.data[i] == j);
      }

      // accessors
      {
        crusher::mat4 m(1.0f, 2.0f, 3.0f, 4.0f, 
                        5.0f, 6.0f, 7.0f, 8.0f, 
                        9.0f, 10.0f, 11.0f, 12.0f,
                        13.0f, 14.0f, 15.0f, 16.0f);
        float j = 1.0f;
        for (int i = 0; i < 16; ++i, ++j)
          REQUIRE(m.data[i] == j);

        REQUIRE(m.m[0][0] == 1.0f);
        REQUIRE(m.m[0][1] == 2.0f);
        REQUIRE(m.m[0][2] == 3.0f);
        REQUIRE(m.m[0][3] == 4.0f);
        REQUIRE(m.m[1][0] == 5.0f);
        REQUIRE(m.m[1][1] == 6.0f);
        REQUIRE(m.m[1][2] == 7.0f);
        REQUIRE(m.m[1][3] == 8.0f);
        REQUIRE(m.m[2][0] == 9.0f);
        REQUIRE(m.m[2][1] == 10.0f);
        REQUIRE(m.m[2][2] == 11.0f);
        REQUIRE(m.m[2][3] == 12.0f);
        REQUIRE(m.m[3][0] == 13.0f);
        REQUIRE(m.m[3][1] == 14.0f);
        REQUIRE(m.m[3][2] == 15.0f);
        REQUIRE(m.m[3][3] == 16.0f);

        REQUIRE(m.m00 == 1.0f);
        REQUIRE(m.m01 == 2.0f);
        REQUIRE(m.m02 == 3.0f);
        REQUIRE(m.m03 == 4.0f);
        REQUIRE(m.m10 == 5.0f);
        REQUIRE(m.m11 == 6.0f);
        REQUIRE(m.m12 == 7.0f);
        REQUIRE(m.m13 == 8.0f);
        REQUIRE(m.m20 == 9.0f);
        REQUIRE(m.m21 == 10.0f);
        REQUIRE(m.m22 == 11.0f);
        REQUIRE(m.m23 == 12.0f);
        REQUIRE(m.m30 == 13.0f);
        REQUIRE(m.m31 == 14.0f);
        REQUIRE(m.m32 == 15.0f);
        REQUIRE(m.m33 == 16.0f);
      }

      // identity test
      crusher::mat4 ident(1.0f, 0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 0.0f, 1.0f);
      REQUIRE(ident == crusher::mat4::identity);

      // set identity test
      crusher::mat4 set_ident;
      set_ident.set_identity();
      REQUIRE(set_ident == crusher::mat4::identity);
    }

    SECTION("equality", "")
    {
      crusher::mat4 m0(1.0f, 2.0f, 3.0f, 4.0f, 
                       5.0f, 6.0f, 7.0f, 8.0f, 
                       9.0f, 10.0f, 11.0f, 12.0f,
                       13.0f, 14.0f, 15.0f, 16.0f);

      crusher::mat4 m1(1.4f, 2.0f, 3.0f, 4.0f, 
                       5.0f, 6.0f, 7.0f, 8.0f, 
                       9.0f, 10.0f, 11.0f, 12.0f,
                       13.0f, 14.0f, 15.0f, 16.0f);

      auto m0_copy = m0;
      REQUIRE(m0_copy == m0); 

      bool m0_equals_m1 = m0 == m1;
      REQUIRE(!m0_equals_m1);
      REQUIRE(m0 != m1);
    }

    SECTION("invert", "")
    {
      crusher::mat4 m(1.0f, 2.0f, 3.0f, 4.0f,
                      4.0f, 3.0f, 2.0f, 1.0f,
                      2.0f, 1.0f, 3.0f, 4.0f,
                      3.0f, 4.0f, 1.0f, 2.0f);

      crusher::mat4 m_inv_ans(-0.575f, 0.05f, 0.5f, 0.125f,
                              0.425f, 0.05f, -0.5f, 0.125f,
                              0.675f, 0.55f, -0.5f, -0.625f,
                              -0.325f, -0.45f, 0.5f, 0.375f);

      // determinant
      float det = m.determinant();
      REQUIRE(det == -40.0f);

      // basic invert
      crusher::mat4 m_inv = m.inverted();
      REQUIRE(m_inv == m_inv_ans);
    
      m.invert();
      REQUIRE(m == m_inv_ans);

      // singular matrix
      crusher::mat4 sing(1.0f, 2.0f, 3.0f, 4.0f,
                         4.0f, 3.0f, 2.0f, 1.0f,
                         2.0f, 1.0f, 3.0f, 4.0f,
                         3.0f, 4.0f, 2.0f, 1.0f);
      float det_sing = sing.determinant();
      REQUIRE(det_sing == 0.0f);
      // assertion handled
      //sing.invert();

      // identity check
      m.set(1.0f, 2.0f, 3.0f, 4.0f,
            4.0f, 3.0f, 2.0f, 1.0f,
            2.0f, 1.0f, 3.0f, 4.0f,
            3.0f, 4.0f, 1.0f, 2.0f);
      auto result = m * m_inv;
      REQUIRE(result == crusher::mat4::identity);

      auto inv_result = crusher::mat4::identity.inverted();
      REQUIRE(inv_result == crusher::mat4::identity);
    }

    SECTION("transpose", "")
    {
      crusher::mat4 m(1.0f, 2.0f, 3.0f, 4.0f, 
                      5.0f, 6.0f, 7.0f, 8.0f, 
                      9.0f, 10.0f, 11.0f, 12.0f,
                      13.0f, 14.0f, 15.0f, 16.0f);

      crusher::mat4 m_trans(1.0f, 5.0f, 9.0f, 13.0f,
                            2.0f, 6.0f, 10.0f, 14.0f,
                            3.0f, 7.0f, 11.0f, 15.0f,
                            4.0f, 8.0f, 12.0f, 16.0f);
      auto trans = m.transposed();
      REQUIRE(trans == m_trans);

      m.transpose();
      REQUIRE(m == m_trans);
    }

    SECTION("addition / subtraction", "")
    {
      crusher::mat4 m0(1.0f, 2.0f, 3.0f, 4.0f, 
                       5.0f, 6.0f, 7.0f, 8.0f, 
                       9.0f, 10.0f, 11.0f, 12.0f,
                       13.0f, 14.0f, 15.0f, 16.0f);

      crusher::mat4 m1(-1.0f, 4.0f, 3.7f, 0.9f,
                       1.0f, -2.7f, 1.0f, 0.84f,
                       3.0f, 2.8f, -2.0f, 1.0f,
                       0.75f, 0.0f, -3.4f, 17.0f);

      // +
      crusher::mat4 m0_plus_m1(0.0f, 6.0f, 6.7f, 4.9f,
                               6.0f, 3.3f, 8.0f, 8.84f,
                               12.0f, 12.8f, 9.0f, 13.0f,
                               13.75f, 14.0f, 11.6f, 33.0f);
      auto m0_plus_m1_res = m0 + m1;
      REQUIRE(m0_plus_m1_res == m0_plus_m1);

      // +=
      m0 += m1;
      REQUIRE(m0 == m0_plus_m1);

      // -
      m0.set(1.0f, 2.0f, 3.0f, 4.0f, 
             5.0f, 6.0f, 7.0f, 8.0f, 
             9.0f, 10.0f, 11.0f, 12.0f,
             13.0f, 14.0f, 15.0f, 16.0f);

      crusher::mat4 m0_minus_m1(2.0f, -2.0f, -0.7f, 3.1f,
                                4.0f, 8.7f, 6.0f, 7.16f,
                                6.0f, 7.2f, 13.0f, 11.0f,
                                12.25f, 14.0f, 18.4f, -1.0f);
      auto m0_minus_m1_res = m0 - m1;
      REQUIRE(m0_minus_m1_res == m0_minus_m1);

      // -=
      m0 -= m1;
      REQUIRE(m0 == m0_minus_m1);
    }

    SECTION("multiplication", "")
    {
      crusher::mat4 m0(1.0f, 2.0f, 3.0f, 4.0f, 
                       5.0f, 6.0f, 7.0f, 8.0f, 
                       9.0f, 10.0f, 11.0f, 12.0f,
                       13.0f, 14.0f, 15.0f, 16.0f);
    
      crusher::mat4 m1(-1.0f, 4.0f, 3.7f, 0.9f,
                       1.0f, -2.7f, 1.0f, 0.84f,
                       3.0f, 2.8f, -2.0f, 1.0f,
                       0.75f, 0.0f, -3.4f, 17.0f);

      crusher::mat4 m0_x_m1(13.0f, 7.0f, -13.9f, 73.58f,
                            28.0f, 23.4f, -16.7f, 152.54f,
                            43.0f, 39.8f, -19.5f, 231.5f,
                            58.0f, 56.2f, -22.3f, 310.46f);

      // *
      auto m0_x_m1_res = m0 * m1;
      REQUIRE(m0_x_m1_res == m0_x_m1);

      // *=
      m0 *= m1;
      REQUIRE(m0 == m0_x_m1);

      // mult with identity
      auto ident_res = m1 * crusher::mat4::identity;
      REQUIRE(ident_res == m1);

      // vector multiplication
      crusher::vec4 v0(1.0f, 2.0f, 3.0f, 0.5f);
      crusher::vec4 m1_x_v0(18.55f, -0.98f, 3.1f, -0.95f);

      auto m1_x_v0_res = m1 * v0;
      REQUIRE(crusher::float_equal(m1_x_v0_res.x, m1_x_v0.x));
      REQUIRE(crusher::float_equal(m1_x_v0_res.y, m1_x_v0.y));
      REQUIRE(crusher::float_equal(m1_x_v0_res.z, m1_x_v0.z));
    }

    SECTION("scalar multiplication / division", "")
    {
      crusher::mat4 m0(1.0f, 2.0f, 3.0f, 4.0f, 
                       5.0f, 6.0f, 7.0f, 8.0f, 
                       9.0f, 10.0f, 11.0f, 12.0f,
                       13.0f, 14.0f, 15.0f, 16.0f);
      crusher::mat4 m0x3(3.0f, 6.0f, 9.0f, 12.0f, 
                         15.0f, 18.0f, 21.0f, 24.0f, 
                         27.0f, 30.0f, 33.0f, 36.0f,
                         39.0f, 42.0f, 45.0f, 48.0f);
      crusher::mat4 m0_div2(0.5f, 1.0f, 1.5f, 2.0f, 
                            2.5f, 3.0f, 3.5f, 4.0f, 
                            4.5f, 5.0f, 5.5f, 6.0f,
                            6.5f, 7.0f, 7.5f, 8.0f);

      // *
      auto m0x3_res = m0 * 3.0f;
      REQUIRE(m0x3_res == m0x3);

      // *=
      m0 *= 3.0f;
      REQUIRE(m0 == m0x3);

      // /
      m0.set(1.0f, 2.0f, 3.0f, 4.0f, 
             5.0f, 6.0f, 7.0f, 8.0f, 
             9.0f, 10.0f, 11.0f, 12.0f,
             13.0f, 14.0f, 15.0f, 16.0f);
      auto m0_div2_res = m0 / 2.0f;
      REQUIRE(m0_div2_res == m0_div2);

      // /=
      m0 /= 2.0f;
      REQUIRE(m0 == m0_div2);
    }
  }
}
