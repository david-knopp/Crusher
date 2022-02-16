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
#include "entity.h"
#include "utils/debug/assert.h"

using namespace crusher;

entity::entity(void)
  : _dead(false)
{
}

entity::entity(const std::string& name)
  : _name(name)
  , _dead(false)
{
}

entity::~entity(void)
{
}

const std::string& entity::name(void) const
{
  return _name;
}

component& entity::add_component(const std::string& id, component* comp)
{
  error_if(_components.find(id) != _components.end(), 
           "entity '%s' already has component '%s.'", _name.c_str(), id.c_str());

  comp->_owner = this;
  _components.insert(component_pair(id, comp));
  comp->startup();

  return (*comp);
}

component& entity::get_component(const std::string& id) const
{
  auto it = _components.find(id);
  error_if(it == _components.end(), 
           "entity '%s' doesn't have component '%s.'", _name.c_str(), id.c_str());

  return (*it->second);
}

bool entity::has_component(const std::string& id) const
{
  return (_components.find(id) != _components.end());
}

void entity::remove_component(const std::string& id)
{
  auto it = _components.find(id);
  if (it != _components.end())
  {
    it->second->shutdown();
    _components.erase(it);
  }
}

void entity::destroy(void)
{
  _dead = true;
}

bool entity::dead(void)
{
  return _dead;
}
