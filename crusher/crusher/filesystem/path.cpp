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
#include "path.h"

using namespace crusher;

path::path(void)
{
}

path::path(const std::string& p)
  : _entire_path(p)
{
  construct();
}

path::path(const char* p)
  : _entire_path(p)
{
  construct();
}

const std::string& path::filename(void) const
{
  return _filename;
}

const std::string& path::extension(void) const
{
  return _extension;
}

const std::string& path::directory(void) const
{
  return _directory;
}

const std::string& path::entire_path(void) const
{
  return _entire_path;
}

void path::construct(void)
{
  // find filename subdivisions
  std::size_t dir_end = _entire_path.find_last_of("\\/");
  std::size_t name_end = _entire_path.find_last_of(".");

  // extract file info
  _directory = _entire_path.substr(0, dir_end + 1);

  if (dir_end != _entire_path.npos)
   _filename = _entire_path.substr(dir_end + 1);
  else
    _filename = _entire_path;

  if (name_end != _entire_path.npos)
    _extension = _entire_path.substr(name_end + 1);
}

path& path::append(const path& append_path)
{
  _entire_path += append_path._entire_path;
  construct();
  return *this;
}

path& path::prepend(const path& prepend_path)
{
  _entire_path = (prepend_path._entire_path + _entire_path);
  construct();
  return *this;
}

path path::operator+(const path& rhs) const
{
  return path(_entire_path + rhs._entire_path);
}

path& path::operator+=(const path& rhs)
{
  return append(rhs);
}

bool path::operator==(const path& rhs) const
{
  return _entire_path == rhs._entire_path;
}

bool path::operator!=(const path& rhs) const
{
  return _entire_path != rhs._entire_path;
}
