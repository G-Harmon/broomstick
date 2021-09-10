//
// Created by Dhara Balaji on 9/5/21.
//

#ifndef JOBY_SIM_ACTOR_H
#define JOBY_SIM_ACTOR_H

namespace dharas
{
// Abstract class
/**
 * Abstract class, SimulationRunner uses this to notify the actor
 * every second/tick
 */
class SimActor
{
public:
    virtual void Update(uint16_t simIterations) = 0;
//    virtual ~SimActor();
};
using SimActorPtr = std::shared_ptr<SimActor>;
}
#endif //JOBY_SIM_ACTOR_H
