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
#include "math/mat4.h"
#include "math/vec2.h"

namespace crusher
{

  class camera : public component
  {
    public:
      // static members
      static const std::string id;

      // ctors
      camera(void);
      camera(float fov_degrees, float z_near, float z_far);

      // public methods
      void set_viewport(float width, float height);
      void set_viewport(const vec2& viewport);

      void set_fov(float fov_degrees);

      mat4 get_view_matrix(void) const;
      mat4 get_proj_matrix(void) const;

    private:
      // private members
      vec2 _viewport;
      float _fov;
      float _near;
      float _far;

  }; // class camera

} // namespace crusher
