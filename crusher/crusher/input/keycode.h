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

  // input keycodes
  typedef enum keycode
  {
    k_space = 32,

    // numeric keys
    k_0 = 48,
    k_1,
    k_2,
    k_3,
    k_4,
    k_5,
    k_6,
    k_7,
    k_8,
    k_9,

    // alphabetical
    k_A = 65,
    k_B,
    k_C,
    k_D,
    k_E,
    k_F,
    k_G,
    k_H,
    k_I,
    k_J,
    k_K,
    k_L,
    k_M,
    k_N,
    k_O,
    k_P,
    k_Q,
    k_R,
    k_S,
    k_T,
    k_U,
    k_V,
    k_W,
    k_X,
    k_Y,
    k_Z,

    k_escape = 256,

    k_right = 262,
    k_left,
    k_down,
    k_up,

    k_num_keys

  }; // typedef enum keycode

} // namespace crusher
