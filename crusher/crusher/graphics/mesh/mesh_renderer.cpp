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
#include "mesh_renderer.h"
#include "graphics/mesh/mesh.h"
#include "core/core.h"
#include "graphics/system/graphics_system.h"
#include "math/transform/transform3d.h"
#include "math/quat.h"

using namespace crusher;

const std::string mesh_renderer::id = "mesh_renderer";

mesh_renderer::mesh_renderer(void)
  : _mesh(nullptr)
{
}

mesh_renderer::mesh_renderer(const path& mesh_file)
  : _mesh(core::instance().get_system<graphics_system>().load_mesh(mesh_file))
{
}

mesh_renderer::mesh_renderer(const mesh::vertex_list& vertices, 
                             const mesh::index_list& indices)
  : _mesh(new mesh(vertices, indices))
{
}

void mesh_renderer::startup(void)
{
  graphics_system& graphics = core::instance().get_system<graphics_system>();
  graphics.add_component(this);
}

void mesh_renderer::shutdown(void)
{
  graphics_system& graphics = core::instance().get_system<graphics_system>();
  graphics.remove_component(this);
}

void mesh_renderer::render(void)
{
  graphics_system& graphics = core::instance().get_system<graphics_system>();
  shader_manager& shader_mgr = graphics.shader_mgr;

  transform3d& trans = get_component<transform3d>();
  
  /////////////////////////////////////////
  //static vec3 rot(0, 0, 0);
  //rot.y += 0.001f;
  //rot.z += 0.001f;
  //quat q;
  //q.set_euler(rot.x, rot.y, rot.z);
  //trans.set_rotation(q);
  /////////////////////////////////////////

  camera* cam = get_system<graphics_system>().get_active_camera();
  mat4 model_to_cam = cam->get_view_matrix() * trans.model_to_world();

  // setup shader uniforms
  shader_mgr.bind("phong");
  shader_mgr.set_data("model_to_cam", model_to_cam);

  mat3 normal_matrix = model_to_cam.to_mat3();
  normal_matrix.invert();
  shader_mgr.set_data("normal_matrix", normal_matrix.transpose());

  // render mesh
  _mesh->bind();
  _mesh->render();
  _mesh->unbind();

  shader_mgr.unbind();
}