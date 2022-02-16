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
#include "interval_action.h"

using namespace crusher;

interval_action::interval_action(float time)
  : _total_time(time)
  , _elapsed(0.0f)
{
}

interval_action::~interval_action(void)
{
}

void interval_action::on_startup(void)
{
}

void interval_action::on_update(float)
{
}

void interval_action::on_shutdown(void)
{
}

void interval_action::startup(void)
{
  _elapsed = 0.0f;
  on_startup();
}

void interval_action::update(float dt)
{
  _elapsed += dt;

  float interval = _elapsed / _total_time;
  if (interval < 1.0f)
    on_update(interval);
  else
    set_finished();
}

void interval_action::shutdown(void)
{
  on_shutdown();
}

float interval_action::get_total_time(void) const
{
  return _total_time;
}

float interval_action::get_elapsed_time(void) const
{
  return _elapsed;
}
