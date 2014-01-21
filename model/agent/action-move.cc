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

#include "ns3/action-move.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/mobility-model.h"
#include <vector>

NS_LOG_COMPONENT_DEFINE ("MoveActionModel");

namespace ns3{

  MoveAction::MoveAction()
  {
    NS_LOG_FUNCTION (this);
  }

  MoveAction::MoveAction(Ptr<Node> node, double x, double y)
    :
    Action(node)
  {
    m_targetPos.x = x;
    m_targetPos.y = y;
    NS_LOG_FUNCTION(this);
  }
  MoveAction::~MoveAction()
  {
    NS_LOG_FUNCTION (this);
  }


  bool
  MoveAction::execute()
  {
    NS_LOG_DEBUG("move action execute");
    Ptr<MobilityModel> mobility = m_node->GetObject<MobilityModel>();
    Vector pos = mobility->GetPosition();
    delta_x = (m_targetPos.x - pos.x)/MOVE_TIMES;
    delta_y = (m_targetPos.y - pos.y)/MOVE_TIMES;

    advancePosition();

    return true;
  }

  void
  MoveAction::advancePosition()
  {
    Ptr<MobilityModel> mobility = m_node->GetObject<MobilityModel>();
    Vector pos = mobility->GetPosition();

    if(pos.x == m_targetPos.x && pos.y == m_targetPos.y)
      return;
    pos.x += delta_x;
    pos.y += delta_y;

    mobility->SetPosition(pos);
    Simulator::Schedule(Seconds(MOVE_INTERVAL_TIME), &MoveAction::advancePosition, this);
  }


}//namespace ns3
