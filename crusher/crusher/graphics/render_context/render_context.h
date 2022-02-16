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
#include "graphics/handle/handle.h"
#include "graphics/types/buffer_usage.h"
#include "graphics/vertex/vertex.h"
#include "math/vec4.h"
#include <vector>

namespace crusher
{

  /* manages opengl-specific rendering functionality */
  class render_context
  {
    public:
      // public typedefs
      typedef std::vector<vertex> vertex_list;
      typedef std::vector<unsigned> index_list;

      // ctor / dtor
      render_context(void);
      ~render_context(void);

      // public methods
      static bool initialize(void);

      // clear color
      static void set_clear_color(float r, float g, float b, float a);
      static void set_clear_color(const vec4& color);

      // buffer creation
      static bool create_vertex_buffer(handle& vertex_buffer);
      static bool create_vertex_array(handle& vertex_array);
      static bool create_index_buffer(handle& index_buffer);

      // data buffering
      static void set_vertex_data(const vertex_list& vertices, buffer_usage usage);
      static void set_index_data(const index_list& indices, buffer_usage usage);

      // buffer destruction
      static void destroy_vertex_buffer(handle& vertex_buffer);
      static void destroy_vertex_array(handle& vertex_array);
      static void destroy_index_buffer(handle& index_buffer);

      // binding
      static void bind_vertex_buffer(const handle& vertex_buffer);
      static void unbind_vertex_buffer(void);
      static void bind_vertex_array(const handle& vertex_array);
      static void unbind_vertex_array(void);
      static void bind_vertex_attribs(void);
      static void bind_index_buffer(const handle& index_buffer);
      static void unbind_index_buffer(void);

      // drawing
      static void draw_array(int count);
      static void draw_array_offset(int count, int offset);
      static void draw_elements(int num_indices);

      // clearing
      static void clear_frame_buffer(void);

    private:
      // private members

      // private methods

  }; // class render_context

} // namespace crusher
