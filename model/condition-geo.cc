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

#include "ns3/condition-geo.h"
#include "ns3/log.h"
#include "ns3/mobility-model.h"

#include <cmath>
#include <vector>


NS_LOG_COMPONENT_DEFINE ("GEOConditionModel");

namespace ns3{

GeoCondition::GeoCondition()
{
    NS_LOG_FUNCTION (this);
}

GeoCondition::GeoCondition(double x, double y, Ptr<Node> node)
  :Condition(node),
    m_delta(1.0)
{
  m_pos.x = x;
  m_pos.y = y;
  NS_LOG_FUNCTION(this);
}

GeoCondition::~GeoCondition()
{
    NS_LOG_FUNCTION (this);
}

/** \brief Check the postion. get the node current position and check if match the condition.
 *         Note that, delta is used to define the match range.
 * \return if current postion is in the range of target's return true, else false.
 *
 */

bool 
GeoCondition::check()
{
    geo_position curPos = getCurPos();
    NS_LOG_DEBUG("current geo is ["<<curPos.x<<" , " << curPos.y << "]");

    if ( fabs(m_pos.x - curPos.x) < m_delta &&  fabs(m_pos.y - curPos.y) < m_delta  )
         return true;
    return false;
}

geo_position 
GeoCondition::getCurPos()
{
    geo_position cur;
    Ptr<MobilityModel> mobility = m_node->GetObject<MobilityModel>();
    Vector pos = mobility->GetPosition();

    cur.x = pos.x;
    cur.y = pos.y;

    return cur;
}

}//namespace ns3
