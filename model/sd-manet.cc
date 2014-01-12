/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
//
// Copyright (c) 2013
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

#include "sd-manet.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "ns3/simulator.h"

NS_LOG_COMPONENT_DEFINE ("SdManet");

namespace ns3 {

  NS_OBJECT_ENSURE_REGISTERED (SdManet);

  TypeId
  SdManet::GetTypeId (void)
  {
    static TypeId tid = TypeId ("ns3::sd-manet")
      .SetParent<Application> ()
      .AddConstructor<SdManet> ()
      .AddAttribute("Agent", "the agent node associated",
                    PointerValue(),
                    MakePointerAccessor(&SdManet::m_agent),
                    MakePointerChecker<sdmanet::Agent>())
      ;
    return tid;
  }


  SdManet::SdManet ()
  {
    NS_LOG_FUNCTION (this);
    m_agent = NULL;
  }

  SdManet::~SdManet()
  {
    NS_LOG_FUNCTION (this);
  }


  // Application Methods
  void SdManet::StartApplication () // Called at time specified by Start
  {
    NS_LOG_FUNCTION (this);
    NS_LOG_DEBUG("Start.....");

    ScheduleStartLoop();

  }

  void SdManet::StopApplication () // Called at time specified by Stop
  {
    NS_LOG_FUNCTION (this);

    NS_LOG_DEBUG("Stoping.....");

    ScheduleStopLoop();

  }

  void SdManet::ScheduleStartLoop()
  {
    NS_LOG_FUNCTION(this);

    if (m_agent != NULL )
      {
        m_agent->loop();
      }

    NS_LOG_DEBUG("start a loop...");
    m_startStopEvent = Simulator::Schedule(Seconds(LOOP_INTERVAL), &SdManet::ScheduleStartLoop, this);
  }

  void SdManet::ScheduleStopLoop()
  {
    NS_LOG_FUNCTION(this);

    Simulator::Cancel(m_startStopEvent);
  }


}

