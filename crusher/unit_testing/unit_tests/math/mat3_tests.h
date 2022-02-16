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
#include "math/mat3.h"
#include "math/vec3.h"
#include "math/math.h"

namespace mat3_tests
{

  TEST_CASE("mat3 tests")
  {
    SECTION("constructor and getter / setter", "")
    {
      // default
      crusher::mat3 def;

      // non-default
      {
        crusher::mat3 n_def(1.0f, 2.0f, 3.0f, 
                            4.0f, 5.0f, 6.0f,
                            7.0f, 8.0f, 9.0f);
        float j = 1.0f;
        for (int i = 0; i < 9; ++i, ++j)
          REQUIRE(n_def.data[i] == j);
      }

      // set test
      {
        crusher::mat3 set_test(0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 0.0f);
        set_test.set(1.0f, 2.0f, 3.0f,
                     4.0f, 5.0f, 6.0f,
                     7.0f, 8.0f, 9.0f);
        float j = 1.0f;
        for (int i = 0; i < 9; ++i, ++j)
          REQUIRE(set_test.data[i] == j);
      }

      // accessors
      {
        crusher::mat3 m(1.0f, 2.0f, 3.0f,
                        4.0f, 5.0f, 6.0f,
                        7.0f, 8.0f, 9.0f);
        float j = 1.0f;
        for (int i = 0; i < 9; ++i, ++j)
          REQUIRE(m.data[i] == j);

        REQUIRE(m.m[0][0] == 1.0f);
        REQUIRE(m.m[0][1] == 2.0f);
        REQUIRE(m.m[0][2] == 3.0f);
        REQUIRE(m.m[1][0] == 4.0f);
        REQUIRE(m.m[1][1] == 5.0f);
        REQUIRE(m.m[1][2] == 6.0f);
        REQUIRE(m.m[2][0] == 7.0f);
        REQUIRE(m.m[2][1] == 8.0f);
        REQUIRE(m.m[2][2] == 9.0f);

        REQUIRE(m.m00 == 1.0f);
        REQUIRE(m.m01 == 2.0f);
        REQUIRE(m.m02 == 3.0f);
        REQUIRE(m.m10 == 4.0f);
        REQUIRE(m.m11 == 5.0f);
        REQUIRE(m.m12 == 6.0f);
        REQUIRE(m.m20 == 7.0f);
        REQUIRE(m.m21 == 8.0f);
        REQUIRE(m.m22 == 9.0f);
      }

      // identity test
      crusher::mat3 ident(1.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 1.0f);
      REQUIRE(ident == crusher::mat3::identity);

      // set identity test
      crusher::mat3 set_ident;
      set_ident.set_identity();
      REQUIRE(set_ident == crusher::mat3::identity);
    }

    SECTION("equality", "")
    {
      crusher::mat3 m0(1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f);

      crusher::mat3 m1(1.4f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f);

      auto m0_copy = m0;
      REQUIRE(m0_copy == m0); 

      bool m0_equals_m1 = m0 == m1;
      REQUIRE(!m0_equals_m1);
      REQUIRE(m0 != m1);
    }

    SECTION("invert", "")
    {
      crusher::mat3 m(1.0f, 2.0f, 3.0f,
                      3.0f, 2.0f, 1.0f,
                      2.0f, 1.0f, 3.0f);

      crusher::mat3 m_inv_ans(-0.416667f, 0.25f, 0.3333333f,
                              0.5833333f, 0.25f, -0.666667f,
                              0.0833333f, -0.25f, 0.3333333f);

      // determinant
      float det = m.determinant();
      REQUIRE(det == -12.0f);

      // basic invert
      crusher::mat3 m_inv = m.inverted();
      REQUIRE(m_inv == m_inv_ans);
    
      m.invert();
      REQUIRE(m == m_inv_ans);

      // singular matrix
      crusher::mat3 sing(1.0f, 2.0f, 3.0f,
                         4.0f, 5.0f, 6.0f,
                         7.0f, 8.0f, 9.0f);
      float det_sing = sing.determinant();
      REQUIRE(det_sing == 0.0f);
      // assertion handled
      //sing.invert();

      // identity check
      m.set(1.0f, 2.0f, 3.0f,
            3.0f, 2.0f, 1.0f,
            2.0f, 1.0f, 3.0f);
      auto result = m * m_inv;
      REQUIRE(result == crusher::mat3::identity);

      auto inv_result = crusher::mat3::identity.inverted();
      REQUIRE(inv_result == crusher::mat3::identity);
    }

    SECTION("transpose", "")
    {
      crusher::mat3 m(1.0f, 2.0f, 3.0f,
                      4.0f, 5.0f, 6.0f,
                      7.0f, 8.0f, 9.0f);

      crusher::mat3 m_trans(1.0f, 4.0f, 7.0f,
                            2.0f, 5.0f, 8.0f,
                            3.0f, 6.0f, 9.0f);
      auto trans = m.transposed();
      REQUIRE(trans == m_trans);

      m.transpose();
      REQUIRE(m == m_trans);
    }

    SECTION("addition / subtraction", "")
    {
      crusher::mat3 m0(1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f);

      crusher::mat3 m1(-1.0f, 4.0f, 3.7f,
                       1.0f, -2.7f, 1.0f,
                       3.0f, 2.8f, -2.0f);

      // +
      crusher::mat3 m0_plus_m1(0.0f, 6.0f, 6.7f,
                               5.0f, 2.3f, 7.0f,
                               10.0f, 10.8f, 7.0f);
      auto m0_plus_m1_res = m0 + m1;
      REQUIRE(m0_plus_m1_res == m0_plus_m1);

      // +=
      m0 += m1;
      REQUIRE(m0 == m0_plus_m1);

      // -
      m0.set(1.0f, 2.0f, 3.0f,
             4.0f, 5.0f, 6.0f,
             7.0f, 8.0f, 9.0f);

      crusher::mat3 m0_minus_m1(2.0f, -2.0f, -0.7f,
                                3.0f, 7.7f, 5.0f,
                                4.0f, 5.2f, 11.0f);
      auto m0_minus_m1_res = m0 - m1;
      REQUIRE(m0_minus_m1_res == m0_minus_m1);

      // -=
      m0 -= m1;
      REQUIRE(m0 == m0_minus_m1);
    }

    SECTION("multiplication", "")
    {
      crusher::mat3 m0(1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f);
    
      crusher::mat3 m1(-1.0f, 4.0f, 7.0f,
                       7.4f, -2.0f, 5.0f,
                       -0.5f, 0.6f, 1.0f);

      crusher::mat3 m0_x_m1(12.3f, 1.8f, 20.0f,
                            30.0f, 9.6f, 59.0f,
                            47.7f, 17.4f, 98.0f);

      // *
      auto m0_x_m1_res = m0 * m1;
      REQUIRE(m0_x_m1_res == m0_x_m1);

      // *=
      m0 *= m1;
      REQUIRE(m0 == m0_x_m1);

      // mult with identity
      auto ident_res = m1 * crusher::mat3::identity;
      REQUIRE(ident_res == m1);

      // vector multiplication
      crusher::vec3 v0(1.0f, 2.0f, 3.0f);
      crusher::vec3 m1_x_v0(28.0f, 18.4f, 3.7f);

      auto m1_x_v0_res = m1 * v0;
      REQUIRE(m1_x_v0_res.x == m1_x_v0.x);
      REQUIRE(m1_x_v0_res.y == m1_x_v0.y);
      REQUIRE(m1_x_v0_res.z == m1_x_v0.z);
    }

    SECTION("scalar multiplication / division", "")
    {
      crusher::mat3 m0(1.0f, 2.0f, 3.0f,
                       4.0f, 5.0f, 6.0f,
                       7.0f, 8.0f, 9.0f);
      crusher::mat3 m0x3(3.0f, 6.0f, 9.0f,
                         12.0f, 15.0f, 18.0f,
                         21.0f, 24.0f, 27.0f);
      crusher::mat3 m0_div2(0.5f, 1.0f, 1.5f,
                            2.0f, 2.5f, 3.0f,
                            3.5f, 4.0f, 4.5f);

      // *
      auto m0x3_res = m0 * 3.0f;
      REQUIRE(m0x3_res == m0x3);

      // *=
      m0 *= 3.0f;
      REQUIRE(m0 == m0x3);

      // /
      m0.set(1.0f, 2.0f, 3.0f,
             4.0f, 5.0f, 6.0f,
             7.0f, 8.0f, 9.0f);
      auto m0_div2_res = m0 / 2.0f;
      REQUIRE(m0_div2_res == m0_div2);

      // /=
      m0 /= 2.0f;
      REQUIRE(m0 == m0_div2);
    }
  }

}
