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

#include "ns3/condition-linked.h"
#include "ns3/log.h"
#include "ns3/wifi-net-device.h"


NS_LOG_COMPONENT_DEFINE ("LinkedConditionModel");

namespace ns3{

LinkedCondition::LinkedCondition()
{
    NS_LOG_FUNCTION (this);
}

LinkedCondition::LinkedCondition(Ptr<Node> node,Ipv4Address ip_target)
  :
  Condition(node),
  m_connect(false)
{
  Ptr<NetDevice> dev = node->GetDevice(0);
  Ptr<WifiNetDevice> wifi = dev->GetObject<WifiNetDevice>();
  if(wifi == 0)
    return;
  mac = wifi->GetMac();
  if(mac == 0)
    return;

  NodeContainer c = NodeContainer::GetGlobal();
  
  for (NodeContainer::Iterator iter = c.Begin (); iter != c.End (); ++iter)
  {
    //node1 = *iter;
	//Ipv4InterfaceAddress iaddr = dev->GetAddress();
	Ptr<Ipv4> ipv4 = (*iter)->GetObject<Ipv4>();
    int32_t result = ipv4->GetInterfaceForAddress(ip_target);
	if(result != -1)
	{  
	  dev = (*iter)->GetDevice(0);
	  wifi = dev->GetObject<WifiNetDevice>();
	  if(wifi == 0)
        return;
      Ptr<WifiMac> mac_target = wifi->GetMac();
      if(mac_target == 0)
        return; 
	  mac_target_addr = mac_target->GetAddress();
      break;		
	}
  }
  mac->TraceConnectWithoutContext("TxOkHeader", MakeCallback (&LinkedCondition::ProcessConnect, this));

}

LinkedCondition::~LinkedCondition()
{
    NS_LOG_FUNCTION (this);
}

bool
LinkedCondition::check()
{
    return m_connect;
}


void
LinkedCondition::ProcessConnect(WifiMacHeader const & hdr)
{
  Mac48Address addr = hdr.GetAddr1();
  //NS_LOG_DEBUG("find neighbor mac :" << addr);
  if(mac_target_addr == addr)
  {
    m_connect = true;
	mac->TraceDisconnectWithoutContext("TxErrHeader", MakeCallback (&LinkedCondition::ProcessDisconnect, this));
  }

}

void
LinkedCondition::ProcessDisconnect(WifiMacHeader const & hdr)
{
  Mac48Address addr = hdr.GetAddr1();
  //NS_LOG_DEBUG("find neighbor mac :" << addr);
  if(mac_target_addr == addr)
  {
    m_connect = false;
	mac->TraceConnectWithoutContext("TxOkHeader", MakeCallback (&LinkedCondition::ProcessConnect, this));
  }

}

}//namespace ns3
