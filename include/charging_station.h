//
// Created by Dhara Balaji on 8/30/21.
//

#ifndef JOBY_CHARGING_STATION_H
#define JOBY_CHARGING_STATION_H

#include <chrono>
#include <mutex>
#include <vector>
#include <future>
#include <list>

namespace dharas
{
class ChargingStation
{
public:
    explicit ChargingStation(int count);

    /**
     * gives you charging station # or -1 if there are non available
     * @return
     */
    bool charge();
    /**
     * empty that charging station
     */
    void doneCharging();
    /**
     * is there any charging station available
     * @return
     */
    bool isAvailable();

private:

    /** Total available gas stations */
    int total;

    /** This class is getting used in multi-threaded env, let's protect it */
    std::mutex mutex;

    /** represents charging stations - True means it is occupied. */
    std::list<bool> chargingStations;
};
using ChargingStationPtr = std::shared_ptr<ChargingStation>;
}

#endif //JOBY_CHARGING_STATION_H
