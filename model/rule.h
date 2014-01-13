/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 CTTC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Haidong Zhang <heyeast.geek@gmail.com>
 */

#ifndef RULE_H
#define RULE_H

#include "ns3/condition.h"
#include "ns3/action.h"

#include <list>

namespace ns3{

  //Type define for condition list.
  typedef std::list<Condition *> LISTCON;

  class Rule
  {
  public:
    Rule();
    virtual ~Rule();
    /**
     * \brief Match a pre conditions of a rule
     */
    bool preMatch();
    /**
     * \brief Match a post conditions of a rule
     */
    bool postMatch();
    /**
     * \brief add a pre condition to the precondition list.
     */
    void addpreCondition(Condition* c);
    /**
     * \brief add a post condition to the postcondition list.
     */
    void addpostCondition(Condition* c);
    void addAction(Action * a);
    Action* getAction();

  private:
    /**
     * preConditions is set for when the action should be executed.
     */
    LISTCON preConditions;
    /**
     * postConditions is set for when some action should stop execute.
     * some action like move will be executed continuously until some
     * condition is triggered.
     */
    LISTCON postConditions;
    LISTCON::iterator condition;
    Action* action; // The action will be executed.

    /**
     * \internal
     * \brief Match the condition list.
     * \param conList Condition list will be matched.
     * \return TRUE if condition is triggered.FALSE is failed.
     */
    bool match(LISTCON conList);

  };

} // namespace ns3


#endif /* RULE_H */
