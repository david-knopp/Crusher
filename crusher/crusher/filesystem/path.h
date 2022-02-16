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
#include <string>

namespace crusher
{

  class path
  {
    public:
      // ctors
      path(void);
      path(const std::string& p);
      path(const char* p);

      // public methods
      const std::string& filename(void) const;
      const std::string& extension(void) const;
      const std::string& directory(void) const;
      const std::string& entire_path(void) const;

      path& append(const path& append_path);
      path& prepend(const path& prepend_path);

      // operators
      path operator+(const path& rhs) const;
      path& operator+=(const path& rhs);

      bool operator==(const path& rhs) const;
      bool operator!=(const path& rhs) const;

    private:
      // privat members
      std::string _filename;
      std::string _extension;
      std::string _directory;
      std::string _entire_path;

      // private methods
      void construct(void);

  }; // class path

} // namespace crusher
