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

#include <ns3/rule.h>
#include <ns3/log.h>

NS_LOG_COMPONENT_DEFINE ("RuleModel");


namespace ns3{

Rule::Rule()
{
    NS_LOG_FUNCTION (this);
}

Rule::~Rule()
{
    NS_LOG_FUNCTION (this);
}

bool 
Rule::preMatch(){

    return match(preConditions);
}

void 
Rule::addpreCondition(Condition* c){

	preConditions.push_back(c);
}

void 
Rule::addpostCondition(Condition* c){

    postConditions.push_back(c);
}

void 
Rule::addAction(Action * a){
    action = a;
}

Action* 
Rule::getAction(){
    return action;
}

bool 
Rule::postMatch()
{
    return match(postConditions);
}

bool 
Rule::match(LISTCON conList)
{
	bool res = false;
	if(!conList.empty()){

		/*条件判断，list中条件之间为or关系，条件内部的链表项之间是and关系，只有判断整个条件
		为true时才返回true*/


		for (condition = conList.begin(); condition != conList.end(); ++condition)
		{

			res = true;
			// 单个条件内的链表中如果有一个为false，则此条件的结果为false
			Condition* c = *condition;
			while(c){
				if(!c->check()){
					res = false;
					break;
				}
				c = c->getNext();
			}
			// 如果前面的某个条件判断为真，则所有条件都为真，
			if(res)break;

		}
	}

	return res;
}

}// namespace ns3


