//
// Created by Dhara Balaji on 8/30/21.
//

#ifndef JOBY_AIRCRAFT_SIMULATION_RUNNER_H
#define JOBY_AIRCRAFT_SIMULATION_RUNNER_H

#include "charging_station.h"
#include "evotl_aircraft.h"
#include "sim_actor.h"

namespace dharas
{
struct SimRunnerResponse
{
    AircraftType t;
    double time_in_flight;
    double charge_waiting_time;
    double faultProbability;
    double distance_travelled;
    int passengerCount;
};

/** Runs EvotlAircraft in simulation */
// Bridge between Aircraft & SimulationPipeline. Since all the types of EVOTL uses same "impl" to run
// simulation, we do this here once
class AircraftSimulationActor : public SimActor
{

    enum class AircraftState {
        RUNNING,
        WAITING, // waiting for charging queue
        CHARGING
    };
public:
    AircraftSimulationActor(EvotlAirCraftPtr& aircraft, ChargingStationPtr& chargingStation);
    /**
     * @return Simulation stats that we are asked to collect
     */
    SimRunnerResponse CollectStats();
    /**
     * "Updates" the Aircraft for tick
     * @param simIterations
     */
    void Update(uint16_t simIterations) override;

private:
    EvotlAirCraftPtr aircraft;
    ChargingStationPtr chargingStation;

    /// Aircraft state
    AircraftState state;

    /// Start out with full battery capacity
    double remainingBattery;
    /// Displacement: battery consumption in last 60 sec
    double displacement;

//    /// Block till charger is available
//    std::unique_lock<std::mutex> lock;
//    std::condition_variable blockOnChargerCv;

    /// Final response
    SimRunnerResponse response{};

};
using AircraftSimulationRunnerPtr = std::shared_ptr<AircraftSimulationActor>;
}
#endif //JOBY_AIRCRAFT_SIMULATION_RUNNER_H
