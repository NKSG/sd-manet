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
    typedef std::list<Rule *> RULELIST;

    class Agent : public Object
    {
    public:

      Agent();
      virtual ~Agent();
      void loop();

      void setController(Ptr<sdmanet::Controller> c);
      void installRule(Rule* rule);
      void setNode(Ptr<Node> node);
      Ptr<Node> getNode();

    private:
      RULELIST m_installedRules;
      RULELIST m_exeRules;
      RULELIST m_completeRules;

      RULELIST::iterator rule;

      Ptr<sdmanet::Controller> m_controller;
      Ptr<Node> m_node;

      void checkInstalledRules();
      void doExeRule();
    };

  }
}//namespace ns3

#endif /* SDMANET_AGENT_H */
