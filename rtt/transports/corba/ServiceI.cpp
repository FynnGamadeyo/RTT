/***************************************************************************
  tag: The SourceWorks  Tue Sep 7 00:55:18 CEST 2010  ServiceI.cpp

                        ServiceI.cpp -  description
                           -------------------
    begin                : Tue September 07 2010
    copyright            : (C) 2010 The SourceWorks
    email                : peter@thesourceworks.com

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU General Public                   *
 *   License as published by the Free Software Foundation;                 *
 *   version 2 of the License.                                             *
 *                                                                         *
 *   As a special exception, you may use this file as part of a free       *
 *   software library without restriction.  Specifically, if other files   *
 *   instantiate templates or use macros or inline functions from this     *
 *   file, or you compile this file and link it with other files to        *
 *   produce an executable, this file does not by itself cause the         *
 *   resulting executable to be covered by the GNU General Public          *
 *   License.  This exception does not however invalidate any other        *
 *   reasons why the executable file might be covered by the GNU General   *
 *   Public License.                                                       *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public             *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/


// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from 
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1196

#include "ServiceI.h"

using namespace RTT;
using namespace RTT::detail;

// Implementation skeleton constructor
RTT_corba_CService_i::RTT_corba_CService_i ( RTT::Service::shared_ptr service, PortableServer::POA_ptr poa)
    : RTT_corba_CConfigurationInterface_i( service.get(), PortableServer::POA::_duplicate( poa) ), 
      RTT_corba_COperationInterface_i( service.get(), PortableServer::POA::_duplicate( poa) ),
      RTT::corba::CDataFlowInterface_i( service.get(), PortableServer::POA::_duplicate( poa) ),
      mpoa(poa), mservice(service)
{
}

// Implementation skeleton destructor
RTT_corba_CService_i::~RTT_corba_CService_i (void)
{
}

PortableServer::POA_ptr RTT_corba_CService_i::_default_POA()
{
    return PortableServer::POA::_duplicate(mpoa);
}

char * RTT_corba_CService_i::getName (
    void)
{
    return CORBA::string_dup( mservice->getName().c_str() );
}

char * RTT_corba_CService_i::getServiceDescription (
    void)
{
    return CORBA::string_dup( mservice->doc().c_str() );
}

::RTT::corba::CService::CProviderNames * RTT_corba_CService_i::getProviderNames (
    void)
{
    Service::ProviderNames names = mservice->getProviderNames();
    ::RTT::corba::CService::CProviderNames_var result = new ::RTT::corba::CService::CProviderNames();
    result->length( names.size() );
    for (unsigned int i=0; i != names.size(); ++i )
        result[i] = CORBA::string_dup( names[i].c_str() );

    return result._retn();
}

::RTT::corba::CService_ptr RTT_corba_CService_i::getService (
    const char * service_name)
{
    Service::shared_ptr provider = mservice->getService(service_name);
    if ( !provider )
    	return RTT::corba::CService::_nil();

    // check for existing service
    for(Servants::iterator it = mservs.begin(); it != mservs.end(); ++it) {
    	CORBA::String_var sname = it->first->getName();
    	if ( sname.in() == service_name )
    		return  RTT::corba::CService::_duplicate( it->first.in() );
    }
    // not found: new service
    
    RTT_corba_CService_i* serv_i;
    RTT::corba::CService_var serv;
    serv_i = new RTT_corba_CService_i( provider, mpoa );
    serv = serv_i->activate_this();
    mservs.push_back( std::pair<RTT::corba::CService_var,PortableServer::ServantBase_var>( RTT::corba::CService::_duplicate(serv.in()), serv_i ) );
    //CService_i::registerServant(serv, mtask->provides(service_name));
    return RTT::corba::CService::_duplicate( serv.in() );
}

::CORBA::Boolean RTT_corba_CService_i::hasService (
    const char * name)
{
    return mservice->hasService( name );
}
