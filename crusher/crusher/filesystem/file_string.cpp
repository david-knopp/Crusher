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
#include "file_string.h"

using namespace crusher;

file_string::file_string(const path& file_path)
  : _loaded(false)
{
  load_file(file_path.entire_path());
}

file_string::file_string(const std::string& file_path)
  : _loaded(false)
{
  load_file(file_path);
}

file_string::~file_string()
{
}

size_t file_string::size(void) const
{
  return _file_data.size();
}

const char* file_string::c_str(void) const
{
  return _file_data.c_str();
}

const std::string& file_string::str(void) const
{
  return _file_data;
}

bool file_string::loaded(void) const
{
  return _loaded;
}

void file_string::load_file(const std::string& file_path)
{
  std::FILE* file = nullptr;
  fopen_s(&file, file_path.c_str(), "rb");
  error_if(file == nullptr, "couldn't open file '%s'", file_path.c_str());
  if (file)
  {
    // resize string to size of the file
    std::fseek(file, 0, SEEK_END);
    _file_data.resize(std::ftell(file));

    // copy file data
    std::rewind(file);
    std::fread(&_file_data[0], 1, _file_data.size(), file);

    std::fclose(file);
    _loaded = true;
    return;
  }

  _loaded = false;
}
