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

#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include "ns3/action.h"
#include "ns3/ptr.h"
#include "ns3/node.h"
#include "ns3/condition-geo.h"

namespace ns3{

#define MOVE_TIMES 10
#define MOVE_INTERVAL_TIME 1.0

  class MoveAction : public Action
  {
  public:
    MoveAction();

    MoveAction(Ptr<Node> node, double x, double y);
    virtual ~MoveAction();

    bool execute();

  private:
    void advancePosition();
    geo_position m_targetPos;
    double delta_x;
    double delta_y;

  };

}// namespace ns3

#endif /* MOVE_ACTION_H */
