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

#include <Windows.h>
#include <iostream>
#include "core/core.h"
#include "core/system.h"
#include "graphics/window_manager/window_manager.h"
#include "graphics/system/graphics_system.h"
#include "input/input_manager.h"
#include "core/entity.h"
#include "graphics/mesh/mesh_renderer.h"
#include "graphics/vertex/vertex.h"
#include "math/transform/transform3d.h"

using namespace crusher;
using namespace std;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  core& c = core::instance();
  c.add_system<window_manager>(800, 600, "crusher");
  c.add_system<graphics_system>();
  c.add_system<input_manager>();

  auto& window = c.get_system<window_manager>();
  window.create_console();

  c.run();

  return 0;
}
