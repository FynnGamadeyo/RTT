/***************************************************************************
  tag: Bernd Langpap  Wed Jan 18 14:09:48 CET 2006  INamingService.hpp

                        INameService.hpp -  description
                           -------------------
    begin                : Mon March 17 2015
    copyright            : (C) 2015 Bernd Langpap
    email                : bernd.langpap@dfki.de

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
#ifndef REMOTE_INAMINGSERVICE_HPP
#define REMOTE_INAMINGSERVICE_HPP

#include <string>
#include <rtt/TaskContext.hpp>
#include "TaskContextServerCollection.hpp"


namespace RTT
{namespace Communication
{
    /**
      * @brief This class is an abstract representation of a name service.
      * 
      */
    class INameService
    {
    public:
      // Type Definition of a smart pointer to a name service
      typedef boost::shared_ptr<INameService> shared_ptr;
      
      // Ctor / Dtor
      INameService() {};
      virtual ~INameService() {};
      
      // General Name Service methods
      virtual std::string getURI(std::string Name) = 0;
      virtual bool RegisterTaskContextServer(std::string Name, TaskContextServerCollection& tcsCollection) = 0;   
    };    
}
}

#endif // REMOTE_INAMINGSERVICE_HPP