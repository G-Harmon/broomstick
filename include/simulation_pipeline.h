//
// Created by Dhara Balaji on 8/30/21.
//

#ifndef JOBY_SIMULATION_PIPELINE_H
#define JOBY_SIMULATION_PIPELINE_H

#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include "evotl_aircraft.h"
#include "charging_station.h"
#include "aircraft_simulation_runner.h"
#include "evotl_aircraft_builder.h"

namespace dharas
{
class SimulationPipeline
{
public:
    SimulationPipeline() = default;
    /**
     * Run simulation
     * @param numOfVehicles
     * @param totalChargingStations
     * @param simTime
     */
    void run(int numOfVehicles, int totalChargingStations, std::chrono::duration<double> simTime);
private:
    struct SimMetrics
    {
        int numInstances{0};
        double timeInFlight{0};
        double chargeWaitingTime{0};
        double numOfFaults{0};
        double distanceTravelled{0};
        int passengerCount{0};
    };

    /**
     * Build aircrafts
     * @param numOfVehicles
     * @return
     */
    std::vector<EvotlAirCraftPtr> buildAircrafts(int numOfVehicles);

    /**
     * print "collective" stats
     * @param stats
     */
    static void printStats(std::vector<SimRunnerResponse> &stats);
    /**
     * Calculate num of faults using Poisson distribution
     * @param faultProbability
     * @param totalTimeInFlight
     * @return
     */
    static double numFaults(double faultProbability, double totalTimeInFlight);

    EvotlAircraftBuilder aircraftBuilder{};

};
}
#endif //JOBY_SIMULATION_PIPELINE_H
