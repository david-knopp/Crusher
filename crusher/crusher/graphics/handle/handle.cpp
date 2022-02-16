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
#include "handle.h"
#include "graphics/types/object_type.h"
#include <climits>

using namespace crusher;

const handle handle::null;

handle::handle(void)
  : _handle(UINT_MAX)
  , _type(object_type::NONE)
{
}

handle::~handle(void)
{
}

unsigned& handle::operator*(void)
{
  return _handle;
}

unsigned handle::operator*(void) const
{
  return _handle;
}

handle::operator bool(void) const
{
  return (_type != object_type::NONE && _handle != UINT_MAX);
}

object_type handle::type(void) const
{
  return _type;
}

handle handle::create_handle(unsigned int handle_value, object_type type)
{
  handle h;
  h._handle = handle_value;
  h._type = type;

  return h;
}
