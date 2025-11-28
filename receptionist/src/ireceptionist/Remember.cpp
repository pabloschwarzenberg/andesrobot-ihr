#include "Remember.hpp"

NodeStatus Remember::tick()
{
  Expected<std::string> msg = getInput<std::string>("object");
  if (!msg)
  {
    throw BT::RuntimeError("missing required input [object]: ", 
                            msg.error() );
  }
  // use the method value() to extract the valid message.
  std::cout << "Robot remember: " << msg.value() << std::endl;
  return NodeStatus::SUCCESS;
}
