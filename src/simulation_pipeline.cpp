//
// Created by Dhara Balaji on 8/30/21.
//
#include <simulation_pipeline.h>
#include <evotl_aircraft_builder.h>
#include <thread>
#include <iostream>
#include "simulation_runner.h"

namespace dharas
{

void SimulationPipeline::run(int numOfVehicles, int totalChargingStations, std::chrono::duration<double> simTime)
{
    SimulationRunner runner(simTime);
    auto aircrafts = buildAircrafts(numOfVehicles);
    auto station = std::make_shared<ChargingStation>(totalChargingStations);
    std::vector<SimActorPtr> aircraftSimActors;
    aircraftSimActors.reserve(numOfVehicles);
    // register our aircraft actors
    for (auto &aircraft : aircrafts)
    {
        SimActorPtr actor = std::make_shared<AircraftSimulationActor>(aircraft, station);
        aircraftSimActors.emplace_back(actor);
        runner.RegisterActor(actor);
    }
    // this was to see clean debug stmt
//    std::this_thread::sleep_for(std::chrono::seconds(2));
    runner.StartSimulation();

    std::vector<SimRunnerResponse> stats;
    stats.reserve(numOfVehicles);
    for (auto &aircraft : aircraftSimActors)
    {
        AircraftSimulationRunnerPtr aircraftSimRunner = std::dynamic_pointer_cast<AircraftSimulationActor>(aircraft);
        stats.emplace_back(aircraftSimRunner->CollectStats());
    }

    printStats(stats);
}

void SimulationPipeline::printStats(std::vector<SimRunnerResponse>& stats)
{
    std::cout << "\n\n\n***** ***** **** **** **** *****\n\n";
    std::unordered_map<AircraftType, SimMetrics> metrics;

    for (const auto& stat : stats)
    {
        ++metrics[stat.t].numInstances;
        metrics[stat.t].timeInFlight += stat.time_in_flight;
        metrics[stat.t].chargeWaitingTime += stat.charge_waiting_time;
        metrics[stat.t].distanceTravelled += stat.distance_travelled;
        metrics[stat.t].numOfFaults = std::max(metrics[stat.t].numOfFaults, numFaults(stat.faultProbability, stat.time_in_flight));
        metrics[stat.t].passengerCount += stat.passengerCount;
    }
    for (const auto& itr: metrics)
    {
        auto aircraftType = itr.first;
        auto metric = itr.second;
        std::cout << "stats for " << aircraftType << "\n";
        std::cout << "Avg time in flight: " << metric.timeInFlight/metric.numInstances << "\n";
        std::cout << "Avg time waiting to be charged: " << metric.chargeWaitingTime/metric.numInstances << "\n";
        std::cout << "Max num of faults: " << metric.numOfFaults << "\n";
        std::cout << "Total distance travelled: " << metric.passengerCount * metric.distanceTravelled << "\n";
    }
}

/**
 *
 * @param faultProbability per 60 min
 * @param totalTimeInFlight
 * @return num of faults happening
 * reference: https://math.stackexchange.com/questions/2480542/probability-of-an-event-occurring-within-a-smaller-time-interval-if-one-knows-th
 *
 * I solved lambda * e^-lambda = p; where p is the faultProbability
 * then lambda = e^(p+1).
 * num of faults in x min = x * lambda.
 */
double SimulationPipeline::numFaults(double faultProbability, double totalTimeInFlight)
{
    auto lambda = exp(faultProbability + 1);
    return totalTimeInFlight * lambda;
}

std::vector<EvotlAirCraftPtr> SimulationPipeline::buildAircrafts(int numOfVehicles)
{
    std::vector<EvotlAirCraftPtr> aircrafts;
    // Build aircrafts of random numbers of given types
    aircrafts.reserve(numOfVehicles);
    auto total = static_cast<int>(AircraftType::LAST);
    for (int i = 0; i < numOfVehicles; i++)
        aircrafts.push_back(
                aircraftBuilder.BuildAircraft(static_cast<AircraftType>(rand() % total)));
    return aircrafts;
}

}