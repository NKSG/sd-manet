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

#ifndef GEO_CONDITION_H
#define GEO_CONDITION_H

#include "ns3/condition.h"
#include "ns3/node.h"
#include "ns3/ptr.h"

namespace ns3{

struct geo_position{
    double x;
    double y;
};

class GeoCondition : public Condition
{
    public:
        GeoCondition();
  GeoCondition(double x, double y, Ptr<Node> node);
        virtual ~GeoCondition();

        bool check();



    private:
  geo_position getCurPos();

        double m_delta;
        geo_position m_pos;

};

}// namespace ns3

#endif /* GEO_CONDITION_H */
