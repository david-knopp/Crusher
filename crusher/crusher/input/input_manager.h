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
#include "keycode.h"

// forward declarations
  struct GLFWwindow;

namespace crusher
{

  /* manages keyboard/mouse/gamepad input */
  class input_manager : public system
  {
    public:
      // static members
      static const std::string id;

      // ctor / dtor
      input_manager(void);
      ~input_manager(void);

      // overrides
      void update(float) override;

      // public methods
      static bool get_key_triggered(keycode key);
      static bool get_key_down(keycode key);
      static bool get_key_up(keycode key);
      static bool get_key_released(keycode key);

      // input callbacks
      static void key_callback(GLFWwindow* window, int key, int, int action, int mods);
      static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
      static void cursor_pos_callback(GLFWwindow* window, double x, double y);

    private:
      // private static members
      static bool _cur[keycode::k_num_keys];
      static bool _prev[keycode::k_num_keys];

  }; // class input_manager

} // namespace crusher
