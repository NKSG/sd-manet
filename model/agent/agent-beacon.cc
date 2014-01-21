/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 NUDT
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

#include "ns3/agent-beacon.h"


namespace ns3 {

  AgentBeacon::AgentBeacon (Ssid ssid, SupportedRates rates, uint64_t us)
  {
    m_header.SetSsid (ssid);
    m_header.SetSupportedRates (rates);
    m_header.SetBeaconIntervalUs (us);
  }

  Time
  AgentBeacon::GetBeaconInterval () const
  {
    return MicroSeconds (m_header.GetBeaconIntervalUs ());
  }

  Ptr<Packet>
  AgentBeacon::CreatePacket ()
  {
    Ptr<Packet> packet = Create <Packet> ();
    packet->AddHeader (BeaconHeader ());
    return packet;
  }
  WifiMacHeader
  AgentBeacon::CreateHeader (Mac48Address address, Mac48Address adAddress)
  {
    WifiMacHeader hdr;

    hdr.SetBeacon ();
    hdr.SetAddr1 (Mac48Address::GetBroadcast ());
    hdr.SetAddr2 (address);
    hdr.SetAddr3 (adAddress);
    hdr.SetDsNotFrom ();
    hdr.SetDsNotTo ();

    return hdr;
  }
} // namespace ns3
