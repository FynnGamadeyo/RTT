#ifndef REMOTE_TYPEGENERATOR_HPP
#define REMOTE_TYPEGENERATOR_HPP

#include <string>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>
#include <boost/shared_ptr.hpp>
#include "ITypeGenerator.hpp"
#include "ITaskContextServer.hpp"

namespace RTT
{namespace Communication
{
    /**
      * @brief This class enforcing the plugins to provide the necessary methods
      * for generating new taskcontextserver plugins
      * 
      */
    template<class GeneratorType, class ProductionType>
    class TypeGenerator  : public ITypeGenerator<GeneratorType>
    {
    public:     
      // Ctor / Dtor
      TypeGenerator(std::string Name) {};
      virtual ~TypeGenerator() {};
      
      /**
      * @brief Generates a new instance of the specified name service type
      * 
      * @return RTT::Communication::ITaskContextServer::shared_ptr
      */
      
      virtual boost::shared_ptr<GeneratorType> getNewInstance() //override
      {
	boost::shared_ptr<GeneratorType> pGenerator;

	// Check for T being the correct type
	if (boost::is_base_of<GeneratorType, ProductionType>::value)
	{  
	  // Create a name service object depending on the task context server implementation type
	  pGenerator.reset(new ProductionType());
	}
	else
	{
	  // throw error
	  // TBD
	}

	return pGenerator;
      }

     
    };    
}
}

#endif // REMOTE_TYPEDNAMESERVICEGENERATOR_HPP