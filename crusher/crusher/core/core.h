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
#include "utils/time/timer.h"
#include <map>
#include <list>
#include <string>
#include <vector>

namespace crusher
{

  // forward declarations
  class system;
  class entity;

  /* core engine, maintains entities and systems */
  class core
  {
    public:
      // public methods
      static core& instance(void);
      void run(void);
      void quit(void);

      // system functionality
      template <typename system_type, typename... param_types>
      system_type& add_system(param_types... params);
      system* add_system(const std::string& id, system* sys);

      template <typename system_type>
      void remove_system(void);
      void remove_system(const std::string& id);

      template <typename system_type>
      system_type& get_system(void);
      system* get_system(const std::string& id);

      template <typename system_type>
      bool has_system(void);
      bool has_system(const std::string& id);
      
      // entity functionality
      entity& create_entity(const std::string& name);
      void destroy_entity(const std::string& name);
      entity& get_entity(const std::string& name);
      bool has_entity(const std::string& name);

    private:
      // typedef
      typedef std::map<std::string, system*> system_container;
      typedef std::pair<std::string, system*> system_pair;
      typedef std::vector<system*> system_list;
      typedef std::map<std::string, entity*> entity_container;
      typedef std::pair<std::string, entity*> entity_pair;
      typedef std::list<entity*> entity_list;

      // private members
      system_container _system_map;
      system_list _system_list;
      entity_container _entities;
      timer _frame_timer;
      bool _running;

      // instance protection
      core(void);
      core(const core&) {}
      ~core(void);
      void operator=(const core&) {}

      // private methods
      void startup(void);
      void update(void);
      void shutdown(void);

      bool remove_listed_system(system* sys);

  }; // class core

} // namespace crusher

// template definitions
#include "core_template_bodies.h"
