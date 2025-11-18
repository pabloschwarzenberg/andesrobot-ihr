#include "See.hpp"

NodeStatus See::tick()
{
  Optional<std::string> msg = getInput<std::string>("object");
  // Check if optional is valid. If not, throw its error
  if (!msg)
  {
    throw BT::RuntimeError("missing required input [object]: ", 
                            msg.error() );
  }
  // use the method value() to extract the valid message.
  std::cout << "Robot see: " << msg.value() << std::endl;
  return NodeStatus::SUCCESS;
}