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
#include "callback.h"
#include "static_function_callback.h"
#include "member_function_callback.h"

namespace crusher
{

  /* delegate class */
  template <typename ret_type, typename... param_types>
  class delegate
  {
    public:
      // static function ctor
      delegate(ret_type (*fun)(param_types...))
        : _callback(new static_function_callback<ret_type, param_types...>(fun))
      {
      }

      // member function ctor
      template <typename obj_type>
      delegate(ret_type (obj_type::*fun)(param_types...), obj_type * obj)
        : _callback(new member_function_callback<obj_type, ret_type, param_types...>(fun, obj))
      {
      }

      // copy ctor
      delegate(const delegate& copy)
        : _callback(copy._callback->clone())
      {
      }

      ~delegate(void) 
      { 
        delete _callback; 
      }

      // public methods
      ret_type operator()(param_types... params)
      { 
        return ((*_callback)(params...));
      }

      bool operator==(const delegate& rhs) const
      {
        return *_callback == *(rhs._callback);
      }

      delegate& operator=(const delegate& rhs)
      {
        if (this != &rhs)
        {
          callback<ret_type, param_types...>* callback = rhs._callback->clone();
          delete _callback;
          _callback = callback;
        }
        return *this;
      }

    private:
      // private members
      callback<ret_type, param_types...>* _callback;

  }; // class delegate

  template <typename ret_type, typename... param_types>
  static delegate<ret_type, param_types...> make_delegate(ret_type (*func)(param_types...))
  {
    return (delegate<ret_type, param_types...>(func));
  }

  template <typename obj_type, typename ret_type, typename... param_types>
  static delegate<ret_type, param_types...> make_delegate(ret_type (obj_type::*func)(param_types...), obj_type* obj)
  {
    return (delegate<ret_type, param_types...>(func, obj));
  }

} // namespace crusher