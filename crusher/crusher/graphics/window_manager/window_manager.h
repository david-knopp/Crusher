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
#include "utils/signal/signal.h"

// forward declarations
struct GLFWwindow;

namespace crusher
{

  /* manages window creation, destruction, and events */
  class window_manager : public system
  {
    public:
      // static members
      static const std::string id;

      // public members
      static signal<int, int> on_resize;

      // ctor / dtor
      window_manager(int width, int height, const std::string& window_title);
      ~window_manager(void);
      
      // overriden methods
      void startup(void) override;
      void update(float) override;
      void end_frame(void) override;
      void shutdown(void) override;

      // public methods
      int width(void);
      int height(void);
      void create_console(void);
      void destroy_console(void);
      GLFWwindow* get_glfw_window(void);
      void quit(void);

      // buffers
      void swap_buffers(void);

    private:
      // private members
      std::string _title;
      GLFWwindow* _glfw_window;
      int _width;
      int _height;
      bool _created;
      bool _console;

      static void resize(GLFWwindow*,int,int);

  }; // class window_manager

} // namespace crusher
