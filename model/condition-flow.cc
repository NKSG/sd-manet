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

#include "ns3/condition-flow.h"
#include "ns3/log.h"
#include "ns3/wifi-net-device.h"



NS_LOG_COMPONENT_DEFINE ("FlowConditionModel");

namespace ns3{

FlowCondition::FlowCondition()
{
    NS_LOG_FUNCTION (this);
}

FlowCondition::FlowCondition(Ptr<Node> node, Mac48Address m)
  :
  Condition(node),
  m_connect(false),
  m_mac(m)
{

  Ptr<NetDevice> dev = node->GetDevice(0);
  Ptr<WifiNetDevice> wifi = dev->GetObject<WifiNetDevice>();
  if(wifi == 0)
    return;
  Ptr<WifiMac> mac = wifi->GetMac();
  if(mac == 0)
    return;

  mac->TraceConnectWithoutContext("TxOkHeader", MakeCallback (&FlowCondition::ProcessTxOk, this));

}

FlowCondition::~FlowCondition()
{
    NS_LOG_FUNCTION (this);
}

bool 
FlowCondition::check()
{
    return m_connect;
}


void 
FlowCondition::ProcessTxOk(WifiMacHeader const & hdr)
{
  Mac48Address addr = hdr.GetAddr1();
  //NS_LOG_DEBUG("find neighbor mac :" << addr);
  if(m_mac == addr)
    m_connect = true;
}

}//namespace ns3
