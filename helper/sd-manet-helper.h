/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
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
 * Author: Haidong Zhang <zhanghaidong@nudt.edu.cn>
 */

#ifndef SD_MANET_HELPER_H
#define SD_MANET_HELPER_H

#include "ns3/sd-manet.h"
#include <stdint.h>
#include <string>
#include "ns3/object-factory.h"
#include "ns3/node-container.h"
#include "ns3/application-container.h"
#include "ns3/node.h"
#include "ns3/ptr.h"
#include "ns3/controller.h"

namespace ns3 {

  /**
   * \brief A helper to make it easier to instantiate an ns3::SdManet 
   * application on a set of nodes.
   */
  class SdManetHelper
  {
  public:
    /**
     * Create an SdManetHelper to make it easier to work with SdManet
     *
     */
    SdManetHelper ();


    /**
     * Install an ns3::SdManet on each node of the input container
     * configured with all the attributes set with SetAttribute.
     *
     * \param c NodeContainer of the set of nodes on which an SdManet application
     * will be installed.
     * \param controller The controller all the nodes connected.
     * \returns Container of Ptr to the applications installed.
     */
    ApplicationContainer Install (NodeContainer c, Ptr<ns3::sdmanet::Controller> controller);

    /**
     * Install an ns3::SdManet on the node configured with all the
     * attributes set with SetAttribute.
     *
     * \param node The node on which an SdManet will be installed.
     * \param controller The controller all the nodes connected.
     * \returns Container of Ptr to the applications installed.
     */
    ApplicationContainer Install (Ptr<Node> node, Ptr<ns3::sdmanet::Controller> controller);

    /**
     * Install an ns3::SdManet on the node configured with all the
     * attributes set with SetAttribute.
     *
     * \param nodeName The node on which an SdManet will be installed.
     * \param controller The controller all the nodes connected.
     * \returns Container of Ptr to the applications installed.
     */
    ApplicationContainer Install (std::string nodeName, Ptr<ns3::sdmanet::Controller> controller);


  private:
    /**
     * \internal
     * Install an ns3::SdManet on the node configured with all the
     * attributes set with SetAttribute.
     *
     * \param node The node on which an SdManet will be installed.
     * \param controller The controller all the nodes connected.
     * \returns Ptr to the application installed.
     */
    Ptr<Application> InstallPriv (Ptr<Node> node, Ptr<ns3::sdmanet::Controller> controller);
    ObjectFactory m_factory;
  };

}

#endif /* SD_MANET_HELPER_H */

