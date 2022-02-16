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
#include "core/system.h"
#include "filesystem/path.h"
#include "graphics/shader/shader_manager.h"
#include "graphics/camera/camera.h"
#include "graphics/lighting/light.h"
#include <unordered_map>

namespace crusher
{

  // forward declarations
  class render_context;
  class mesh;
  class mesh_renderer;

  /* handles graphical rendering */
  class graphics_system : public system
  {
    public:
      // static members
      static const std::string id;

      // public members
      shader_manager shader_mgr;

      // ctor / dtor
      graphics_system(void);
      ~graphics_system(void);

      // overriden methods
      void startup(void) override;
      void shutdown(void) override;
      void update(float) override;

      mesh* load_mesh(const path& file);

      // camera
      camera* get_active_camera(void) const;
      void set_active_camera(camera* cam);

      // components
      void add_component(mesh_renderer* renderer);
      void remove_component(mesh_renderer* renderer);

      void add_component(light* l);
      void remove_component(light* l);

    private:
      // private types
      typedef std::unordered_map<std::string, mesh*> mesh_container;
      typedef std::pair<std::string, mesh*> mesh_pair;
      typedef std::list<mesh_renderer*> renderer_container;
      typedef std::list<light*> light_container;

      // private members
      mesh_container _meshes;
      renderer_container _mesh_renderers;
      light_container _lights;
      std::list<int> _free_light_ids;
      vec2 _viewport;
      camera* _camera;

      // private methods
      void resize(int width, int height);

  }; // class graphics_system

} // namespace crusher
