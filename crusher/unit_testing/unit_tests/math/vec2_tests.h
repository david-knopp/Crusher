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
#include "math/vec2.h"
#include "math/math.h"

namespace vec2_tests
{

  TEST_CASE("vec2 tests", "vec2 tests")
  {
    SECTION("constructor", "")
    {
      // default
      crusher::vec2 v0;

      // non-default
      crusher::vec2 v1(1.0f, 1.0f);
      REQUIRE(v1.x == 1.0f);
      REQUIRE(v1.y == 1.0f);

      // copy constructor
      crusher::vec2 lhs;
      lhs.x = lhs.y = -1.0f;
      crusher::vec2 rhs;
      rhs.x = rhs.y = 3.0f;
      lhs = rhs;
      REQUIRE(lhs.x == rhs.x);
      REQUIRE(lhs.y == rhs.y);
    }

    SECTION("setter", "")
    {
      // set
      crusher::vec2 v(-1.0f, -1.0f);
      v.set(1.0f, 1.0f);
      REQUIRE(v.x == 1.0f);
      REQUIRE(v.y == 1.0f);

      // set_zero
      v.set_zero();
      REQUIRE(v.x == 0.0f);
      REQUIRE(v.y == 0.0f);
    }

    SECTION("scalar multiplication", "")
    {
      // scalar multiplication
      crusher::vec2 v(1.0f, 1.0f);
      crusher::vec2 result = v * 6.0f;
      REQUIRE(result.x == 6.0f);
      REQUIRE(result.y == 6.0f);

      // * constness
      v * 7.0f = result;
      REQUIRE(v.x == 1.0f);
      REQUIRE(v.y == 1.0f);

      // *=
      v.x = v.y = 1.0f;
      v *= 6.0f;
      REQUIRE(v.x == 6.0f);
      REQUIRE(v.y == 6.0f);

      // *= assignment
      v.x = v.y = 1.0f;
      (v *= 6.0f) = crusher::vec2(0.0f, 0.0f);
      REQUIRE(v.x == 0.0f);
      REQUIRE(v.y == 0.0f);
    }

    SECTION("scalar division", "")
    {
      // scalar division
      crusher::vec2 v(6.0f, 6.0f);
      crusher::vec2 result = v / 3.0f;
      REQUIRE(result.x == 2.0f);
      REQUIRE(result.y == 2.0f);

      // / constness
      v / 3.0f = result;
      REQUIRE(v.x == 6.0f);
      REQUIRE(v.y == 6.0f);

      // /=
      v.x = v.y = 6.0f;
      v /= 3.0f;
      REQUIRE(v.x == 2.0f);
      REQUIRE(v.y == 2.0f);

      // /= assignment
      v.x = v.y = 6.0f;
      (v /= 3.0f) = crusher::vec2(0.0f, 0.0f);
      REQUIRE(v.x == 0.0f);
      REQUIRE(v.y == 0.0f);
    }

    SECTION("length", "")
    {
      // length
      crusher::vec2 v0(1.0f, 0.0f);
      REQUIRE(v0.length() == 1.0f);

      crusher::vec2 v1(2.0f, 2.0f);
      REQUIRE(crusher::float_equal(v1.length(), 2.82843f));

      crusher::vec2 v2(-2.0f, 2.0f);
      REQUIRE(crusher::float_equal(v2.length(), 2.82843f));

      crusher::vec2 v3(0.0f, 0.0f);
      REQUIRE(v3.length() == 0.0f);

      // length_sq
      crusher::vec2 v4(1.0f, 0.0f);
      REQUIRE(v4.length_sq() == 1.0f);

      crusher::vec2 v5(2.0f, 2.0f);
      REQUIRE(v5.length_sq() == 8.0f);

      crusher::vec2 v6(-2.0f, 2.0f);
      REQUIRE(v6.length_sq() == 8.0f);

      crusher::vec2 v7(0.0f, 0.0f);
      REQUIRE(v7.length_sq() == 0.0f);
    }

    SECTION("normalization", "")
    {
      // normalize
      crusher::vec2 v0(1.0f, 1.0f);
      v0.normalize();
      REQUIRE(crusher::float_equal(v0.x, 0.707107f));
      REQUIRE(crusher::float_equal(v0.y, 0.707107f));

      // 0 length
      //crusher::vec2 v1(0.0f, 0.0f);
      //v1.normalize();
      // div by 0 case handled by assert

      crusher::vec2 v1(1.0f, 1.0f);
      auto result = v1.normalized();
      // check original is untouched
      REQUIRE(crusher::float_equal(v1.x, 1.0f));
      REQUIRE(crusher::float_equal(v1.y, 1.0f));
      // check result
      REQUIRE(crusher::float_equal(result.x, 0.707107f));
      REQUIRE(crusher::float_equal(result.y, 0.707107f));

      // combining length and normalization
      crusher::vec2 v2(45.0f, 55.0f);
      v2.normalize();
      REQUIRE(crusher::float_equal(v2.length(), 1.0f));

      crusher::vec2 v3(0.1f, 0.1f);
      v3.normalize();
      REQUIRE(crusher::float_equal(v3.length(), 1.0f));
    }

    SECTION("addition / subtraction", "")
    {
      // +
      crusher::vec2 v0(-1.0f, 4.0f);
      crusher::vec2 v1(2.0f, 1.0f);
      auto result01 = v0 + v1;
      REQUIRE(result01.x == 1.0f);
      REQUIRE(result01.y == 5.0f);

      // +=
      crusher::vec2 v2(-1.0f, 4.0f);
      crusher::vec2 v3(2.0f, 1.0f);
      v2 += v3;
      REQUIRE(v2.x == 1.0f);
      REQUIRE(v2.y == 5.0f);

      // -
      crusher::vec2 v4(-1.0f, 4.0f);
      crusher::vec2 v5(2.0f, 1.0f);
      auto result45 = v4 - v5;
      REQUIRE(result45.x == -3.0f);
      REQUIRE(result45.y == 3.0f);

      // -=
      crusher::vec2 v6(-1.0f, 4.0f);
      crusher::vec2 v7(2.0f, 1.0f);
      v6 -= v7;
      REQUIRE(v6.x == -3.0f);
      REQUIRE(v6.y == 3.0f);
    }

    SECTION("negation", "")
    {
      // simple negate
      crusher::vec2 v0(1.0f, 7.0f);
      auto res0 = -v0;
      REQUIRE(res0.x == -1.0f);
      REQUIRE(res0.y == -7.0f);

      // negative negate
      crusher::vec2 v1(-1.0f, -7.0f);
      auto res1 = -v1;
      REQUIRE(res1.x == 1.0f);
      REQUIRE(res1.y == 7.0f);
    }
  }
}