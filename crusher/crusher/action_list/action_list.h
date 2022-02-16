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
#include "action.h"
#include <map>
#include <list>

namespace crusher
{

  /* runs actions in order, stopping at a blocking action */
  class action_list : public action
  {
    public:
      // typedefs
      typedef int lane_id;

      // ctor / dtor
      action_list(void);
      virtual ~action_list(void);

      // public methods
      void update(float dt);
      void push_back(action* back, lane_id id = 0);
      void push_front(action* front, lane_id id = 0);
      void clear(void);
      void clear_lane(lane_id clear_id);

      bool empty(void) const;
      bool lane_empty(lane_id id) const;

    private:
      // private types
      typedef std::list<action*> action_container;
      typedef std::map<lane_id, action_container> lane_map;
      typedef std::pair<lane_id, action_container> lane_pair;

      // private members
      lane_map _lanes;
      int _size;

  }; // class action_list

} // namespace crusher
