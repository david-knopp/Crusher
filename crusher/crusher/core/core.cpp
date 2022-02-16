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
#include "core.h"
#include "system.h"
#include "entity.h"
#include "utils/debug/assert.h"

using namespace crusher;

core::core(void)
  : _running(false)
{
}

core::~core(void)
{
}

core& core::instance(void)
{
  static core c;
  return c;
}

void core::run(void)
{
  startup();

  while (_running)
    update();

  shutdown();
}

void core::quit(void)
{
  _running = false;
}

void core::startup(void)
{
  _running = true;

  for (auto& s : _system_list)
    s->startup();

  _frame_timer.start();
}

void core::update(void)
{

  //std::cout << _frame_timer.elapsed() << std::endl;
  //_frame_timer.start();
  //! TODO: get actual dt from frame_timer
  float dt = 0.016f;

  for (auto& s : _system_list)
    s->start_frame();

  for (auto& s : _system_list)
    s->update(dt);

  for (auto& s : _system_list)
    s->end_frame();

  // remove dead entities
  for (auto it = _entities.begin(); it != _entities.end();)
  {
    entity* e = it->second;
    if (e->dead())
      _entities.erase(it++);
    else
      ++it;
  }
}

void core::shutdown(void)
{
  for (auto& s : _system_list)
    s->shutdown();
}

crusher::system* core::add_system(const std::string& id, crusher::system* sys)
{
  error_if(_system_map.find(id) != _system_map.end(), 
           "attempting to add a duplicate system '%s'", id.c_str());

  _system_map.insert(system_pair(id, sys));
  _system_list.push_back(sys);
  return sys;
}

void core::remove_system(const std::string& id)
{
  auto it = _system_map.find(id);
  if (it != _system_map.end())
  {
    _system_map.erase(it);
    remove_listed_system(it->second);
  }
}

bool core::remove_listed_system(crusher::system* sys)
{
  for (auto it = _system_list.begin(); it != _system_list.end(); ++it)
  {
    if (*it == sys)
    {
      _system_list.erase(it);
      return true;
    }
  }

  return false;
}

crusher::system* core::get_system(const std::string& id)
{
  auto it = _system_map.find(id);
  error_if(it == _system_map.end(), 
    "attempting to get a system that the engine doesn't own: '%s'", id.c_str());

  return it->second;
}

bool core::has_system(const std::string& id)
{
  auto it = _system_map.find(id);
  return (it != _system_map.end());
}

entity& core::create_entity(const std::string& name)
{
  error_if(_entities.find(name) != _entities.end(), 
    "attempting to create an entity that already exists: '%s'", name.c_str());

  entity* e = new entity(name);
  _entities.insert(entity_pair(name, e));

  return (*e);
}

void core::destroy_entity(const std::string& name)
{
  auto it = _entities.find(name);
  if (it != _entities.end())
  {
    entity* e = it->second;
    e->destroy();
  }
}

entity& core::get_entity(const std::string& name)
{
  auto it = _entities.find(name);
  error_if(it == _entities.end(), 
    "attempting to get an entity that doesn't exist: '%s'", name.c_str());

  return (*it->second);
}

bool core::has_entity(const std::string& name)
{
  auto it = _entities.find(name);
  return (it != _entities.end());
}
