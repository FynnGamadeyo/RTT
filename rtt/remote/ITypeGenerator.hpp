
#ifndef REMOTE_ITYPEGENERATOR_HPP
#define REMOTE_ITYPEGENERATOR_HPP

#include <string>
#include <boost/shared_ptr.hpp>

namespace RTT
{namespace Communication
{
    /**
      * @brief This class enforcing the plugins to provide the necessary methods
      * for generating new taskcontextserver plugins
      * 
      */
    template<class GeneratorType>
    class ITypeGenerator 
    {
    private:
      std::string m_Name;
    public:  
       // Type Definition of a smart pointer to a taskcontext server generator
      typedef boost::shared_ptr<ITypeGenerator> shared_ptr;
      
      // Ctor / Dtor
      ITypeGenerator() : m_Name("Unknown") {};
      ITypeGenerator(std::string Name) : m_Name(Name) {};
      virtual ~ITypeGenerator() {};
      
      // Generating methodsgetNewInstancegetNewInstance
      virtual boost::shared_ptr<GeneratorType> getNewInstance() = 0;
      virtual inline std::string getName()
      {
	return m_Name;
      }
    };    
}
}

#endif // REMOTE_TASKCONTEXTSERVERGENERATOR_HPP