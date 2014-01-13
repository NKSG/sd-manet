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

#include "ns3/condition-time.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

NS_LOG_COMPONENT_DEFINE ("TimeConditionModel");

namespace ns3{

  TimeCondition::TimeCondition()
  {
    NS_LOG_FUNCTION (this);
  }

  TimeCondition::~TimeCondition()
  {
    NS_LOG_FUNCTION (this);
  }

  TimeCondition::TimeCondition(Time t)
  {
    m_conTime = Simulator::Now() + t;
  }


  bool
  TimeCondition::check()
  {
    NS_LOG_FUNCTION(this);

    if(m_conTime < Simulator::Now())
      {
        NS_LOG_DEBUG("Time is up!");
        return true;
      }
    else
      return false;
  }

  void
  TimeCondition::setTimeAfter(Time t)
  {
    m_conTime = Simulator::Now() + t;

  }


}//namespace ns3
