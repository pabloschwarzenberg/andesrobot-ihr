#include "Talk.hpp"

NodeStatus Talk::tick()
{
  Optional<std::string> msg = getInput<std::string>("speech");
  // Check if optional is valid. If not, throw its error
  if (!msg)
  {
    throw BT::RuntimeError("missing required input [message]: ", 
                            msg.error() );
  }
  // use the method value() to extract the valid message.
  std::cout << "Robot says: " << msg.value() << std::endl;
  return NodeStatus::SUCCESS;
}

NodeStatus Greet::tick()
{
  return Talk::tick();
}

NodeStatus Ask::tick()
{
  return Talk::tick();
}