/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 University of Washington
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
 */

//
// This program configures a linear topology of three nodes on an  802.11g physical layer, 
// with 802.11g NICs in adhoc mode, and by default, sends udp packet stream from node C to node A
//
// The default layout is like this, on a 2-D grid.
//
//  A)))))                 (((((((  C
//                       <-------move
//    
//      ((((( B )))))   
//
//
// Node C moves toward to node A pass by node B, 
// and compare the routing performace between OLSR Routing with Static Routing
//
// There are a number of command-line options available to control
// the default behavior.  The list of available command-line options
// can be listed with the following command:
// ./waf --run "wifi-simple-adhoc-grid --help"
//
// Note that all ns-3 attributes (not just the ones exposed in the below
// script) can be changed at command line; see the ns-3 documentation.
//
// For instance, for this configuration, we can change the routing protocol by attibute verbose
// To run the olsrd routing , try running:
//
// ./waf --run "wifi-simple-adhoc-s1 --verbose=true"
//
// and to run static routing, try running:
// ./waf --run "wifi-simple-adhoc-s1 --verbose=false"


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/sd-manet-helper.h"
#include "ns3/simple-controller.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

NS_LOG_COMPONENT_DEFINE ("SdManetExample");

using namespace ns3;

//log the received packet size in one second
uint32_t m_bytesTotal;
//global attribute to enable static routing, default is olsrd routing

bool verbose = true;

static void ReceivePacket (Ptr<Socket> socket)
{
  //NS_LOG_UNCOND ("Received one packet!");
  Ptr<Packet> packet = socket->Recv();
  m_bytesTotal += packet->GetSize();
}


void
SetPosition (Ptr<Node> node, Vector position)
{

  Ptr<MobilityModel> mobility = node->GetObject<MobilityModel> ();
  mobility->SetPosition (position);
}

Vector
GetPosition (Ptr<Node> node)
{
  Ptr<MobilityModel> mobility = node->GetObject<MobilityModel> ();
  return mobility->GetPosition ();
}

void
AdvancePosition (Ptr<Node> node)
{
  Vector pos = GetPosition (node);
  //  double mbs = ((m_bytesTotal * 8.0) / 1000000);
  m_bytesTotal = 0;

  pos.x -= 1.0;
  if (pos.x <= 10.0)
    {
      return;
    }

  SetPosition (node, pos);
  //  std::cout << pos.x <<"  "<<mbs << std::endl;
  Simulator::Schedule (Seconds (1.0), &AdvancePosition, node);
}


int main (int argc, char *argv[])
{

  uint32_t numNodes = 3;
  bool tracing = true;

  CommandLine cmd;

  cmd.AddValue ("verbose", "turn on all WifiNetDevice log components", verbose);
  cmd.AddValue ("tracing", "turn on ascii and pcap tracing", tracing);

  cmd.Parse (argc, argv);

  //log enable.
  LogComponentEnable ("TimeConditionModel", LOG_LEVEL_DEBUG);
  LogComponentEnable ("FlowConditionModel", LOG_LEVEL_DEBUG);
  LogComponentEnable ("GEOConditionModel", LOG_LEVEL_DEBUG);
  LogComponentEnable ("FlowActionModel", LOG_LEVEL_DEBUG);
  LogComponentEnable ("MoveActionModel", LOG_LEVEL_DEBUG);
  LogComponentEnable ("SimpleController", LOG_LEVEL_DEBUG);
  LogComponentEnable ("SdManetHelper", LOG_LEVEL_DEBUG);

  // disable fragmentation for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("2200"));
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));

  NodeContainer c;
  c.Create (numNodes);

  // The below set of helpers will help us to put together the wifi NICs we want
  WifiHelper wifi;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211g);
  wifi.SetRemoteStationManager ("ns3::ArfWifiManager");

  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");

  wifiPhy.SetChannel (wifiChannel.Create ());

  // Add a non-QoS upper mac, and disable rate control
  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
  wifiMac.SetType ("ns3::AdhocWifiMac");


  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);

  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (0.0, 0.0, 0.0));
  positionAlloc->Add (Vector (50.0, 50.0, 0.0));
  positionAlloc->Add (Vector (220.0, 0.0, 0.0));

  mobility.SetPositionAllocator (positionAlloc);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  mobility.Install (c);


  Ipv4ListRoutingHelper list;
  InternetStackHelper internet;
  Ipv4StaticRoutingHelper staticRouting;

  if(verbose){

    list.Add (staticRouting, 0);
  }
  else{
    // Enable OLSR
    OlsrHelper olsr;
    list.Add (olsr, 10);
  }

  internet.SetRoutingHelper (list); // has effect on the next Install ()
  internet.Install (c);


  Ipv4AddressHelper ipv4;
  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i = ipv4.Assign (devices);

  //setup the static route tables
  if(verbose){
    Ptr<ns3::sdmanet::SimpleController> controller = CreateObject<ns3::sdmanet::SimpleController> ();
    SdManetHelper sdmanet;
    ApplicationContainer sdmanetApp = sdmanet.Install(c, controller);
    sdmanetApp.Start(Seconds(2.0));
    sdmanetApp.Stop(Seconds(200.0));

  }

  // OnOff application. send upd stream from C to A
  uint16_t port = 9;
  OnOffHelper onoff ("ns3::UdpSocketFactory", Address(InetSocketAddress(i.GetAddress(0,0), port)));
  onoff.SetConstantRate (DataRate (30000000));
  onoff.SetAttribute ("PacketSize", UintegerValue (1000));
  onoff.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  onoff.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  ApplicationContainer apps = onoff.Install (c.Get (2));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (500.0));

  //sink the stream and compute the packets received.
  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
  Ptr<Socket> recvSink = Socket::CreateSocket (c.Get (0), tid);
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), port);
  recvSink->Bind (local);
  recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));


  if (tracing == true)
    {
      AsciiTraceHelper ascii;
      wifiPhy.EnableAsciiAll (ascii.CreateFileStream ("wifi-simple-adhoc-grid.tr"));
      wifiPhy.EnablePcap ("wifi-simple-adhoc-s1", devices);
    }

  Simulator::Schedule (Seconds (2.0), &AdvancePosition, c.Get (2));

  Simulator::Stop (Seconds (500.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}




