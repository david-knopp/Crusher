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
#include "utils/delegate/delegate.h"
#include <vector>
#include <algorithm>

namespace crusher
{

  /* signal dispatch object, allows method registration and dispatch */
  template <typename... param_types>
  class signal
  {
    public:
      // typedefs
      typedef delegate<void, param_types...> method;

      // public methods
      void add(method callback, bool dispatch_once = false)
      {
        _listeners.push_back(listener(callback, dispatch_once));
      }

      void operator+=(method callback)
      {
        add(callback);
      }

      void remove(method callback)
      {
        auto it = std::remove_if(_listeners.begin(), _listeners.end(), 
          [&callback](listener& l)
          {
            return l.callback == callback;
          });
        _listeners.erase(it, _listeners.end());
      }

      void dispatch(param_types... params)
      {
        for (auto it = _listeners.begin(); it != _listeners.end();)
        {
          listener& l = *it;
          l.callback(params...);

          if (l.once)
            it = _listeners.erase(it);
          else
            ++it;
        }
      }

      void operator()(param_types... params)
      {
        dispatch(params...);
      }

    private:
      // private types
      struct listener
      {
        listener(method _callback, bool _once)
          : callback(_callback)
          , once(_once)
        {
        }

        method callback;
        bool once;
      }; // struct listener

      // private members
      std::vector<listener> _listeners;

  }; // class signal

} // namespace crusher
