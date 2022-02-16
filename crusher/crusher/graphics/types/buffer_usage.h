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

  /* graphics buffer usage types */
  enum class buffer_usage
  {
    // draw
    STATIC_DRAW = GL_STATIC_DRAW,
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    STREAM_DRAW = GL_STREAM_DRAW,

    // read
    STATIC_READ = GL_STATIC_READ,
    DYNAMIC_READ = GL_DYNAMIC_READ,
    STREAM_READ = GL_STREAM_READ,

    // copy
    STATIC_COPY = GL_STATIC_COPY,
    DYNAMIC_COPY = GL_DYNAMIC_COPY,
    STREAM_COPY = GL_STREAM_COPY

  }; // typedef enum buffer_usage

} // namespace crusher
