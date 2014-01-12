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

#ifndef FLOW_ACTION_H
#define FLOW_ACTION_H

#include "ns3/action.h"
#include "ns3/ptr.h"
#include "ns3/node.h"
#include "ns3/internet-module.h"

namespace ns3{

class FlowAction : public Action
{
    public:
        FlowAction();
  FlowAction(Ptr<Node> node, Ipv4Address target, Ipv4Address nexthop);
  virtual ~FlowAction();
        bool execute();

    private:

  Ipv4Address m_target;
  Ipv4Address m_nexthop;
};

}// namespace ns3

#endif /* FLOW_ACTION_H */
