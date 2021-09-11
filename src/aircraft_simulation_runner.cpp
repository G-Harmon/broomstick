//
// Created by Dhara Balaji on 8/31/21.
//

#include <iostream>
#include <thread>
#include "aircraft_simulation_runner.h"

namespace dharas
{
AircraftSimulationActor::AircraftSimulationActor(EvotlAirCraftPtr& aircraft,
                                                 ChargingStationPtr& chargingStation) : aircraft(aircraft),
                                   chargingStation(chargingStation), state(AircraftState::RUNNING),
                                   displacement(0), response()
{
    std::cout << "Creating SimRunner for " << aircraft->GetAircraftType() << "\n";
    response.t = aircraft->GetAircraftType();
    response.passengerCount = aircraft->GetPassengersCount();
    response.faultProbability = aircraft->GetFaultProbability();
    remainingBattery = aircraft->GetBatteryCapacity();
}

SimRunnerResponse AircraftSimulationActor::CollectStats()
{
    return response;
}

// This could use State design pattern: https://en.wikipedia.org/wiki/State_pattern
// than the if/else, but for now it did the trick :-)
void AircraftSimulationActor::Update(uint16_t simIterations)
{
    /**
     * Flying algorithm:
     *
     * every sec (in sim time = 60 sec real time):
     *      displacement = cruise_speed_
     *      remaining battery -= displacement * energy consumption
     *
     * When we get charge reset displacement, remainingBattery
     */
    auto chargingFor = 0;
    if (state == AircraftState::RUNNING) {
        if (remainingBattery > 0) {
//            std::cout << "Running [" << response.t << "]" << "\n";
            response.distance_travelled += aircraft->GetCruiseSpeed();
            response.time_in_flight += 1;
            displacement += aircraft->GetCruiseSpeed();
            remainingBattery -= (displacement * aircraft->GetEnergyUse());
        } else {
//            std::cout << "Ran out of battery [" << aircraft->GetAircraftType() << "]" << "\n";
            state = AircraftState::WAITING;
            response.charge_waiting_time += 1;
        }
    } else if (state == AircraftState::WAITING) {
//        std::cout << "Waiting for charger [" << aircraft->GetAircraftType() << "]" << "\n";
        if (chargingStation->isAvailable() && chargingStation->charge()) {
            state = AircraftState::CHARGING;
            ++chargingFor;
        } else {
            response.charge_waiting_time += 1;
        }
    } else {
//        std::cout << "Charging [" << aircraft->GetAircraftType() << "]" << "\n";
        // we are charging
        ++chargingFor;
        if (chargingFor >= aircraft->GetTimeToCharge()) {
            chargingStation->doneCharging();
            state = AircraftState::RUNNING;
            displacement = 0; // resetting after full battery
            chargingFor = 0;
            remainingBattery = aircraft->GetBatteryCapacity();
        }
    }

}

}
