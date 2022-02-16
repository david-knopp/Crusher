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

#include "crusher/precompiled.h"
#include "render_context.h"
#include "graphics/types/object_type.h"
#include "graphics/types/buffer_usage.h"

using namespace crusher;

enum class vertex_attribs
{
  POSITIONS,
  NORMALS,
  TEX_COORDS
};

render_context::render_context(void)
{
}

render_context::~render_context(void)
{
}

bool render_context::initialize(void)
{
  static bool initialized = false;

  if (initialized)
    return false;

  // init glew
  GLenum result = glewInit();
  if (result != GLEW_OK)
  {
    report("glew failed to initialize: %s.", glewGetErrorString(result));
    return false;
  }

  // init gl
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_DEPTH_CLAMP);
  glDepthRange(0.0f, 1.0f);
  glDepthFunc(GL_LEQUAL);
  glDepthMask(GL_TRUE);
  
  glClearColor(0, 0, 0, 0);
  glClearDepth(1.0f);
  
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  
  glFrontFace(GL_CCW);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  initialized = true;

  return true;
}

void render_context::set_clear_color(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a); 
}

void render_context::set_clear_color(const vec4& color)
{
  set_clear_color(color.r, color.g, color.b, color.a);
}

bool render_context::create_vertex_buffer(handle& vertex_buffer)
{
  // generate vertex buffer
  GLuint vbo;
  glGenBuffers(1, &vbo);
  vertex_buffer = handle::create_handle(vbo, object_type::VERTEX_BUFFER);

  return true;
}

bool render_context::create_vertex_array(handle& vertex_array)
{
  GLuint vao;
  glGenVertexArrays(1, &vao);
  vertex_array = handle::create_handle(vao, object_type::VERTEX_ARRAY);

  return true;
}

bool render_context::create_index_buffer(handle& index_buffer)
{
  GLuint ibo;
  glGenBuffers(1, &ibo);
  index_buffer = handle::create_handle(ibo, object_type::INDEX_BUFFER);

  return true;
}

void render_context::set_vertex_data(const vertex_list& vertices, buffer_usage usage)
{
  // bind vertex attribs
  bind_vertex_attribs();

  // copy data
  size_t size = vertices.size() * sizeof(vertex);
  glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), static_cast<GLenum>(usage));
}

void render_context::set_index_data(const index_list& indices, buffer_usage usage)
{
  // copy data
  size_t size = indices.size() * sizeof(GLuint);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices.data(), static_cast<GLenum>(usage));
}

void render_context::destroy_vertex_buffer(handle& vertex_buffer)
{
  error_if(vertex_buffer.type() != object_type::VERTEX_BUFFER, 
           "attempting to destroy an invalid handle to a vertex buffer.");
  glDeleteBuffers(1, &(*vertex_buffer));
}

void render_context::destroy_vertex_array(handle& vertex_array)
{
  error_if(vertex_array.type() != object_type::VERTEX_ARRAY, 
           "attempting to destroy an invalid handle to a vertex array.");
  glDeleteBuffers(1, &(*vertex_array));
}

void render_context::destroy_index_buffer(handle& index_buffer)
{
  error_if(index_buffer.type() != object_type::INDEX_BUFFER, 
           "attempting to destroy an invalid handle to an index buffer.");
  glDeleteBuffers(1, &(*index_buffer));
}

void render_context::bind_vertex_buffer(const handle& vertex_buffer)
{
  error_if(vertex_buffer.type() != object_type::VERTEX_BUFFER, 
           "attempting to bind an invalid handle to a vertex buffer.");
  glBindBuffer(GL_ARRAY_BUFFER, *vertex_buffer);
}

void render_context::unbind_vertex_buffer(void)
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void render_context::bind_vertex_array(const handle& vertex_array)
{
  error_if(vertex_array.type() != object_type::VERTEX_ARRAY, 
           "attempting to bind an invalid handle to a vertex array.");
  glBindVertexArray(*vertex_array);
}

void render_context::unbind_vertex_array(void)
{
  glBindVertexArray(0);
}

void render_context::bind_vertex_attribs(void)
{
  glEnableVertexAttribArray(static_cast<int>(vertex_attribs::POSITIONS));
  glEnableVertexAttribArray(static_cast<int>(vertex_attribs::NORMALS));
  glEnableVertexAttribArray(static_cast<int>(vertex_attribs::TEX_COORDS));

  glVertexAttribPointer(static_cast<int>(vertex_attribs::POSITIONS), 3, GL_FLOAT, GL_FALSE, 
                        sizeof(vertex), (GLvoid*)offsetof(vertex, pos));
  glVertexAttribPointer(static_cast<int>(vertex_attribs::NORMALS), 3, GL_FLOAT, GL_FALSE, 
                        sizeof(vertex), (GLvoid*)offsetof(vertex, norm));
  glVertexAttribPointer(static_cast<int>(vertex_attribs::TEX_COORDS), 2, GL_FLOAT, GL_FALSE, 
                        sizeof(vertex), (GLvoid*)offsetof(vertex, tex));
}

void render_context::bind_index_buffer(const handle& index_buffer)
{
  error_if(index_buffer.type() != object_type::INDEX_BUFFER, 
           "attempting to bind an invalid handle to an index buffer.");
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *index_buffer);
}

void render_context::unbind_index_buffer(void)
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void render_context::draw_array(int count)
{
  glDrawArrays(GL_TRIANGLES, 0, count);
}

void render_context::draw_array_offset(int count, int offset)
{
  glDrawArrays(GL_TRIANGLES, offset, count);
}

void render_context::draw_elements(int num_indices)
{
  glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}

void render_context::clear_frame_buffer(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
