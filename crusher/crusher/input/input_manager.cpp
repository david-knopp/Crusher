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
#include "input_manager.h"

using namespace crusher;

const std::string input_manager::id = "input_manager";

bool input_manager::_cur[keycode::k_num_keys] = { 0 };
bool input_manager::_prev[keycode::k_num_keys] = { 0 };

input_manager::input_manager(void)
{
}

input_manager::~input_manager(void)
{
}

void input_manager::update(float)
{
  for (int i = 0; i < keycode::k_num_keys; ++i)
  {
    _prev[i] = _cur[i];
  }
}

bool input_manager::get_key_triggered(keycode key)
{
  return (_cur[key] && !_prev[key]);
}

bool input_manager::get_key_down(keycode key)
{
  return (_cur[key] && _prev[key]);
}

bool input_manager::get_key_up(keycode key)
{
  return (!_cur[key] && !_prev[key]);
}

bool input_manager::get_key_released(keycode key)
{
  return (!_cur[key] && _prev[key]);
}

void input_manager::key_callback(GLFWwindow*, int key, int, int action, int)
{
  if (key < keycode::k_num_keys && key > 0)
    {
      if (action == GLFW_PRESS)
        _cur[key] = true;
      else if (action == GLFW_RELEASE)
        _cur[key] = false;
    }
}

void input_manager::mouse_button_callback(GLFWwindow*, int, int, int)
{
}

void input_manager::cursor_pos_callback(GLFWwindow*, double, double)
{
}
