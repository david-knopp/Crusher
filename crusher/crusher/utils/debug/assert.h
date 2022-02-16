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
// disable the constant-conditional warning in MSVC
#pragma warning(disable : 4127)

#ifdef _MSC_VER
#define HALT __debugbreak()
#else
#define HALT
#endif

// helper functions
namespace crusher
{
  void report_conditional_failure(const char * cond, const char * file, int line, const char * msg = nullptr, ...);
  void report_failure(const char * file, int line, const char * msg, ...);
} // namespace crusher

#ifdef _DEBUG
#define assert(condition, ...) \
do \
{ \
  if (!(condition)) \
  { \
    crusher::report_conditional_failure(#condition, __FILE__, __LINE__, __VA_ARGS__); \
    HALT; \
  } \
} while (0);

#define error_if(condition, ...) \
do \
{ \
  if (condition) \
  { \
    crusher::report_conditional_failure(#condition, __FILE__, __LINE__, __VA_ARGS__); \
    HALT; \
  } \
} while (0);

#define error(...) \
do \
{ \
  crusher::report_failure(__FILE__, __LINE__, __VA_ARGS__); \
  HALT; \
} while (0);

#define report_if(condition, ...) \
do \
{ \
  if (condition) \
  { \
    crusher::report_conditional_failure(#condition, __FILE__, __LINE__, __VA_ARGS__); \
  } \
} while (0);

#define report(...) \
  crusher::report_failure(__FILE__, __LINE__, __VA_ARGS__);

#else
// do nothing
#define assert(...)
#define error_if(...)
#define error(...)
#define report_if(...)
#define report(...)
#endif // _DEBUG
