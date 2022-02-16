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

namespace crusher
{

  /* base runnable action */
  class action
  {
    public:
      // ctor / dtor
      action(bool blocking = false);
      virtual ~action(void);

      // public methods
      virtual void startup(void) {}
      virtual void update(float) {}
      virtual void shutdown(void) {}

      void pause(void);
      void resume(void);
      void set_finished(void);

      void block(void);
      void unblock(void);
      void set_blocking(bool blocking);

      bool is_started(void) const;
      bool is_paused(void) const;
      bool is_finished(void) const;
      bool is_blocking(void) const;

    private:
      // private members
      bool _blocking;
      bool _started;
      bool _finished;
      bool _paused;

      friend class action_list;

  }; // class action

} // namespace crusher
