//
// Created by Dhara Balaji on 9/5/21.
//

#ifndef JOBY_SIMULATION_RUNNER_H
#define JOBY_SIMULATION_RUNNER_H

#include "sim_actor.h"

#include <vector>

/**
 * this is meat of the whole simulation. It uses facade pattern
 * or some of the SOLID principle to keep thing simple and stupid.
 */
namespace dharas {
class SimulationRunnerPrivate;
class Ticker;
using TickerPtr = std::shared_ptr<Ticker>;
class SimulationRunner
{
public:
    explicit SimulationRunner(std::chrono::duration<double> duration);
    void RegisterActor(SimActorPtr & actor);
    void StartSimulation();
    ~SimulationRunner();
private:
    std::vector<std::unique_ptr<SimulationRunnerPrivate>> actors;
    std::chrono::duration<double> duration;
    std::shared_ptr<Ticker> ticker;
};
}

#endif //JOBY_SIMULATION_RUNNER_H
