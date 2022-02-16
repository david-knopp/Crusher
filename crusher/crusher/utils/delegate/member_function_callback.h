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

namespace crusher
{

  /* member function callback helper */
  template <typename obj_type, typename ret_type, typename... param_types>
  class member_function_callback : public callback<ret_type, param_types...>
  {
    public:
      // ctor
      member_function_callback(ret_type (obj_type::*func)(param_types...), obj_type * obj)
        : _func(func)
        , _obj(obj) 
      {
      }
      
      // public methods
      ret_type operator()(param_types... params)  override
      { 
        return (_obj->*_func)(params...); 
      }

      member_function_callback* clone(void) const override
      {
        return new member_function_callback(*this);
      }

      bool operator==(const callback& rhs) const override
      {
        const member_function_callback* _rhs = dynamic_cast<const member_function_callback*>(&rhs);
        if (_rhs)
          return (_obj == _rhs->_obj) && (_func == _rhs->_func);

        return false;
      }

    private:
      // private members
      obj_type* _obj;
      ret_type (obj_type::*_func)(param_types...);

  }; // class MemberFunctionCallback

} // namespace crusher
