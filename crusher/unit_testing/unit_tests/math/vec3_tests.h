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
#include "math/vec3.h"
#include "math/math.h"

namespace vec3_tests
{

  TEST_CASE("vec3 tests")
  {
    SECTION("vec3 constructor", "")
    {
      // default
      crusher::vec3 v0;

      // non-default
      crusher::vec3 v1(1.0f, 1.0f, 1.0f);
      REQUIRE(v1.x == 1.0f);
      REQUIRE(v1.y == 1.0f);
      REQUIRE(v1.z == 1.0f);

      // copy constructor
      crusher::vec3 lhs;
      lhs.x = lhs.y = lhs.z = -1.0f;
      crusher::vec3 rhs;
      rhs.x = rhs.y = rhs.z = 3.0f;
      lhs = rhs;
      REQUIRE(lhs.x == rhs.x);
      REQUIRE(lhs.y == rhs.y);
      REQUIRE(lhs.z == rhs.z);
    }

    SECTION("setter", "")
    {
      // set
      crusher::vec3 v(-1.0f, -1.0f, -1.0f);
      v.set(1.0f, 1.0f, 1.0f);
      REQUIRE(v.x == 1.0f);
      REQUIRE(v.y == 1.0f);
      REQUIRE(v.z == 1.0f);

      // set_zero
      v.set_zero();
      REQUIRE(v.x == 0.0f);
      REQUIRE(v.y == 0.0f);
      REQUIRE(v.z == 0.0f);
    }

    SECTION("scalar multiplication", "")
    {
      // scalar multiplication
      crusher::vec3 v(1.0f, 1.0f, 1.0f);
      crusher::vec3 result = v * 6.0f;
      REQUIRE(result.x == 6.0f);
      REQUIRE(result.y == 6.0f);
      REQUIRE(result.z == 6.0f);

      // * constness
      v * 7.0f = result;
      REQUIRE(v.x == 1.0f);
      REQUIRE(v.y == 1.0f);
      REQUIRE(v.z == 1.0f);

      // *=
      v.x = v.y = v.z =  1.0f;
      v *= 6.0f;
      REQUIRE(v.x == 6.0f);
      REQUIRE(v.y == 6.0f);
      REQUIRE(v.z == 6.0f);

      // *= assignment
      v.x = v.y = v.z = 1.0f;
      (v *= 6.0f) = crusher::vec3(0.0f, 0.0f, 0.0f);
      REQUIRE(v.x == 0.0f);
      REQUIRE(v.y == 0.0f);
      REQUIRE(v.z == 0.0f);
    }

    SECTION("scalar division", "")
    {
      // scalar division
      crusher::vec3 v(6.0f, 6.0f, 6.0f);
      crusher::vec3 result = v / 3.0f;
      REQUIRE(result.x == 2.0f);
      REQUIRE(result.y == 2.0f);
      REQUIRE(result.z == 2.0f);

      // / constness
      v / 3.0f = result;
      REQUIRE(v.x == 6.0f);
      REQUIRE(v.y == 6.0f);
      REQUIRE(v.z == 6.0f);

      // /=
      v.x = v.y = v.z = 6.0f;
      v /= 3.0f;
      REQUIRE(v.x == 2.0f);
      REQUIRE(v.y == 2.0f);
      REQUIRE(v.z == 2.0f);

      // /= assignment
      v.x = v.y = v.z = 6.0f;
      (v /= 3.0f) = crusher::vec3(0.0f, 0.0f, 0.0f);
      REQUIRE(v.x == 0.0f);
      REQUIRE(v.y == 0.0f);
      REQUIRE(v.z == 0.0f);
    }

    SECTION("length", "")
    {
      // length
      crusher::vec3 v0(1.0f, 0.0f, 0.0f);
      REQUIRE(v0.length() == 1.0f);

      crusher::vec3 v1(2.0f, 2.0f, 2.0f);
      REQUIRE(crusher::float_equal(v1.length(), sqrt(12.0f)));

      crusher::vec3 v2(-2.0f, 2.0f, 1.0f);
      REQUIRE(crusher::float_equal(v2.length(), 3.0f));

      crusher::vec3 v3(0.0f, 0.0f, 0.0f);
      REQUIRE(v3.length() == 0.0f);

      // length_sq
      crusher::vec3 v4(1.0f, 0.0f, 0.0f);
      REQUIRE(v4.length_sq() == 1.0f);

      crusher::vec3 v5(2.0f, 2.0f, 2.0f);
      REQUIRE(v5.length_sq() == 12.0f);

      crusher::vec3 v6(-2.0f, 2.0f, 1.0f);
      REQUIRE(v6.length_sq() == 9.0f);

      crusher::vec3 v7(0.0f, 0.0f, 0.0f);
      REQUIRE(v7.length_sq() == 0.0f);
    }

    SECTION("normalization", "")
    {
      // normalize
      crusher::vec3 v0(1.0f, 1.0f, 1.0f);
      v0.normalize();
      float val0 = 1.0f / sqrt(3.0f);
      REQUIRE(crusher::float_equal(v0.x, val0));
      REQUIRE(crusher::float_equal(v0.y, val0));
      REQUIRE(crusher::float_equal(v0.z, val0));

      // 0 length
      //crusher::vec3 v1(0.0f, 0.0f, 0.0f);
      //v1.normalize();
      // div by 0 case handled by assert

      crusher::vec3 v1(1.0f, 1.0f, 1.0f);
      auto result = v1.normalized();
      // check original is untouched
      REQUIRE(crusher::float_equal(v1.x, 1.0f));
      REQUIRE(crusher::float_equal(v1.y, 1.0f));
      REQUIRE(crusher::float_equal(v1.z, 1.0f));
      // check result
      REQUIRE(crusher::float_equal(result.x, val0));
      REQUIRE(crusher::float_equal(result.y, val0));
      REQUIRE(crusher::float_equal(result.y, val0));

      // combining length and normalization
      crusher::vec3 v2(45.0f, 55.0f, 85.0f);
      v2.normalize();
      REQUIRE(crusher::float_equal(v2.length(), 1.0f));

      crusher::vec3 v3(0.1f, -0.1f, 0.1f);
      v3.normalize();
      REQUIRE(crusher::float_equal(v3.length(), 1.0f));
    }

    SECTION("addition / subtraction", "")
    {
      // +
      crusher::vec3 v0(-1.0f, 4.0f, 0.3f);
      crusher::vec3 v1(2.0f, 1.0f, 7.8f);
      auto result01 = v0 + v1;
      REQUIRE(result01.x == 1.0f);
      REQUIRE(result01.y == 5.0f);
      REQUIRE(result01.z == 8.1f);

      // +=
      crusher::vec3 v2(-1.0f, 4.0f, 456.0f);
      crusher::vec3 v3(2.0f, 1.0f, 100.0f);
      v2 += v3;
      REQUIRE(v2.x == 1.0f);
      REQUIRE(v2.y == 5.0f);
      REQUIRE(v2.z == 556.0f);

      // -
      crusher::vec3 v4(-1.0f, 4.0f, 0.0f);
      crusher::vec3 v5(2.0f, 1.0f, 9.0f);
      auto result45 = v4 - v5;
      REQUIRE(result45.x == -3.0f);
      REQUIRE(result45.y == 3.0f);
      REQUIRE(result45.z == -9.0f);

      // -=
      crusher::vec3 v6(-1.0f, 4.0f, 3.5);
      crusher::vec3 v7(2.0f, 1.0f, 0.7f);
      v6 -= v7;
      REQUIRE(v6.x == -3.0f);
      REQUIRE(v6.y == 3.0f);
      REQUIRE(v6.z == 2.8f);
    }

    SECTION("negation", "")
    {
      // simple negate
      crusher::vec3 v0(1.0f, 7.0f, -0.5);
      auto res0 = -v0;
      REQUIRE(res0.x == -1.0f);
      REQUIRE(res0.y == -7.0f);
      REQUIRE(res0.z == 0.5f);

      // negative negate
      crusher::vec3 v1(-1.0f, -7.0f, -2.0f);
      auto res1 = -v1;
      REQUIRE(res1.x == 1.0f);
      REQUIRE(res1.y == 7.0f);
      REQUIRE(res1.z == 2.0f);
    }

    SECTION("distance", "")
    {
      const crusher::vec3 v0(0.0f, 0.0f, 0.0f);
      const crusher::vec3 v1(1.0f, 3.0f, 2.0f);
      const crusher::vec3 v2(5.0f, 7.5f, -3.0f);

      // simple distance
      float dist01 = crusher::vec3::distance(v0, v1);
      REQUIRE(dist01 == v1.length());
      // simple dist sq
      float dist01_sq = crusher::vec3::distance_sq(v0, v1);
      REQUIRE(dist01_sq == v1.length_sq());

      // no distance
      float dist11 = crusher::vec3::distance(v1, v1);
      REQUIRE(dist11 == 0.0f);
      // no dist sq
      float dist11_sq = crusher::vec3::distance_sq(v1, v1);
      REQUIRE(dist11_sq == 0.0f);

      // distance
      float dist12 = crusher::vec3::distance(v1, v2);
      REQUIRE(crusher::float_equal(dist12, 7.82624f));
      float dist12_sq = crusher::vec3::distance_sq(v1, v2);
      float val12_sq = 61.25;
      REQUIRE(crusher::float_equal(dist12_sq, val12_sq));
      // reverse example
      float dist21 = crusher::vec3::distance(v2, v1);
      REQUIRE(crusher::float_equal(dist21, 7.82624f));
      float dist21_sq = crusher::vec3::distance_sq(v2, v1);
      REQUIRE(crusher::float_equal(dist21_sq, val12_sq));
    }

    SECTION("cross / dot products", "")
    {
      // cross product
      crusher::vec3 v0(-1.0f, 2.0f, 3.0f);
      crusher::vec3 v1(2.0f, -3.4f, 0.1f);
      crusher::vec3 v2(-8.5f, 6.0f, 1.9f);
      auto v0_cross_v1 = v0.cross(v1);
      REQUIRE(crusher::float_equal(v0_cross_v1.x, 10.4f));
      REQUIRE(crusher::float_equal(v0_cross_v1.y, 6.1f));
      REQUIRE(crusher::float_equal(v0_cross_v1.z, -0.6f));
      auto v1_cross_v2 = v1.cross(v2);
      REQUIRE(crusher::float_equal(v1_cross_v2.x, -7.06f));
      REQUIRE(crusher::float_equal(v1_cross_v2.y, -4.65f));
      REQUIRE(crusher::float_equal(v1_cross_v2.z, -16.9f));

      // dot product
      float v0_dot_v1 = v0.dot(v1);
      REQUIRE(crusher::float_equal(v0_dot_v1, -8.5f));
      REQUIRE(crusher::float_equal(v0.dot(v0), v0.length_sq()));
    }
  }
}