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
#include "math/quat.h"

namespace quat_tests
{

  TEST_CASE("quat tests")
  {
    SECTION("constructors", "")
    {
      // default ctor
      crusher::quat q1(1.0f, 2.0f, 3.0f, 4.0f);

      REQUIRE(q1.x == 1.0f);
      REQUIRE(q1.y == 2.0f);
      REQUIRE(q1.z == 3.0f);
      REQUIRE(q1.w == 4.0f);

      REQUIRE(q1.v.x == 1.0f);
      REQUIRE(q1.v.y == 2.0f);
      REQUIRE(q1.v.z == 3.0f);
      REQUIRE(q1.s == 4.0f);

      REQUIRE(q1.data[0] == 1.0f);
      REQUIRE(q1.data[1] == 2.0f);
      REQUIRE(q1.data[2] == 3.0f);
      REQUIRE(q1.data[3] == 4.0f);

      // axis angle
      crusher::quat q2(PI_2, crusher::vec4(1.0f, 0.0f, 0.0f, 0.0f));
      REQUIRE(crusher::float_equal(q2.x, 0.7071f));
      REQUIRE(crusher::float_equal(q2.y, 0.0f));
      REQUIRE(crusher::float_equal(q2.z, 0.0f));
      REQUIRE(crusher::float_equal(q2.w, 0.7071f));

      crusher::quat q3(PI_2, crusher::vec3(1.0f, 0.0f, 0.0f));
      REQUIRE(q3 == q2);

      crusher::vec3 axis4(0.57735f, 0.57735f, 0.57735f);
      crusher::quat q4(1.319f, axis4);
      REQUIRE(crusher::float_equal(q4.x, 0.3537f));
      REQUIRE(crusher::float_equal(q4.y, 0.3537f));
      REQUIRE(crusher::float_equal(q4.z, 0.3537f));
      REQUIRE(crusher::float_equal(q4.w, 0.7903f));

      // matrix
      crusher::mat3 m5(.25581f, -.77351f, .57986f,
                       -.85333f, -.46255f, -.24057f,
                       .45429f, -.43327f, -.77839f);
      crusher::quat q5(m5);
      REQUIRE(crusher::float_equal(q5.x, 0.79012f));
      REQUIRE(crusher::float_equal(q5.y, -0.51487f));
      REQUIRE(crusher::float_equal(q5.z, 0.32728f));
      REQUIRE(crusher::float_equal(q5.w, -0.06097f));

      crusher::mat4 m6(.25581f, -.77351f, .57986f, 0.0f,
                       -.85333f, -.46255f, -.24057f, 0.0f,
                       .45429f, -.43327f, -.77839f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
      crusher::quat q6(m6);
      REQUIRE(q6 == q5);
    }

    SECTION("equality", "")
    {
      crusher::quat q(1.0f, 2.0f, 3.0f, -1.0f);
      crusher::quat r(1.0f, 2.0f, 3.0f, -1.0f);
      REQUIRE(q == r);
      
      crusher::quat q1(-1.0f, 2.0f, 3.0f, -1.0f);
      REQUIRE(q1 != q);
      crusher::quat q2(1.0f, -2.0f, 3.0f, -1.0f);
      REQUIRE(q2 != q);
      crusher::quat q3(1.0f, 2.0f, -3.0f, -1.0f);
      REQUIRE(q3 != q);
      crusher::quat q4(1.0f, 2.0f, 3.0f, 1.0f);
      REQUIRE(q4 != q);
    }

    SECTION("setters", "")
    {
      // note: other setters implicitly tested in constructor tests
      crusher::quat q1;
      q1.set_euler(0.0f, 0.0f, 0.0f);
      REQUIRE(crusher::float_equal(q1.x, 0.0f));
      REQUIRE(crusher::float_equal(q1.y, 0.0f));
      REQUIRE(crusher::float_equal(q1.z, 0.0f));
      REQUIRE(crusher::float_equal(q1.w, 1.0f));

      crusher::quat q2;
      // b, h, a
      q2.set_euler(PI_2, 0.0f, 0.0f);
      REQUIRE(crusher::float_equal(q2.x, 0.7071f));
      REQUIRE(crusher::float_equal(q2.y, 0.0f));
      REQUIRE(crusher::float_equal(q2.z, 0.0f));
      REQUIRE(crusher::float_equal(q2.w, 0.7071f));

      q2.set_euler(0.0f, PI_2, 0.0f);
      REQUIRE(crusher::float_equal(q2.x, 0.0f));
      REQUIRE(crusher::float_equal(q2.y, 0.7071f));
      REQUIRE(crusher::float_equal(q2.z, 0.0f));
      REQUIRE(crusher::float_equal(q2.w, 0.7071f));

      q2.set_euler(0.0f, 0.0f, PI_2);
      REQUIRE(crusher::float_equal(q2.x, 0.0f));
      REQUIRE(crusher::float_equal(q2.y, 0.0f));
      REQUIRE(crusher::float_equal(q2.z, 0.7071f));
      REQUIRE(crusher::float_equal(q2.w, 0.7071f));

      q2.set_euler(0.0f, 45.0f * DEGREE_TO_RADIAN, -20 * DEGREE_TO_RADIAN);
      REQUIRE(crusher::float_equal(q2.x, -0.06645f));
      REQUIRE(crusher::float_equal(q2.y, 0.37686f));
      REQUIRE(crusher::float_equal(q2.z, -0.16042f));
      REQUIRE(crusher::float_equal(q2.w, 0.90984f));

      q2.set_euler(45.0f * DEGREE_TO_RADIAN, 0.0f, -20 * DEGREE_TO_RADIAN);
      REQUIRE(crusher::float_equal(q2.x, 0.37686f));
      REQUIRE(crusher::float_equal(q2.y, 0.06645f));
      REQUIRE(crusher::float_equal(q2.z, -0.16042f));
      REQUIRE(crusher::float_equal(q2.w, 0.90984f));
    }

    SECTION("to matrix", "")
    {
      crusher::mat3 rotx(1.0f, 0.0f, 0.0f,
                         0.0f, cos(PI_2), sin(PI_2),
                         0.0f, -sin(PI_2), cos(PI_2));
      crusher::mat4 rotx2(1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, cos(PI_2), sin(PI_2), 0.0f,
                         0.0f, -sin(PI_2), cos(PI_2), 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f);
      crusher::quat q(rotx);

      REQUIRE(q.to_mat3() == rotx);
      REQUIRE(q.to_mat4() == rotx2);

      crusher::mat3 roty(cos(PI_2), 0.0f, -sin(PI_2),
                         0.0f, 1.0f , 0.0f,
                         sin(PI_2), 0.0f, cos(PI_2));

      q.set(roty);
      REQUIRE(q.to_mat3() == roty);

      q.set(rotx * roty);
      REQUIRE(q.to_mat3() == (rotx * roty));

      crusher::mat3 m;
      q.to_matrix(m);
      REQUIRE(m == q.to_mat3());

      crusher::mat4 m4;
      q.to_matrix(m4);
      REQUIRE(m4 == q.to_mat4());
    }

    SECTION("multiplication", "")
    {
      crusher::quat q(0.0f, 0.0f, 0.0f, 1.0f);
      crusher::quat r(0.0f, 0.7f, 0.0f, 0.7f);

      REQUIRE((q * r) == crusher::quat(0.0f, 0.7f, 0.0f, 0.7f));
      REQUIRE((q * q) == crusher::quat(0.0f, 0.0f, 0.0f, 1.0f));

      crusher::quat t(-0.3856f, 0.2966f, 0.1796f, 0.8599f);

      auto res = t * r;
      REQUIRE(crusher::float_equal(res.x, -0.3956f));
      REQUIRE(crusher::float_equal(res.y, 0.8095f));
      REQUIRE(crusher::float_equal(res.z, -0.14419f));
      REQUIRE(crusher::float_equal(res.w, 0.3943f));

      t *= r;
      REQUIRE(t == crusher::quat(-0.3956f, 0.8095f, -0.14419f, 0.3943f));
    }

    SECTION("negation", "")
    {
      crusher::quat q(1.0f, 2.0f, 3.0f, -1.0f);
      crusher::quat neg(-1.0f, -2.0f, -3.0f, 1.0f);

      REQUIRE(-q == neg);
    }

    SECTION("invert", "")
    {
      crusher::quat r(0.0f, 0.7071068f, 0.0f, 0.7071068f);
      crusher::quat r_inv = r.inverted();

      REQUIRE((r_inv * r) == crusher::quat::identity);

      crusher::quat q(-0.1830127f, -0.5f, 0.6830127f, 0.5f);
      crusher::quat q_og = q;
      q.invert();

      REQUIRE((q * q_og) == crusher::quat::identity);
    }
  }

}
