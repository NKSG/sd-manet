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

#ifndef RULE_H
#define RULE_H

#include "ns3/condition.h"
#include "ns3/action.h"

#include <list>

namespace ns3{

typedef std::list<Condition *> LISTCON;

class Rule
{
    public:
        Rule();
        virtual ~Rule();
        bool preMatch();
        bool postMatch();
        void addpreCondition(Condition* c);
        void addpostCondition(Condition* c);
        void addAction(Action * a);
        Action* getAction();

    private:
        LISTCON preConditions;
        LISTCON postConditions;
        LISTCON::iterator condition;
        Action* action;

        bool match(LISTCON conList);

};

} //


#endif /* RULE_H */
