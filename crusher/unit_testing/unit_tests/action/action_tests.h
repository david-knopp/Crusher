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
#include "crusher/action/action_list.h"
#include <string>

/* helper action for testing */
class test_action : public crusher::action
{
  public:
    test_action(int action_num, int update_count, bool blocking = false)
      : crusher::action(blocking)
      , _action_num(action_num)
      , _count(update_count)
    {
    }

    void update(float) override 
    {
      update_order.append("update" + std::to_string(_action_num));
      --_count;
      if (_count <= 0)
        set_finished();
    }

    void startup(void) override 
    {
      update_order.append("startup" + std::to_string(_action_num));
    }

    void shutdown(void) override 
    {
      update_order.append("shutdown" + std::to_string(_action_num));
    }

    // properties
    static std::string update_order;
    int _action_num;
    int _count;
};

std::string test_action::update_order;

TEST_CASE("action tests", "action tests")
{
  SECTION("action methods", "")
  {
    // nonblocking
    test_action t0(0, 0);
    REQUIRE(t0.is_blocking() == false);
    REQUIRE(t0.is_started() == false);
    REQUIRE(t0.is_finished() == false);
    REQUIRE(t0.is_paused() == false);

    // blocking
    test_action t1(0, 0, true);
    REQUIRE(t1.is_blocking() == true);
  }

  SECTION("adding / removing", "")
  {
    crusher::action_list actions;
    REQUIRE(actions.empty() == true);
    REQUIRE(actions.lane_empty(5) == true);

    actions.push_back(new test_action(0, 0), 5);
    REQUIRE(actions.empty() == false);
    REQUIRE(actions.lane_empty(5) == false);

    actions.clear();
    REQUIRE(actions.empty() == true);
    REQUIRE(actions.lane_empty(5) == true);
  }

  SECTION("update order")
  {
    crusher::action_list actions;
    actions.push_back(new test_action(0, 1));
    actions.update(0.0f);
    REQUIRE(test_action::update_order == "startup0update0shutdown0");
    REQUIRE(actions.empty() == true);

    // blocking test
    test_action::update_order.clear();
    actions.push_back(new test_action(0, 2, true));
    actions.push_back(new test_action(1, 1));
    actions.update(0.0f);
    actions.update(0.0f);
    REQUIRE(test_action::update_order == 
            "startup0update0update0shutdown0startup1update1shutdown1");
    REQUIRE(actions.empty() == true);

    // front / back test
    test_action::update_order.clear();
    actions.push_back(new test_action(0, 1, true));
    actions.push_front(new test_action(1, 2));
    actions.update(0.0f);
    actions.update(0.0f);
    REQUIRE(test_action::update_order == 
            "startup1update1startup0update0shutdown0update1shutdown1");
    REQUIRE(actions.empty() == true);

    // paused test
    test_action::update_order.clear();
    crusher::action* pause = new test_action(0, 1);
    pause->pause();
    actions.push_back(pause);
    crusher::action* pause2 = new test_action(1, 1);
    actions.push_back(pause2);
    actions.update(0.0f);
    REQUIRE(test_action::update_order == 
            "startup1update1shutdown1");
    REQUIRE(actions.empty() == false);
    actions.clear();
    REQUIRE(actions.empty() == true);

    // lane test
    test_action::update_order.clear();
    actions.push_back(new test_action(0, 2, true), 1);
    actions.push_back(new test_action(1, 2, true), 15);
    actions.update(0.0f);
    actions.update(0.0f);
    REQUIRE(test_action::update_order == 
            "startup0update0startup1update1update0shutdown0update1shutdown1");
    REQUIRE(actions.empty() == true);
  }

  SECTION("composite pattern test", "")
  {
    // simple
    test_action::update_order.clear();
    crusher::action_list* comp0 = new crusher::action_list;
    crusher::action_list actions;
    comp0->push_back(new test_action(0, 1));
    actions.push_back(comp0);
    actions.update(0.0f);
    REQUIRE(test_action::update_order == "startup0update0shutdown0");
    REQUIRE(actions.empty() == true);

    // paused
    test_action::update_order.clear();
    crusher::action_list* comp1 = new crusher::action_list;
    comp1->push_back(new test_action(0, 1));
    comp1->pause();
    actions.push_back(comp1);
    actions.update(0.0f);
    REQUIRE(test_action::update_order == "");
    REQUIRE(actions.empty() == false);
    actions.clear();
    REQUIRE(actions.empty() == true);
  }
}