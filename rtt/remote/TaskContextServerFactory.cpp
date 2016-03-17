#include "TaskContextServerFactory.hpp"
// #include <boost/type_traits/is_base_of.hpp>
// #include <boost/static_assert.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
// #include <typeinfo>
#include "ITypeGenerator.hpp"

using namespace RTT::Communication;


boost::atomic<TaskContextServerFactory*> TaskContextServerFactory::m_Instance(0);
boost::mutex  TCSMapMutex;
boost::mutex  TaskContextServerFactory::m_InstantiationMutex;


// TaskContextServerFactory* GetInstance()
// {
//   TaskContextServerFactory* tmp = TaskContextServerFactory::m_Instance.load(boost::memory_order_consume);
//   if (!tmp) {
//     boost::mutex::scoped_lock guard(TaskContextServerFactory::m_InstantiationMutex);
//     tmp = TaskContextServerFactory::m_Instance.load(boost::memory_order_consume);
//     if (!tmp) {
//       tmp = new TaskContextServerFactory();
//       TaskContextServerFactory::m_Instance.store(tmp, boost::memory_order_release);
//       }
//     }
//     return tmp;
// }


/**
 * @brief Default contructor for the task context server factory
 * 
 */
TaskContextServerFactory::TaskContextServerFactory() {}

/**
 * @brief Default destructor for the task context server factory.
 * 
 */
TaskContextServerFactory::~TaskContextServerFactory() {}

/**
 * @brief This methods adds a taskcontext server generator to the list of known generators. If
 * a generator is already listed, the new one will be disregarded and needs to be deleted first.
 * 
 * @param NameID The name with which the generator shall bTCSMapMutexe listed
 * @param pTCSGenerator A pointer to the generator
 * @return bool The result of the add-operation
 */
bool TaskContextServerFactory::RegisterTaskContextServerGenerator(std::string NameID, ITypeGenerator<ITaskContextServer>::shared_ptr pTCSGenerator)
{
  bool IsRegistered = false;
  // Check whether the passed TCS generator is not listed yet
  if (m_RegisteredTCSGenerators.find(NameID) == m_RegisteredTCSGenerators.end())
  {
    // Ensure exclusive write access
    boost::unique_lock<boost::mutex> scoped_lock(TCSMapMutex);
    
    // Register the taskcontext server generator
    m_RegisteredTCSGenerators.insert(std::pair<std::string, ITypeGenerator<ITaskContextServer>::shared_ptr>(NameID, pTCSGenerator));
    
    // State the success
    IsRegistered = true;
  }
  
  // Return the result
  return IsRegistered;
}

/**
 * @brief This methods deletes a registered taskcontext server generator
 * 
 * @param NameID The name with which the generator is registerd
 * @return bool The result of the delete operation
 */
bool TaskContextServerFactory::DeleteTaskContextServerGenerator(std::string NameID)
{
  bool IsDeleted = false;
  
  // Check whether the passed TCS generator is already listed
  if (m_RegisteredTCSGenerators.find(NameID) != m_RegisteredTCSGenerators.end())
  {
    // Ensure exclusive write access
    boost::unique_lock<boost::mutex> scoped_lock(TCSMapMutex);
    
    // Delete the registered the taskcontext server generator
    m_RegisteredTCSGenerators.erase(NameID);
    
    // State the success
    IsDeleted = false;
  }
  
  // Return the result
  return IsDeleted;
}


/**
 * @brief Creates a taskcontext server object based upon the desired implementation option.
 * 
 * @param NameID The string/name identifier for the implementation option.
 * @param pTaskContext the task context the taskcontext server shall be attached to.
 * @return RTT::Communication::ITaskContextServer::shared_ptr
 */
ITaskContextServer::shared_ptr TaskContextServerFactory::CreateTaskContextServer(std::string NameID, TaskContext* pTaskContext, int argc, char* argv[])
{
  ITaskContextServer::shared_ptr pTaskContextServer;

  // Check whether the passed TCS generator is already listed
  if (m_RegisteredTCSGenerators.find(NameID) != m_RegisteredTCSGenerators.end())
  {
 
    pTaskContextServer = m_RegisteredTCSGenerators[NameID]->getNewInstance();

    pTaskContextServer->AttachTo(pTaskContext, argc, argv);   
  }
  
  return pTaskContextServer;
}




ITaskContextServer::shared_ptr TaskContextServerFactory::GetTaskContextServer(std::string NameID)
{
  ITaskContextServer::shared_ptr pTaskContextServer;
  if (m_RegisteredTCSGenerators.find(NameID) != m_RegisteredTCSGenerators.end())
  {
      pTaskContextServer = m_RegisteredTCSGenerators[NameID]->getNewInstance();
      return pTaskContextServer;
  }
  return pTaskContextServer;
}




std::vector<std::string> TaskContextServerFactory::GetAllRegisteredGeneratorNames()
{
  std::vector<std::string> RegisteredGeneratorNames;
  
  for(std::map<std::string, ITypeGenerator<ITaskContextServer>::shared_ptr>::iterator it = m_RegisteredTCSGenerators.begin(); 
      it != m_RegisteredTCSGenerators.end(); ++it) 
      {
	RegisteredGeneratorNames.push_back(it->first);
      }
  
  return RegisteredGeneratorNames;
}



ITypeGenerator<ITaskContextServer>::shared_ptr TaskContextServerFactory::GetGenerator(std::string registeredGeneratorImplementation){
    return m_RegisteredTCSGenerators[registeredGeneratorImplementation];
}






