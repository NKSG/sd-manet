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

#include "ns3/agent.h"
#include "ns3/log.h"

NS_LOG_COMPONENT_DEFINE ("Agent");

namespace ns3{

namespace sdmanet{

Agent::Agent()
{
    NS_LOG_FUNCTION (this);
}

Agent::~Agent()
{
    NS_LOG_FUNCTION (this);
}

void
Agent::setController(Ptr<sdmanet::Controller> c)
{
  m_controller = c;
}

void
Agent::setNode(Ptr<Node> node)
{
  m_node = node;
}

Ptr<Node>
Agent::getNode()
{
  return m_node;
}

void
Agent::loop(){

    checkInstalledRules();
    //    doExeRule();
}

void
Agent::installRule(Rule* rule){

	m_installedRules.push_back(rule);
}

void
Agent::checkInstalledRules()
{

  for(rule = m_installedRules.begin(); rule != m_installedRules.end() && !m_installedRules.empty(); ){
    Rule *r = *rule;
    if(r->preMatch()){
      Action * action = r->getAction();
      action->execute();
      m_completeRules.push_back(*rule);
      rule = m_installedRules.erase(rule);
    }
    else{
      ++rule;
    }
  }
}

void
Agent::doExeRule()
  {
    for(rule = m_exeRules.begin(); rule != m_exeRules.end(); ){

      Rule *r = *rule;
      Action * action = r->getAction();
      if(!r->postMatch()){
        action->execute();
        ++rule;
      }
      else{
        m_completeRules.push_back(*rule);
        rule = m_exeRules.erase(rule);
      }

    }
  }

}
}//namespace ns3
