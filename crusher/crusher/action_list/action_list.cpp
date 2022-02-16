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
#include "action_list.h"

using namespace crusher;

action_list::action_list(void)
  : _size(0)
{
}

action_list::~action_list(void)
{
  clear();
}

void action_list::update(float dt)
{
  if (is_paused())
    return;

  // update all action lanes
  for (auto& lane_pair : _lanes)
  {
    // update actions until blocking action
    action_container& lane = lane_pair.second;
    for (auto it = lane.begin(); it != lane.end();)
    {
      action* cur_action = *it;

      // don't update if paused
      if (!cur_action->is_paused())
      {
        // start if hasn't started
        if (!cur_action->is_started())
        {
          cur_action->_started = true;
          cur_action->startup();
        }

        cur_action->update(dt);

        // remove if finished
        if (cur_action->is_finished())
        {
          cur_action->shutdown();
          delete cur_action;
          it = lane.erase(it);
          --_size;
          continue;
        }
      }

      // remaining actions blocked
      if (cur_action->is_blocking())
        break;

      ++it;
    }
  }

  // finish if empty
  if (empty())
    set_finished();
}

void action_list::push_back(action* back, lane_id id)
{
  _lanes[id].push_back(back);
  ++_size;
}

void action_list::push_front(action* front, lane_id id)
{
  _lanes[id].push_front(front);
  ++_size;
}

void action_list::clear(void)
{
  // delete all actions
  for (auto& lane : _lanes)
  {
    // delete all actions in lane
    for (action* action : lane.second)
      delete action;
  }

  _lanes.clear();
  _size = 0;
}

void action_list::clear_lane(lane_id clear_id)
{
  auto lane = _lanes.find(clear_id);
  if (lane != _lanes.end())
  {
    // delete all actions in lane
    action_container& clear_lane = lane->second;
    for (action* action : clear_lane)
      delete action;

    clear_lane.clear();
  }
}

bool action_list::empty(void) const
{
  return (_size == 0);
}

bool action_list::lane_empty(lane_id id) const
{
  auto lane = _lanes.find(id);
  if (lane == _lanes.end())
    return true;
  
  return lane->second.empty();
}
