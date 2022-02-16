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
#include "core/core.h"
#include <string>

namespace crusher
{

  /* system interface */
  class system
  {
    public:
      // static members
      // id used to identify component, must be defined uniquely per subclass
      static const std::string id;
      
      // ctor / dtor
      system(void) {}
      virtual ~system(void) {}

      // public methods
      // called once when the engine begins
      virtual void startup(void) {}
      // called once when the engine shuts down
      virtual void shutdown(void) {}

      // called before all system updates each frame
      virtual void start_frame(void) {}
      // called once per frame
      virtual void update(float dt);
      // called after all system updates each frame
      virtual void end_frame(void) {}

      template<typename system_type>
      system_type& get_system(void) const
      {
        return core::instance().get_system<system_type>();
      }

    private:

  }; // class system

} // namespace crusher
