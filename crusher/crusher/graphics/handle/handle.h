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

  // forward declarations
  enum class object_type;

  /* graphics api handle abstraction */
  class handle
  {
    public:
      // public static members
      static const handle null;

      // ctor / dtor
      handle(void);
      ~handle(void);

      // public methods
      unsigned& operator*(void);
      unsigned operator*(void) const;
      operator bool(void) const;

      object_type type(void) const;

      // static methods
      static handle create_handle(unsigned int handle_value, object_type type);

    private:
      // private members
      unsigned int _handle;
      object_type _type;

  }; // class handle

} // namespace crusher
