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

#ifndef SD_MANET_AGENT_H
#define SD_MANET_AGENT_H

#include <list>

#include "ns3/rule.h"
#include "ns3/action.h"
#include "ns3/condition.h"
#include "ns3/object.h"
#include "ns3/controller.h"
#include "ns3/ptr.h"

namespace ns3{

  namespace sdmanet{

    class Controller;
    //Type define for rules list
    typedef std::list<Rule *> RULELIST;

    class Agent : public Object
    {
    public:

      Agent();
      virtual ~Agent();
      void loop();

      void setController(Ptr<sdmanet::Controller> c);
      /**
       * \brief install a rule to the rules list.
       * \param rule Rule to installed.
       * \return void
       */
      void installRule(Rule* rule);
      void setNode(Ptr<Node> node);
      Ptr<Node> getNode();

    private:
      RULELIST m_installedRules; //Rules list installed in the agent.
      RULELIST m_exeRules;       //Rules list needed to execute all the time.
      RULELIST m_completeRules;  //Rules list had completed.

      RULELIST::iterator rule;

      Ptr<sdmanet::Controller> m_controller; //The controller node connected.
      Ptr<Node> m_node; //The node agent application installed.

      /**
       * \brief Check the condition of the rules installed in rules list one by one.
       */
      void checkInstalledRules();

      /**
       * \brief Execute the rules need to execute all the time utill some condition triggered.
       *
       */
      void doExeRule();
    };

  }
}//namespace ns3

#endif /* SDMANET_AGENT_H */
