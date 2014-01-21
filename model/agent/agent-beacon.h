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

#ifndef SDMANET_AGENT_BEACON_H
#define SDMANET_AGENT_BEACON_H

#include "ns3/object.h"
#include "ns3/packet.h"
#include "ns3/mgt-headers.h"     //from wifi module
#include "ns3/wifi-mac-header.h"

namespace ns3{
  /**
   * \brief Agent beacon
   * It is used to discover neighbor nodes.
   */

  class AgentBeacon{
  public:
    /**
     * C-tor
     *
     * \param ssid is SSID for beacon header
     * \param rates is a set of supported rates
     * \param us beacon interval in microseconds
     */
    AgentBeacon(Ssid ssid, SupportedRates rates, uint64_t us);
    //Get standard wifi beacon header
    MgtBeaconHeader BeaconHeader () const { return m_header;}
    /**
     * \brief create wifi header for beacon frame.
     *
     * \param address is sender address
     * \param adAddress is adhoc point address
     * \return Wifi mac header
     */
    WifiMacHeader CreateHeader (Mac48Address address, Mac48Address adAddress);
    //return a beacon interval of wifi beacon
    Time GetBeaconInterval () const;
    //create beacon frame
    Ptr<Packet> CreatePacket ();

  private:
    //Beacon header
    MgtBeaconHeader m_header;

  };
}//namespace ns3

#endif
