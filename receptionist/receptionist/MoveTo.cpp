#include "MoveTo.hpp"

NodeStatus MoveTo::tick()
{
  auto input = getInput<Position2D>("location");
  // Check if optional is valid. If not, throw its error
  if (!input)
  {
    throw BT::RuntimeError("missing required input [location]: ", 
                            msg.error() );
  }
  Position2D target = res.value();
  printf("Target positions: [ %.1f, %.1f ]\n", target.x, target.y );  
  return NodeStatus::SUCCESS;
}