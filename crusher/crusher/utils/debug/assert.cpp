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
#include "assert.h"
#include <cstdio> // sprintf_s, vsnprintf_s
#include <string>

#ifdef _MSC_VER
#include <windows.h>

static const int msg_size = 1024;

void crusher::report_conditional_failure(const char * cond, const char * file, int line, const char * msg, ...)
{
  char user_msg[msg_size] = { 0 };
  std::string final_msg;

  // copy user message
  if (msg != nullptr)
  {
    va_list args;
    va_start(args, msg);
    vsnprintf_s(user_msg, msg_size, _TRUNCATE, msg, args);
    va_end(args);
    final_msg = user_msg + std::string("\n\n");
  }

  // extract filename from file path
  std::string filename(file);
  auto it = filename.find_last_of("\\/");

  // combine file, line number, and error message
  final_msg += std::string("error:\n") + cond + "\n\nfile:\n" + filename.substr(it + 1) 
            + " (line: " + std::to_string(line) + ")";

  // create message box
  MessageBoxA(nullptr, final_msg.c_str(), "assertion failure", 0);
}

void crusher::report_failure(const char * file, int line, const char * msg, ...)
{
  char user_msg[msg_size] = { 0 };
  std::string final_msg;

  // copy user message
  if (msg != nullptr)
  {
    va_list args;
    va_start(args, msg);
    vsnprintf_s(user_msg, msg_size, _TRUNCATE, msg, args);
    va_end(args);
    final_msg = user_msg + std::string("\n\n");
  }

  // extract filename from file path
  std::string filename(file);
  auto it = filename.find_last_of("\\/");

  // combine file, line number, and error message
  final_msg += std::string("file:\n") + filename.substr(it + 1) 
    + " (line: " + std::to_string(line) + ")";

  // create message box
  MessageBoxA(nullptr, final_msg.c_str(), "assertion failure", 0);
}

#else
/* non MSVC */
#include <cassert>
void crusher::report_conditional_failure(const char * cond, const char * file, int line, const char * msg, ...) { std::assert(true); }
void crusher::report_failure(const char * file, int line, const char * msg, ...) { std::assert(true); }
#endif
