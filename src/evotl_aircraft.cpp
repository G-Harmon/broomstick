//
// Created by Dhara Balaji on 8/31/21.
//

#include <iostream>
#include "evotl_aircraft.h"

namespace dharas
{

EvotlAircraft::EvotlAircraft(AircraftType t, double cruiseSpeed,
                             double batteryCapacity, double energyUse,
                             double timeToCharge,int passengersCount,
                             double faultProbability) : type(t), passengers(passengersCount),
                             fault_probability(faultProbability)
{
    // let's convert everything per hour to everything per min
    cruise_speed_ = cruiseSpeed/60.0;
    battery_capacity_ = batteryCapacity; // let it be for 60 min of real time = 60 sec of sim time
    time_to_charge_ = timeToCharge * 60.0;
    energey_use_ = energyUse / 60.0;
}

double EvotlAircraft::GetCruiseSpeed() const
{
    return cruise_speed_;
}

double EvotlAircraft::GetBatteryCapacity() const
{
    return battery_capacity_;
}

double EvotlAircraft::GetTimeToCharge() const
{
    return time_to_charge_;
}

int EvotlAircraft::GetPassengersCount() const
{
    return passengers;
}

double EvotlAircraft::GetFaultProbability() const
{
    return fault_probability;
}

AircraftType EvotlAircraft::GetAircraftType() const
{
    return type;
}

double EvotlAircraft::GetEnergyUse() const
{
    return energey_use_;
}

std::ostream& operator<<(std::ostream& out, const AircraftType& t)
{
    switch(t)
    {
        case AircraftType::ALPHA:
            out << "ALPHA";
            break;
        case AircraftType::BETA:
            out << "BETA";
            break;
        case AircraftType::CHARLIE:
            out << "CHARLIE";
            break;
        case AircraftType::DELTA:
            out << "DELTA";
            break;
        case AircraftType::ECHO:
            out << "ECHO";
            break;
        default:
            out << "UNKNOWN";
    }
    return out;
}
}
