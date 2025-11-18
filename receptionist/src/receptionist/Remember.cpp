#include "Remember.hpp"

NodeStatus Remember::tick()
{
  Optional<std::string> msg = getInput<std::string>("object");
  // Check if optional is valid. If not, throw its error
  if (!msg)
  {
    throw BT::RuntimeError("missing required input [object]: ", 
                            msg.error() );
  }
  // use the method value() to extract the valid message.
  std::cout << "Robot remember: " << msg.value() << std::endl;
  return NodeStatus::SUCCESS;
}