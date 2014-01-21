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

#ifndef SD_MANET_CONTROLLER_H
#define SD_MANET_CONTROLLER_H

#include "ns3/agent.h"
#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/object.h"
#include <set>

namespace ns3{

  namespace sdmanet{
    class Agent;
    class Controller : public Object
    {
    public:
      static TypeId GetTypeId(void)
      {
        static TypeId tid = TypeId("ns3::sdmanet::Controller")
          .SetParent<Object> ()
          .AddConstructor<Controller>()
          ;
        return tid;
      }

      virtual ~Controller()
      {
        m_agents.clear();
      }

      void addAgent(Ptr<sdmanet::Agent> agent);
      virtual void receiveFromAgent(Ptr<sdmanet::Agent> agent){}
      virtual void initRules(Ptr<sdmanet::Agent>){}

    protected:
      virtual void initRules(){}
      virtual void buildRules(){}
      virtual void installRules(Ptr<sdmanet::Agent> agent){}
      virtual void installRulesAll(){}

      typedef std::set< Ptr<sdmanet::Agent> > Agents_t;
      Agents_t m_agents;
    };

  }
}

#endif /* SD_MANET_CONTROLLER_H */
