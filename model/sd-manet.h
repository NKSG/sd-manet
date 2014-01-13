/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
//
// Copyright (c) 2006 Georgia Tech Research Corporation
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation;
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Author: Haidong Zhang <zhanghaidong@nudt.edu.cn>
//
// ns3 - mission orient mobile wireless communication Application class
// NUDT @ 2013
//

#ifndef SD_MANET_H
#define SD_MANET_H

#include "ns3/application.h"
#include "ns3/ptr.h"
#include "ns3/event-id.h"
#include "ns3/agent.h"

namespace ns3 {
#define LOOP_INTERVAL  1.0

/**
 * \ingroup applications
 * \defgroup SdManet SdManet Application
 */
/**
* \ingroup onoff
*
* \brief Create SdManet agent on the node and execute the rules
* installed in nodes.
*/

class SdManet : public Application
{
public:
  static TypeId GetTypeId (void);

  SdManet ();

  virtual ~SdManet();

private:
  // inherited from Application base class.
  virtual void StartApplication (void);    // Called at time specified by Start
  virtual void StopApplication (void);     // Called at time specified by Stop

  Ptr<sdmanet::Agent> m_agent;  //The agent application installed in node.
  EventId  m_startStopEvent;


  void ScheduleStartLoop();
  void ScheduleStopLoop();
};

} // namespace ns3

#endif /* SD_MANET_H */

