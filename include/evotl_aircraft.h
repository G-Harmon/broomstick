//
// Created by Dhara Balaji on 8/30/21.
//

#ifndef JOBY_EVOTL_AIRCRAFT_H
#define JOBY_EVOTL_AIRCRAFT_H

#include <memory>

namespace dharas
{
enum class AircraftType
{
    ALPHA,
    BETA,
    CHARLIE,
    DELTA,
    ECHO,
    LAST // to make my life easier when generating random evotl aircraft
};
std::ostream& operator<<(std::ostream& out, const AircraftType& t);

class EvotlAircraft
{
public:
    // This is cause I'm lazy to write a loader which can read from a config file
    EvotlAircraft(AircraftType t, double cruiseSpeed, double batteryCapacity, double energyUse,
                  double timeToCharge, int passengersCount, double faultProbability);


    ~EvotlAircraft() = default;
    // Note: all the getters are in per min for easy math. Depending upon use-case
    //       we may want to use different getters for sim time.

    /** Get the cruise speed in mile per min (or mile per second for sim time) */
    double GetCruiseSpeed() const;

    /** Get the battery capacity in KW per min (or KW per second for sim time) */
    double GetBatteryCapacity() const;

    /** Get time to charge in min (or in second for sim time) */
    double GetTimeToCharge() const;

    /** Get energey use in KW per min (or in second for sim time) */
    double GetEnergyUse() const;

    int GetPassengersCount() const;

    /** Get fault probability per hour (or 60 seconds) */
    double GetFaultProbability() const;

    AircraftType GetAircraftType() const;
private:
    AircraftType type;
    double cruise_speed_;
    double battery_capacity_;
    double time_to_charge_;
    double energey_use_;
    int passengers;
    double fault_probability;
};
using EvotlAirCraftPtr = std::shared_ptr<EvotlAircraft>;
}

#endif //JOBY_EVOTL_AIRCRAFT_H
