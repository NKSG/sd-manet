/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
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
 * Author: Haidong Zhang <zhanghaidong@nudt.edu.cn>
 */

#include "ns3/sd-manet-helper.h"
#include "ns3/uinteger.h"
#include "ns3/names.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "ns3/string.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"

NS_LOG_COMPONENT_DEFINE("SdManetHelper");

namespace ns3 {

SdManetHelper::SdManetHelper ()
{
  m_factory.SetTypeId ("ns3::sd-manet");

}

ApplicationContainer
SdManetHelper::Install (Ptr<Node> node, Ptr<ns3::sdmanet::Controller> controller) 
{
  return ApplicationContainer (InstallPriv (node, controller));
}

ApplicationContainer
SdManetHelper::Install (std::string nodeName, Ptr<ns3::sdmanet::Controller> controller)
{
  Ptr<Node> node = Names::Find<Node> (nodeName);
  return ApplicationContainer (InstallPriv (node, controller));
}

ApplicationContainer
SdManetHelper::Install (NodeContainer c, Ptr<ns3::sdmanet::Controller> controller) 
{
  ApplicationContainer apps;
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      apps.Add (InstallPriv (*i, controller));
      NS_LOG_DEBUG("app is installed in node ");
    }

  return apps;
}


Ptr<Application>
SdManetHelper::InstallPriv (Ptr<Node> node, Ptr<ns3::sdmanet::Controller> controller) 
{
  //create agent and set the controller.
  Ptr<sdmanet::Agent> agent = CreateObject<sdmanet::Agent>();
  agent->setController(controller);
  agent->setNode(node);
  controller->addAgent(agent);
  controller->initRules(agent);
  m_factory.Set("Agent", PointerValue(agent));

  Ptr<Application> app = m_factory.Create<Application> ();
  node->AddApplication (app);
  return app;
}


}

