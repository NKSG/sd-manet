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

#include "ns3/action-flow.h"
#include "ns3/log.h"

NS_LOG_COMPONENT_DEFINE ("FlowActionModel");

namespace ns3{

  FlowAction::FlowAction()
  {
    NS_LOG_FUNCTION (this);
  }

  FlowAction::FlowAction(Ptr<Node> node, Ipv4Address target, Ipv4Address nexthop)
    :
    Action(node),
    m_target(target),
    m_nexthop(nexthop)
  {
    NS_LOG_FUNCTION(this);
  }

  FlowAction::~FlowAction()
  {
    NS_LOG_FUNCTION (this);
  }

  bool
  FlowAction::execute()
  {
    NS_LOG_DEBUG("flow action execute");
    Ipv4StaticRoutingHelper staticRoutingHelper;
    Ptr<Ipv4> ipv4 = m_node->GetObject<Ipv4>();
    Ptr<Ipv4StaticRouting> staticRouting = staticRoutingHelper.GetStaticRouting(ipv4);
    staticRouting->AddHostRouteTo(m_target, m_nexthop, 1);
    return true;
  }


}//namespace ns3
