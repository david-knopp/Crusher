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
#include "window_manager.h"
#include "core/core.h"
#include "input/input_manager.h"

using namespace crusher;

const std::string window_manager::id = "window_manager";
signal<int, int> window_manager::on_resize;

window_manager::window_manager(int width, int height, 
                               const std::string& window_title)
  : _title(window_title)
  , _glfw_window(nullptr)
  , _width(width)
  , _height(height)
  , _created(false)
  , _console(false)
{
}

window_manager::~window_manager(void)
{
}

void window_manager::startup(void)
{
  // init glfw
  if (glfwInit())
  {
    // create glfw window
    _glfw_window = glfwCreateWindow(_width, _height, _title.c_str(), 
                                    nullptr, nullptr);
    if (_glfw_window)
    {
      glfwMakeContextCurrent(_glfw_window);
      _created = true;
    }

    // register resize callback
    glfwSetWindowSizeCallback(_glfw_window, resize);

    // register glfw input callbacks
    glfwSetKeyCallback(_glfw_window, input_manager::key_callback);
    glfwSetMouseButtonCallback(_glfw_window, input_manager::mouse_button_callback);
    glfwSetCursorPosCallback(_glfw_window, input_manager::cursor_pos_callback);
  }

  if (_created == false)
    quit();
}

void window_manager::update(float)
{
  glfwPollEvents();

  if (glfwWindowShouldClose(_glfw_window))
    quit();
}

void window_manager::end_frame(void)
{
  swap_buffers();
}

void window_manager::shutdown(void)
{
  if (!_created)
    return;

  // destroy glfw window
  glfwTerminate();
  _created = false;
}

int window_manager::width(void)
{
  return _width;
}

int window_manager::height(void)
{
  return _height;
}

void window_manager::create_console(void)
{
  if (_console)
      return;

  if (AllocConsole())
  {
    __pragma(warning(push))
    __pragma(warning(disable : 4996))

    std::freopen("CON", "r", stdin);
    std::freopen("CON", "w", stdout);
    std::freopen("CON", "w", stderr);

    __pragma(warning(pop));

    _console = true;
  }
}

void window_manager::destroy_console(void)
{
  if (_console)
  {
    _console = false;
    FreeConsole();
  }
}

GLFWwindow* window_manager::get_glfw_window(void)
{
  return _glfw_window;
}

void window_manager::quit(void)
{
  core::instance().quit();
}

void window_manager::swap_buffers(void)
{
  glfwSwapBuffers(_glfw_window);
}

void window_manager::resize(GLFWwindow*, int width, int height)
{
  on_resize(width, height);
}
