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
#include "graphics_system.h"
#include "graphics/render_context/render_context.h"
#include "graphics/mesh/mesh.h"
#include "graphics/mesh/mesh_renderer.h"
#include "graphics/window_manager/window_manager.h"
#include "utils/delegate/delegate.h"


#include "graphics/shader/shader_program.h"
#include "math/transform/transform3d.h"
#include "core/core.h"
#include "input/input_manager.h"

using namespace crusher;

const std::string graphics_system::id = "graphics_system";

graphics_system::graphics_system(void)
  : _camera(nullptr)
{
}

graphics_system::~graphics_system(void)
{
}

///////////////////////// REMOVE
entity* cam;
vertex make_vertex(const vec3& pos, const vec3& norm)
{
  vertex v;
  v.pos = pos;
  v.norm = norm;
  //v.tex = vec2::zero;

  return v;
}

entity* light_entity;

void graphics_system::startup(void)
{
  render_context::initialize();

  shader_program* default = new shader_program("phong", "..\\resources\\shaders\\default.vert", 
                                               "..\\resources\\shaders\\phong.frag");
  shader_mgr.add_program(default);

  // init available light ids
  for (int i = 0; i < 8; ++i)
    _free_light_ids.push_back(i);

  /////////////////////////////////////////////////

  entity& e = core::instance().create_entity("test");
  e.add_component<mesh_renderer>("..\\resources\\models\\sphere.obj");
  auto& trans = e.add_component<transform3d>();
  trans.set_position(0.0f, 0, -10.0f);
  trans.set_scale(2, 2, 2);

  cam = &core::instance().create_entity("camera");
  cam->add_component<transform3d>();
  _camera = &cam->add_component<camera>(60.0f, 1.0f, 100.0f);

  light_entity = &core::instance().create_entity("light");
  light& l = light_entity->add_component<light>();
  transform3d& light_trans = light_entity->add_component<transform3d>();
  light_entity->add_component<mesh_renderer>("..\\resources\\models\\sphere.obj");

  l.ambient = vec3(0.1f, 0.1f, 0.1f);
  l.diffuse = vec3(1.0f, 1.0f, 1.0f);
  l.specular = vec3(1.0f, 1.0f, 1.0f);
  l.active = true;

  light_trans.set_position(0.0f, 0.0f, -3.0f);
  light_trans.set_scale(0.5f, 0.5f, 0.5f);

  //////////////////////////////////////////////////

  window_manager& window = get_system<window_manager>();
  resize(window.width(), window.height());
  window_manager::on_resize += make_delegate(&graphics_system::resize, this);
}

void graphics_system::shutdown(void)
{
  // delete meshes
  for (const mesh_pair& m : _meshes)
    delete m.second;
  _meshes.clear();
}

void graphics_system::update(float)
{
  ////////////////////////////////////////
  const float speed = 0.01f;

  transform3d& trans = light_entity->get_component<transform3d>();
  if (input_manager::get_key_down(keycode::k_D))
  {
    vec3 pos = trans.position();
    pos.x += speed;
    trans.set_position(pos);
  }
  else if (input_manager::get_key_down(keycode::k_A))
  {
    vec3 pos = trans.position();
    pos.x -= speed;
    trans.set_position(pos);
  }
  if (input_manager::get_key_down(keycode::k_W))
  {
    vec3 pos = trans.position();
    pos.y += speed;
    trans.set_position(pos);
  }
  else if (input_manager::get_key_down(keycode::k_S))
  {
    vec3 pos = trans.position();
    pos.y -= speed;
    trans.set_position(pos);
  }

  ///////////////////////////////////////

  render_context::clear_frame_buffer();

  shader_mgr.bind("phong");
  shader_mgr.set_data("cam_to_proj", _camera->get_proj_matrix());

  for (auto l : _lights)
    l->update();

  shader_mgr.unbind();

  // render meshes
  for (auto renderer : _mesh_renderers)
    renderer->render();
}

mesh* graphics_system::load_mesh(const path& file)
{
  auto it = _meshes.find(file.filename());
  
  // check if mesh is already loaded
  if (it != _meshes.end())
    return it->second;

  // load mesh
  mesh* m = new mesh;
  m->load(file);
  _meshes.insert(mesh_pair(file.filename(), m));

  return m;
}

camera* graphics_system::get_active_camera(void) const
{
  return _camera;
}

void graphics_system::set_active_camera(camera* cam)
{
  _camera = cam;
}

void graphics_system::add_component(mesh_renderer* renderer)
{
  _mesh_renderers.push_back(renderer);
}

void graphics_system::remove_component(mesh_renderer* renderer)
{
  _mesh_renderers.remove(renderer);
}

void graphics_system::add_component(light* l)
{
  _lights.push_back(l);

  // set id
  if (_free_light_ids.size() != 0)
  {
    l->set_id(_free_light_ids.front());
    _free_light_ids.remove(_free_light_ids.front());
  }
}

void graphics_system::remove_component(light* l)
{
  // free id
  int id = l->get_id();
  if (id > 0)
    _free_light_ids.push_back(id);

  _lights.remove(l);
}

void graphics_system::resize(int width, int height)
{
  _viewport.x = static_cast<float>(width);
  _viewport.y = static_cast<float>(height);

  if (_camera != nullptr)
    _camera->set_viewport(_viewport);
}
