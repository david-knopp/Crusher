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
#include "unit_tests/catch.hpp"
#include "filesystem/path.h"

namespace path_tests
{

  TEST_CASE("path tests", "path tests")
  {
    SECTION("simple constructors", "")
    {
      crusher::path p;
      crusher::path p1("filesystem/path_tests.h");
      std::string dir("filesystem/path_tests.h");
      crusher::path p2(dir);

      // default
      REQUIRE(p.entire_path().length() == 0);
      REQUIRE(p.directory().length() == 0);
      REQUIRE(p.extension().length() == 0);
      REQUIRE(p.filename().length() == 0);

      // non-default (char*)
      REQUIRE(p1.entire_path() == "filesystem/path_tests.h");
      REQUIRE(p1.directory() == "filesystem/");
      REQUIRE(p1.extension() == "h");
      REQUIRE(p1.filename() == "path_tests.h");

      // non-default (string)
      REQUIRE(p2.entire_path() == "filesystem/path_tests.h");
      REQUIRE(p2.directory() == "filesystem/");
      REQUIRE(p2.extension() == "h");
      REQUIRE(p2.filename() == "path_tests.h");
    }

    SECTION("no extension", "")
    {
      crusher::path p("filesystem/path_tests");

      REQUIRE(p.entire_path() == "filesystem/path_tests");
      REQUIRE(p.directory() == "filesystem/");
      REQUIRE(p.extension() == "");
      REQUIRE(p.filename() == "path_tests");
    }

    SECTION("no directory", "")
    {
      crusher::path p("file.txt");

      REQUIRE(p.directory() == "");
      REQUIRE(p.extension() == "txt");
      REQUIRE(p.filename() == "file.txt");
    }

    SECTION("long path", "")
    {
      crusher::path p("some_directory/other.directory/myfiles/yourfiles/filesystem/path_tests.h");

      REQUIRE(p.directory() == "some_directory/other.directory/myfiles/yourfiles/filesystem/");
      REQUIRE(p.extension() == "h");
      REQUIRE(p.filename() == "path_tests.h");
    }

    SECTION("back slashes", "")
    {
      crusher::path p("this\\file\\better\\work.png");

      REQUIRE(p.directory() == "this\\file\\better\\");
      REQUIRE(p.extension() == "png");
      REQUIRE(p.filename() == "work.png");
    }

    SECTION("operators", "")
    {
      crusher::path file("my_secrets.zip");
      crusher::path file_copy(file);
      crusher::path p("top/secret/folder/");
      crusher::path p_copy(p);

      REQUIRE((p + file).entire_path() == "top/secret/folder/my_secrets.zip");
      REQUIRE(p != file);
      REQUIRE(p == p_copy);

      p.append(file);
      REQUIRE(p.entire_path() == "top/secret/folder/my_secrets.zip");
      REQUIRE(p.filename() == "my_secrets.zip");
      REQUIRE(p.extension() == "zip");
      REQUIRE(p.directory() == "top/secret/folder/");
      
      file_copy.prepend(p_copy);
      REQUIRE(file_copy.entire_path() == "top/secret/folder/my_secrets.zip");
      REQUIRE(file_copy.filename() == "my_secrets.zip");
      REQUIRE(file_copy.extension() == "zip");
      REQUIRE(file_copy.directory() == "top/secret/folder/");
    }
  }

}
