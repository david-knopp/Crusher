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
#include "action.h"

using namespace crusher;

action::action(bool blocking)
  : _blocking(blocking)
  , _started(false)
  , _finished(false)
  , _paused(false)
{
}

action::~action(void)
{
}

void action::pause(void)
{
  _paused = true;
}

void action::resume(void)
{
  _paused = false;
}

void action::set_finished(void)
{
  _finished = true;
}

bool action::is_started(void) const
{
  return _started;
}

bool action::is_paused(void) const
{
  return _paused;
}

bool action::is_finished(void) const
{
  return _finished;
}

bool action::is_blocking(void) const
{
  return _blocking;
}

void action::block(void)
{
  _blocking = true;
}

void action::unblock(void)
{
  _blocking = false;
}

void action::set_blocking(bool blocking)
{
  _blocking = blocking;
}
