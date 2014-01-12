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

#include "ns3/simple-controller.h"
/*
#include "ns3/rule.h"
#include "ns3/action.h"
#include "ns3/condition.h"
#include "ns3/action-flow.h"
#include "ns3/action-move.h"
#include "ns3/condition-time.h"
*/
#include "ns3/sd-manet-module.h"
#include "ns3/node.h"
#include "ns3/ptr.h"

namespace ns3{

  namespace sdmanet{

    NS_LOG_COMPONENT_DEFINE("SimpleController");

    void
    SimpleController::receiveFromAgent(Ptr<sdmanet::Agent> agent)
    {
      //todo
    }

    void
    SimpleController::initRules(Ptr<sdmanet::Agent> agent)
    {
      if(m_agents.find(agent) == m_agents.end())
        {
          NS_LOG_INFO("This agent is not registered!");
          return;
        }

      Ptr<Node> node = agent->getNode();
      //NS_LOG_DEBUG("This is node " << node->GetId());
      uint32_t nodeId = node->GetId();
      switch(nodeId)
        {
        case 0:
          break;
        case 1:
          break;
        case 2:
          {
            std::string rules[][6]= {
              {"Ctime", "1.0", "Aflow", "10.1.1.1", "10.1.1.2"},
              {"CGEO", "90","0", "Aflow", "10.1.1.1", "10.1.1.1"}
            };
            installRules(agent, rules, 2);
          }
          break;
        default:
          NS_LOG_INFO("no rules for this node.");
          break;
        }
    }

    void
    SimpleController::installRules(Ptr<sdmanet::Agent> agent, std::string rules[][6], uint32_t size)
    {
      uint32_t i,j;
      Ptr<Node> node = agent->getNode();

      for(i=0; i<size; i++)
        {
          Rule * rule = new Rule();
          Condition* con;
          Action* act;

          j = 0;
          while(j<6){

            if(rules[i][j] == "Ctime")
              {
                uint32_t uTime = atoi(rules[i][j+1].c_str());
                con = new TimeCondition(Seconds(uTime));
                NS_LOG_DEBUG("new time condition");
                //todo init
                j = 2;
              }
            else if(rules[i][j] == "Cflow")
              {
                con = new FlowCondition( node, Mac48Address(rules[i][j+1].c_str()));
                //todo
                NS_LOG_DEBUG("new flow condition");
                j = 2;
              }
            else if(rules[i][j] == "CGEO")
              {
                double x = atoi(rules[i][j+1].c_str());
                double y = atoi(rules[i][j+2].c_str());
                con = new GeoCondition(x, y, node);
                //todo
                NS_LOG_DEBUG("new geo condition");
                j = 3;
              }
            else if (rules[i][j] == "Aflow")
              {
                act = new FlowAction(node, Ipv4Address(rules[i][j+1].c_str()), Ipv4Address(rules[i][j+2].c_str()));
                //todo
                NS_LOG_DEBUG("new flow action");
                j = 6;
              }
            else if (rules[i][j] == "Amove")
              {
                double x = atoi(rules[i][j+1].c_str());
                double y = atoi(rules[i][j+2].c_str());
                act = new MoveAction(node, x, y);
                //todo
                NS_LOG_DEBUG("new move action");
                j = 6;
              }
            else
              {
                NS_LOG_DEBUG("no match action or condition:" << "i is " << i <<"; j is " << j <<" rules is " << rules[i][j]);
                return;
              }
          }//end while

          rule->addpreCondition(con);
          rule->addAction(act);
          agent->installRule(rule);
        }// end for
    }

    } //end naspace sdmanet
}// end namespace ns3
