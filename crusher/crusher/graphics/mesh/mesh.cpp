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
#include "mesh.h"
#include "graphics/render_context/render_context.h"
#include "graphics/types/buffer_usage.h"
#include "graphics/types/object_type.h"
#include "graphics/types/buffer_usage.h"
#include "graphics/mesh/obj_loader.h"

using namespace crusher;

mesh::mesh(void)
  : _num_indices(0)
{
}

mesh::mesh(const vertex_list& vertices, const index_list& indices)
  : _num_indices(indices.size())
{
  init(vertices, indices);
}

mesh::~mesh(void)
{
  render_context::destroy_vertex_buffer(_vtex_buffer);
  render_context::destroy_vertex_array(_vtex_array);
  render_context::destroy_index_buffer(_index_buffer);
}

bool mesh::load(const path& obj_file)
{
  obj_loader loader;
  if (loader.load(obj_file))
    return init(loader.get_vertices(), loader.get_indices());

  return false;
}

void mesh::render(void)
{
  render_context::draw_elements(_num_indices);
}

void mesh::bind(void)
{
  render_context::bind_vertex_array(_vtex_array);
}

void mesh::unbind(void)
{
  render_context::unbind_vertex_array();
}

bool mesh::init(const vertex_list& vertices, const index_list& indices)
{
  _num_indices = indices.size();

  // generate vertex array
  if (!render_context::create_vertex_array(_vtex_array))
  {
    report("couldn't create vertex array.");
    return false;
  }
  render_context::bind_vertex_array(_vtex_array);

  // generate vertex buffer
  if (!render_context::create_vertex_buffer(_vtex_buffer))
  {
    report("couldn't create vertex buffer.");
    return false;
  }
  render_context::bind_vertex_buffer(_vtex_buffer);
  // set vertex data
  render_context::set_vertex_data(vertices, buffer_usage::STATIC_DRAW);

  // generate index buffer
  if (!render_context::create_index_buffer(_index_buffer))
  {
    report("couldn't create index buffer.");
    return false;
  }
  render_context::bind_index_buffer(_index_buffer);
  // set index data
  render_context::set_index_data(indices, buffer_usage::STATIC_DRAW);

  // unbind buffer
  render_context::unbind_vertex_array();
  render_context::unbind_vertex_buffer();
  render_context::unbind_index_buffer();

  return true;
}
