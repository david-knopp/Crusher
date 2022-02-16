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
#include "core/component.h"
#include "math/vec3.h"
#include "math/quat.h"
#include "math/mat4.h"

namespace crusher
{

  class transform3d : public component
  {
    public:
      // static members
      static const std::string id;

      // ctor
      transform3d(void);

      // getters
      const vec3& position(void) const;

      const quat& rotation(void) const;
      vec3 rotation_euler_rad(void) const;
      vec3 rotation_euler_deg(void) const;

      const vec3& scale(void) const;

      // orientation
      vec3 right(void);
      vec3 up(void);
      vec3 forward(void);

      // setters
      void set_position(const vec3& pos);
      void set_position(float x, float y, float z);

      void set_rotation(const quat& rot);
      void set_euler_rad(const vec3& rad);
      void set_euler_rad(float rad_x, float rad_y, float rad_z);
      void set_euler_deg(const vec3& deg);
      void set_euler_deg(float deg_x, float deg_y, float deg_z);

      void set_scale(const vec3& scale);
      void set_scale(float x, float y, float z);

      // matrix transformation
      const mat4& model_to_world(void);

    private:
      // private members
      mat4 _m_to_w;
      quat _orient;
      vec3 _pos;
      vec3 _scale;
      bool _dirty;

      // private methods
      const mat4& calculate_m_to_w(void);

  }; // transform3d

} // namespace crusher
