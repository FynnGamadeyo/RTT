/***************************************************************************
  tag: Bernd Langpap  Wed Jan 18 14:09:48 CET 2006  INamingService.hpp

                        TaskContextServerFactory.hpp -  description
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
#ifndef REMOTE_FACTORY_HPP
#define REMOTE_FACTORY_HPP

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/atomic.hpp>
#include <boost/thread/mutex.hpp>
// #include "RemoteDefinitions.h"
#include "ITypeGenerator.hpp"
#include <rtt/TaskContext.hpp>


namespace RTT
{
namespace Communication
{
/**
  * @brief This class represents a factory, which has the means to create different kind of task context server.
  *
  */
class Factory
{
private:
    std::map<std::string, ITypeGenerator::shared_ptr> m_RegisteredTCSGenerators;

    // Ctor / Dtor
    Factory();
    ~Factory();
    static boost::atomic<Factory *> m_Instance;
    static boost::mutex m_InstantiationMutex;
public:
    static Factory *GetInstance() {
        Factory *tmp = Factory::m_Instance.load(boost::memory_order_consume);
        if (!tmp) {
            boost::mutex::scoped_lock guard(Factory::m_InstantiationMutex);
            tmp = Factory::m_Instance.load(boost::memory_order_consume);
            if (!tmp) {
                tmp = new Factory();
                Factory::m_Instance.store(tmp, boost::memory_order_release);
            }
        }
        return tmp;
    };
    
    // Registration Methods
    bool RegisterTaskContextServerGenerator(std::string NameID, ITypeGenerator::shared_ptr pTCSGenerator);
    bool DeleteTaskContextServerGenerator(std::string NameID);

    // Factory method
    template<class ProductionType>
    boost::shared_ptr<ProductionType> CreateTaskContextServer(std::string NameID, TaskContext *pTaskContext, int argc, char* argv[]);

    template<class ProductionType>
    boost::shared_ptr<ProductionType> getTaskContextServer(std::string NameID);

};
}
}

#endif // REMOTE_TASKCONTEXTSERVERFACTORY_HPP
