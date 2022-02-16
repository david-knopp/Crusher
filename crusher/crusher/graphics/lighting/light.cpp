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
#include "light.h"
#include "graphics/system/graphics_system.h"
#include "math/transform/transform3d.h"

using namespace crusher;
using namespace std;

const std::string light::id = "light";

light::light(void)
  : ambient(vec3::zero)
  , diffuse(vec3::zero)
  , specular(vec3::zero)
  , active(true)
  , _id(-1)
{
}

void light::update(void)
{
  set_data();
}

void light::set_id(int id)
{
  _id = id;
}

int light::get_id(void) const
{
  return _id;
}

void light::startup(void)
{
  graphics_system& graphics = get_system<graphics_system>();
  graphics.add_component(this);
}

void light::shutdown(void)
{
  // deactivate light in shader
  active = false;
  set_data();

  graphics_system& graphics = get_system<graphics_system>();
  graphics.remove_component(this);
}

void light::set_data(void)
{
  // check if light is valid
  if (_id < 0)
    return;

  // get shader manager
  graphics_system& graphics = get_system<graphics_system>();
  shader_manager& shader_mgr = graphics.shader_mgr;

  // set lighting attributes
  string name = "lights[" + to_string(_id) + "]";
  shader_mgr.set_data(name + ".ambient", ambient);
  shader_mgr.set_data(name + ".diffuse", diffuse);
  shader_mgr.set_data(name + ".specular", specular);
  shader_mgr.set_data(name + ".active", active);

  // transform position to camera space
  transform3d trans = get_component<transform3d>();
  camera* cam = get_system<graphics_system>().get_active_camera();
  vec4 cam_pos = cam->get_view_matrix() * vec4(trans.position(), 1.0f);

  // set position
  shader_mgr.set_data(name + ".position", vec3(cam_pos.x, cam_pos.y, cam_pos.z));
}
