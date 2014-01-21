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

#include "ns3/controller.h"

namespace ns3{

  namespace sdmanet{
    NS_LOG_COMPONENT_DEFINE("Controller");

    void
    Controller::addAgent(Ptr<sdmanet::Agent> agent)
    {
      if(m_agents.find(agent) != m_agents.end())
        {
          NS_LOG_INFO("This controller has already registered this node agent!");
        }
      else
        {
          m_agents.insert(agent);
        }
    }
  }
}
